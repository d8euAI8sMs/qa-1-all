#ifdef LIB3DAYS_EXE

#include <tuple>
#include <iostream>

#include <3days/3days.h>

void main()
{
    setlocale(LC_ALL, "RU");

    std::tuple < std::string, int, std::string > inputs[] = {
        std::make_tuple("01.01", ErrorSuccess,       "четвертое января"),
        std::make_tuple("1.01",  ErrorInvalidFormat, ""                ),
        std::make_tuple("AB.CD", ErrorInvalidFormat, ""                ),
        std::make_tuple("32.01", ErrorInvalidDate,   ""                ),
        std::make_tuple("31.13", ErrorInvalidDate,   ""                ),
        std::make_tuple("05.11", ErrorSuccess,       "восьмое ноября"  ),
        std::make_tuple("29.01", ErrorSuccess,       "первое февраля"  ),
        std::make_tuple("30.01", ErrorSuccess,       "второе февраля"  ),
        std::make_tuple("31.01", ErrorSuccess,       "третье февраля"  ),
        std::make_tuple("28.02", ErrorSuccess,       "третье марта"    ),
        std::make_tuple("31.12", ErrorSuccess,       "третье января"   ),
        std::make_tuple("END", 0, "")
    };

    std::string result;
    int status;

    for (size_t i = 0; std::get < 0 > (inputs[i]) != "END"; ++i)
    {
        status = GetDatePlus3DaysStr(std::get < 0 > (inputs[i]), result);
        if (status != std::get < 1 > (inputs[i]))
        {
            std::cout << "failed[status]: " << i + 1 << " [" << std::get < 1 > (inputs[i]) << "] vs actual [" << status << "]" << std::endl;
            continue;
        }
        if (status == 0 && result != std::get < 2 > (inputs[i]))
        {
            std::cout << "failed[result]: " << i + 1 << " [" << std::get < 2 > (inputs[i]) << "] vs actual [" << result << "]" << std::endl;
            continue;
        }
        std::cout << "success: " << i + 1 << std::endl;
    }

    system("pause");
}

#endif