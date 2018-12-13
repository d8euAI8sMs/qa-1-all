#pragma once

#include <string>

class TimeConverter
{
public:
	/** �������� �����, ������� �������� ����� �������� init_time � ������� "HH:MM" + 5 �����,
	����� �������� new_time_str � ��������� �������������.
	* @param init_time - ��������� ����� "HH:MM".
	* @param new_time_str - �����, ������� ����� init_time + 5 �����.
	*/
	static int GetTimePlus5MinStr(std::string init_time, std::string& new_time_str);
	

};
