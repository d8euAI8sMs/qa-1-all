#include <3days/3days.h>

#include <cstdint>
#include <cctype>   // for std::isdigit

#define LIB3DAYS_TRY(x) if ((status = x) != 0) return status

namespace
{

    /* Globals */

    std::string s_daysOfMonth[] = {
        "первое", "второе", "третье", "четвертое", "пятое",
            "шестое", "седьмое", "восьмое", "девятое", "десятое",
        "одиннадцатое", "двенадцатое", "тринадцатое", "четырнадцатое", "пятнадцатое",
            "шестнадцатое", "семнадцатое", "восемнадцатое", "девятнадцатое", "двадцатое",
        "двадцать первое", "двадцать второе", "двадцать третье", "двадцать четвертое", "двадцать пятое",
            "двадцать шестое", "двадцать седьмое", "двадцать восьмое", "двадцать девятое", "тридцатое",
        "тридцать первое"
    };

    std::string s_months[] = {
        "января", "февраля", "марта", "апреля", "мая", "июня",
        "июля", "августа", "сентября", "октября", "ноября", "декабря"
    };

    std::uint8_t s_daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    /* Types */

    struct date_t
    {
        std::uint8_t dayOfMonth; /* zero-based */
        std::uint8_t month; /* zero-based */
    };

    /* Formatters */

    std::string ToString(const date_t & d)
    {
        return std::string(s_daysOfMonth[d.dayOfMonth]) + " " + std::string(s_months[d.month]);
    }

    /* Business Logic */

    bool Add3Days(date_t & d)
    {
        d.dayOfMonth += 3;

        if (d.dayOfMonth >= s_daysInMonth[d.month])
        {
            d.dayOfMonth -= s_daysInMonth[d.month];

            d.month += 1;

            if (d.month == 12)
            {
#               ifdef LIB3DAYS_NO_INTENTIONAL_BUG
                    d.month = 0;
#               else
                    d.month = 1;
#               endif
                return true;
            }
        }

        return false;
    }

    /* Validators */

    int Validate(const date_t & d)
    {
        return (d.month < 12) &&
               (d.dayOfMonth < s_daysInMonth[d.month])
               ? ErrorSuccess : ErrorInvalidDate;
    }

    /* Parsers */

    int Parse(const std::string & s, date_t & d)
    {
        if (s.length() != 5) return ErrorInvalidFormat;
        if (s[2] != '.') return ErrorInvalidFormat;

#       ifdef LIB3DAYS_NO_INTENTIONAL_BUG
        if (!std::isdigit(s[0]) || !std::isdigit(s[1]) ||
            !std::isdigit(s[3]) || !std::isdigit(s[4]))
             return ErrorInvalidFormat;
#       endif

        d.dayOfMonth = 10 * (s[0] - '0') + (s[1] - '0') - 1;
        d.month = 10 * (s[3] - '0') + (s[4] - '0') - 1;

        return ErrorSuccess;
    }

};

int GetDatePlus3DaysStr(std::string date, std::string & date_str)
{
    int status;

    date_t d;

    LIB3DAYS_TRY(Parse(date, d));
    LIB3DAYS_TRY(Validate(d));

    /* bool overflow = */ Add3Days(d);

    date_str = ToString(d);

    return status;
}
