#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <string>
#include <algorithm>
#include <cctype>
#include <Windows.h>


// ����� ��� �������������� ����� std::string
// *������� ������� � ������
// *�������� �������
// *������������ ����� ��������� utf8 � w1251
class StringConverter
{
private:
	std::string m_str;

public:
	StringConverter(const std::string& input)
		: m_str(input)
	{

	}

	std::string deleteQuotes();
	std::string toLower();
	std::string utf8ToW1251();
	std::string w1251ToUtf8();

};

#endif // !STRINGCONVERTER_H