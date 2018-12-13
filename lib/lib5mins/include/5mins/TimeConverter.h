#pragma once

#include <string>

class TimeConverter
{
public:
	/** Получить время, которое передано через параметр init_time в формате "HH:MM" + 5 минут,
	через параметр new_time_str в строковом представлении.
	* @param init_time - начальное время "HH:MM".
	* @param new_time_str - время, которое равно init_time + 5 минут.
	*/
	static int GetTimePlus5MinStr(std::string init_time, std::string& new_time_str);
	

};
