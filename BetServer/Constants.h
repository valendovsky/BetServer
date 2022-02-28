#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>


// �������� ������
// ���� � �������������� �������
const std::string USER_DATA = "FileData\\UserData.csv";

// ���� ���������� ���
const std::string TENNIS_GAME = "FileData\\TennisData.csv";

// ���� ������������ ��� (�������� ��� ���������)
const std::string TENNIS_ARCHIVE = "TennisResult\\TennisArchive_";

// ���� ��� ������������ � ���������� �����
const std::string CANCEL_ARCHIVE = "TennisResult\\CanselArchive_";

// ���� ��� ���������� ����� ������� (���������)
const std::string LOG_FILE = "LogData\\Log_";

// ���� ������� ��������
const std::string TENNIS_HTML = "HTML\\tennis.htm";

// ������������ ��������-����
const std::string CATALOG_SERVER = "C:\\tgbot"; // ������� ���� �����!

// ������ ��������-���� � ��������� ����
const std::string CALL_TG_BOT = " & start python.exe tgbot.py ";


// ���������
const int    g_port = 3001;                // ������� ���� ����!
/* ����� �������� ������� */
const double g_timeFault = 0.0;            // ����� ��� ������� ������
const int    g_score = 1;                  // ���� � ������ (������ �� ����� 0)
/* ����� �������� ������� */


// ����� ����������� ��������� ��� ������ ������ � �������
namespace ComPhr
{
	const std::string INCREMENT = "increment";
	const std::string DECREMENT = "decrement";

	const std::string HOME = "home";
	const std::string AWAY = "away";
	const std::string NONE = "none";

	const std::string NO_SAVE = "no_save";
	const std::string INTERIM = "interim";
	const std::string TOTALLY = "totally";

}


// ��������� ��� ��������-����
namespace TgBot
{
	// ������ ��� ��������-����
	const std::string TEST_CHANNEL =    "0"; // �������� �����
	const std::string SIGNAL_CHANNEL =  "1"; // ����� ��� ��������
	const std::string PREVIEW_CHANNEL = "2"; // ����� ��������������
	const std::string SIGNAL_PREVIEW =  "������� ����������� ������� � �����:";

}

#endif // !CONSTANTS_H