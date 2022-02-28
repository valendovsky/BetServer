#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <string>
#include <algorithm>
#include <cctype>
#include <Windows.h>


// Класс для форматирования строк std::string
// *удаляет кавычки в строке
// *понижает регистр
// *конвертирует между форматами utf8 и w1251
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