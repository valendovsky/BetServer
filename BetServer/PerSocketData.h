#ifndef PERSOCKETDATA_H
#define PERSOCKETDATA_H

#include <string>

#include "TennisMatch.h"


// ���������� � ������������ �������
struct PerSocketData
{
	unsigned int userId;           // �� ������������ ����������
	std::string  login;            // ����� �� ���� ������������������ �������������
	bool         auth =     false; // ������� � ��������� �����������
	bool         is_admin = false; // ������� � ������� ��������������
	TennisMatch   workGame;        // �������� ����
};

#endif // !PERSOCKETDATA_H