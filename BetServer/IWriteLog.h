#ifndef IWRITELOG_H
#define IWRITELOG_H

#include <iostream>
#include <string>
#include <fstream>

#include "Constants.h"
#include "Timer.h"


// ������������ ����� ��� ���������� �����
class IWriteLog
{
public:
	// ������ ����������� ������� ��� ���������� �����
	virtual void writeLog(const std::string& message) const = 0;

	// ����������� ����������
	virtual      ~IWriteLog() {}
};

#endif // !IWRITELOG_H