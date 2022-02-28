#include "FileLog.h"

// ��������� ���� � ����
void FileLog::writeLog(const std::string& message) const
{
	Timer time;

	// ��������� ��������� �����������
	std::string logMsg = time.getFullDate() + message;

	// ���������� ���� � ����
	IWriteLog::writeLog(logMsg);
}
