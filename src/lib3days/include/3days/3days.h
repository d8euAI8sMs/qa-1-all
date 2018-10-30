#pragma once

#include <string>

enum _GetDatePlus3DaysStrErrc : int
{
    ErrorSuccess = 0,
    ErrorInvalidFormat,
    ErrorInvalidDate
};

int GetDatePlus3DaysStr(std::string date, std::string & date_str);
