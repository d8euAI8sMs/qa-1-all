#pragma once

enum IsExpressionCorrect_Result : int
{
    result_correct = 0,
    result_unbalanced_braces,
    result_unmatched_braces,
    result_unexpected_token
};

int IsExpressionCorrect(const char * expr);
