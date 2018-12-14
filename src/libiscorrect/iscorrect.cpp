#include "iscorrect.h"

#include <string>
#include <vector>
#include <stack>
#include <cctype>

enum token_type
{
    token_integral_constant, ///< e.g. 1, 01, 0xB, 0xb
    token_identifier,        ///< e.g. x, log, exp, a_b
    token_brace,             ///< e.g. {}, (), []
    token_operator,          ///< e.g. +-*/
    token_unknown,           ///< e.g. @#$
    token_eos,               ///< end of string
};

struct token
{
    token_type type;
    size_t pos;
    size_t len;
    std::string val;
};

namespace token_traits
{
    bool is_opening(const std::string & b)
    {
        return b.find_first_of("[({") != std::string::npos;
    }
    bool is_closing(const std::string & b)
    {
        return b.find_first_of("])}") != std::string::npos;
    }
    bool are_matched(const std::string & b1, const std::string & b2)
    {
        return (std::string("[({").find(b1) == std::string("])}").find(b2)) ||
            (std::string("[({").find(b2) == std::string("])}").find(b1));
    }
    bool is_valid_un_op(const std::string & b1)
    {
        return (b1 == "+") || (b1 == "-");
    }
}

class lexer
{
private:
    const std::string _s;
    size_t _pos;
public:
    lexer(std::string src) : _s(std::move(src)), _pos(0) {}
public:
    token_type next(token & r);
    const std::string & source() const { return _s; }
};

token_type lexer::next(token & r)
{
    while ((_pos < _s.size()) && std::isspace(_s[_pos])) ++_pos;

    r.val = "";
    r.len = 0;
    r.pos = _pos;
    r.type = token_eos;

    if (_pos >= _s.size()) { return token_eos; }

    while (_pos < _s.size())
    {
        if ((r.type == token_eos ||
             r.type == token_integral_constant ||
             r.type == token_identifier) && std::isdigit(_s[_pos]))
        {
            r.type = token_integral_constant;
            ++_pos; continue;
        }
        if ((r.type == token_eos ||
             r.type == token_identifier) && std::isalnum(_s[_pos]))
        {
            r.type = token_identifier;
            // ((r.type == token_eos) && std::isdigit(_s[_pos])) branch already handled
            ++_pos; continue;
        }
        if ((r.type == token_eos) && (std::string("[{()}]").find(_s[_pos]) != std::string::npos))
        {
            r.type = token_brace;
            ++_pos; break;
        }
        if ((r.type == token_eos) && (std::string("+-/*").find(_s[_pos]) != std::string::npos))
        {
            r.type = token_operator;
            ++_pos; break;
        }
        break;
    }

    r.len = _pos - r.pos;
    r.val = _s.substr(r.pos, r.len);
    
    return r.type;
}

enum expression_type
{
    expr_const,             ///< e.g. 1, 01, 0xB, 0xb
    expr_fname,             ///< e.g. x, log, exp, a_b
    expr_op_br,             ///< e.g. [{(
    expr_cl_br,             ///< e.g. )}]
    expr_op,                ///< e.g. +-/*
    expr_complex,           ///< e.g. (a + b)
    expr_soe,               ///< start of expression
};

struct expression
{
    expression_type type;
    size_t pos;
    size_t len;
    std::string val;

    static expression wrap(token && t)
    {
        expression expr;
        expr.val = std::move(t.val);
        expr.pos = t.pos;
        expr.len = t.len;
        
        switch (t.type)
        {
        case token_integral_constant: expr.type = expr_const; break;
        case token_identifier: expr.type = expr_fname; break;
        case token_brace: expr.type = token_traits::is_opening(expr.val) ? expr_op_br : expr_cl_br; break;
        case token_operator: expr.type = expr_op; break;
        case token_unknown:
        case token_eos:
        default:
            // should not occur
            break;
        }

        return expr;
    }
};

class parser
{
private:
    token _tok;
    lexer _lexer;
    std::stack < expression > _expr;
public:
    parser(std::string s) : _lexer(std::move(s))
    {
        _expr.push({ expr_soe, 0, 0, "" });
    }
public:
    int operator() ();
private:
    int _on_token();
    int _purge();
};

int parser::operator() ()
{
    int r;
    for (;;)
    {
        _lexer.next(_tok);
        if ((r = _on_token()) != result_correct) return r;
        if (_tok.type == token_eos) return r;
    }
}

