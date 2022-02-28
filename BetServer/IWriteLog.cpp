#include "IWriteLog.h"


// ������� �� ��������� ��� ����������� �������
void IWriteLog::writeLog(const std::string& message) const
{
	Timer time;

	// �������� ����� �������� ����� � ���� ���� ������ ����
	std::string fileOut = LOG_FILE + time.getMonthDay() + ".txt";

	// ��������� � ������ ��������
	std::ofstream logOut(fileOut, std::ios::app);

	if (!logOut.is_open())
	{
		// ���� ���� �� ������� �������, ������� ��������� �� �����
		std::cerr << time.getFullDate() << "ERROR OPENING A LOG FILE! Message:" << std::endl;
		std::cerr << message << std::endl;

		return;
	}

	logOut << message << std::endl;

	logOut.close();
}
