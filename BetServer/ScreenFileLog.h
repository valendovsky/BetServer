#ifndef SCREENFILELOG_H
#define SCREENFILELOG_H

#include <iostream>
#include <string>

#include "IWriteLog.h"
#include "Timer.h"


// ����� ��� ������ ����� �� ����� � ���������� � ����
class ScreenFileLog : public IWriteLog
{
public:
	virtual void writeLog(const std::string& message) const override;

	// ����������� ����������
	virtual      ~ScreenFileLog() {}
};

#endif // !SCREENFILELOG_H