int parser::_on_token()
{
    switch (_tok.type)
    {
    case token_eos:
        if (_expr.top().type == expr_op)
            return result_unexpected_token;
        return _purge();
    /* [[fallthrough]] */
    case token_identifier:
    case token_integral_constant:
    {
        if ((_expr.top().type != expr_soe) &&
            (_expr.top().type != expr_op_br) &&
            (_expr.top().type != expr_op))
            return result_unexpected_token;
        _expr.push(expression::wrap(std::move(_tok)));
        break;
    }
    case token_operator:
        if ((_expr.top().type != expr_soe) &&
            (_expr.top().type != expr_const) &&
            (_expr.top().type != expr_complex) &&
            (_expr.top().type != expr_op_br) &&
            (_expr.top().type != expr_op))
            return result_unexpected_token;
        // missing 1st operand
        if (((_expr.top().type == expr_soe) || (_expr.top().type == expr_op_br)) &&
            !token_traits::is_valid_un_op(_tok.val))
            return result_unexpected_token;
        // e.g. `a + * b` or `a / * b`
        if ((_expr.top().type == expr_op) &&
            !token_traits::is_valid_un_op(_tok.val))
            return result_unexpected_token;
        _expr.push(expression::wrap(std::move(_tok)));
        break;
    case token_brace:
        if (token_traits::is_opening(_tok.val))
        {
            if ((_expr.top().type != expr_soe) &&
                (_expr.top().type != expr_fname) &&
                (_expr.top().type != expr_op_br) &&
                (_expr.top().type != expr_op))
                return result_unexpected_token;
            _expr.push(expression::wrap(std::move(_tok)));
        }
        else
        {
            // don't accept fn(), only fn(x)
            if ((_expr.top().type != expr_const) &&
                (_expr.top().type != expr_complex))
                return result_unexpected_token;
            _expr.push(expression::wrap(std::move(_tok)));
            int r;
            if ((r = _purge()) != result_correct) return r;
        }
        break;
    case token_unknown:
    default:
        return result_unexpected_token;
    }
    return result_correct;
}

int parser::_purge()
{
    // empty expression
    if (_expr.top().type == expr_soe) return result_correct;
    if (_expr.top().type != expr_cl_br)
    {
        while ((_expr.top().type != expr_op_br)
               && (_expr.top().type != expr_fname)
               && (_expr.top().type != expr_soe))
               _expr.pop();
        if (_expr.top().type == expr_soe)
            return result_correct;
        if (_expr.top().type == expr_fname)
            return result_unexpected_token;
        return result_unmatched_braces;
    }

    expression cl = std::move(_expr.top());
    expression op;

    // open brace must exist somewhere on the stack
    do _expr.pop(); while (_expr.top().type != expr_op_br);

    op = std::move(_expr.top());
    _expr.pop();

    if (!token_traits::are_matched(cl.val, op.val))
        return result_unmatched_braces;

    // the stack top is either fname or soe
    if (_expr.top().type == expr_fname)
    {
        op = std::move(_expr.top());
        _expr.pop();
    }

    expression res;
    res.type = expr_complex;
    res.pos = op.pos;
    res.len = cl.pos - op.pos + cl.len;
    res.val = _lexer.source().substr(res.pos, res.len);

    _expr.push(std::move(res));

    return result_correct;
}

int IsExpressionCorrect(const char * expr)
{
    return parser(expr)();
}

#ifdef ISCORRECT_CPP_EXE

#include <assert.h>

bool operator == (const token & t1, const token & t2)
{
    return (t1.len == t2.len) && (t1.pos == t2.pos) &&
        (t1.type == t2.type) && (t1.val == t2.val);
}

void main()
{
    std::string s = "123 + abc (0xa) log(x)";
    //               0123456789 123456789 1
    //               0000000000111111111122

    token tok;

    lexer lex(std::move(s));

    assert(lex.next(tok) == token_integral_constant);
    assert((token { token_integral_constant, 0, 3, "123" }) == tok);

    assert(lex.next(tok) == token_operator);
    assert((token { token_operator, 4, 1, "+" }) == tok);

    assert(lex.next(tok) == token_identifier);
    assert((token { token_identifier, 6, 3, "abc" }) == tok);

    assert(lex.next(tok) == token_brace);
    assert((token { token_brace, 10, 1, "(" }) == tok);

    assert(lex.next(tok) == token_integral_constant);
    assert((token { token_integral_constant, 11, 1, "0" }) == tok);

    assert(lex.next(tok) == token_identifier);
    assert((token { token_identifier, 12, 2, "xa" }) == tok);

    assert(lex.next(tok) == token_brace);
    assert((token { token_brace, 14, 1, ")" }) == tok);

    assert(lex.next(tok) == token_identifier);
    assert((token { token_identifier, 16, 3, "log" }) == tok);

    assert(lex.next(tok) == token_brace);
    assert((token { token_brace, 19, 1, "(" }) == tok);

    assert(lex.next(tok) == token_identifier);
    assert((token { token_identifier, 20, 1, "x" }) == tok);

    assert(lex.next(tok) == token_brace);
    assert((token { token_brace, 21, 1, ")" }) == tok);

    assert(lex.next(tok) == token_eos);
    assert((token { token_eos, 22, 0, "" }) == tok);
    
    assert(parser("+")() == result_unexpected_token);
    assert(parser("123")() == result_correct);
    assert(parser("abc")() == result_unexpected_token);
    assert(parser("abc(1)")() == result_correct);
    assert(parser("abc(fn(1))")() == result_correct);
    assert(parser("(1)")() == result_correct);
    assert(parser("((1))")() == result_correct);
    assert(parser("(1 + )")() == result_unexpected_token);
    assert(parser("1 + 2")() == result_correct);
    assert(parser(" * 2")() == result_unexpected_token);
    assert(parser(" + 2")() == result_correct);
    assert(parser("1 * - 2")() == result_correct);
    assert(parser("1 + * 2")() == result_unexpected_token);
    assert(parser("1 + (3 + 4) + 5")() == result_correct);

    system("pause");
}

#endif
