#include "ScreenFileLog.h"

// ������� ���� �� ����� � ��������� � ����
void ScreenFileLog::writeLog(const std::string& message) const
{
	Timer time;

	// ��������� ��������� �����������
	std::string logMsg = time.getFullDate() + message;

	// ������� ��������� �� �����
	std::cout << logMsg << std::endl;

	// ���������� ���� � ����
	IWriteLog::writeLog(logMsg);
}
