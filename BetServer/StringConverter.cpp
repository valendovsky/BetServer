#include "StringConverter.h"

// Убирает кавычки из строки
std::string StringConverter::deleteQuotes()
{
	while (m_str.find('"') != std::string::npos)
	{
		m_str.erase(std::find(m_str.begin(), m_str.end(), '"'));
	}

	return m_str;
}

// Приведение символов к нижнему регистру
std::string StringConverter::toLower()
{
	std::transform(m_str.begin(), m_str.end(), m_str.begin(), std::tolower);

	return m_str;
}

// Конвертация из UTF-8 в стандарт Windows-1251 
std::string StringConverter::utf8ToW1251()
{
	// на единицу больше для '\0'
	int length = m_str.length() + 1;
	char* utf8 = new char[length];
	std::copy(m_str.begin(), m_str.end(), utf8);
	utf8[m_str.length()] = '\0';

	wchar_t* wstr = new wchar_t[length];
	char* w1251 = new char[length];

	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, length);
	wstr[MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, 0)];
	WideCharToMultiByte(1251, 0, wstr, -1, w1251, length, NULL, NULL);
	w1251[WideCharToMultiByte(1251, 0, wstr, -1, w1251, 0, NULL, NULL)];

	m_str = w1251;

	delete[] utf8;
	delete[] wstr;
	delete[] w1251;

	return m_str;
}

// Конвертация из стандарта Windows-1251 в UTF-8
std::string StringConverter::w1251ToUtf8()
{
	const char* str = m_str.c_str();
	wchar_t* wstr = nullptr;
	char* utf8 = nullptr;


	int result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (result_u != 0)
	{
		wstr = new WCHAR[result_u];
		if (MultiByteToWideChar(1251, 0, str, -1, wstr, result_u))
		{
			int result_c = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, 0, 0, 0, 0);
			if (result_c != 0)
			{
				utf8 = new char[result_c];
				if (WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, result_c, 0, 0))
				{
					m_str = utf8;
				}
			}
		}
	}

	delete[] wstr;
	delete[] utf8;

	return m_str;
}
