#include "LogAndSend.h"

// ������� ����������� ������� 
void saveLog(    const std::string message,
	             IWriteLog& typeLog)
{
	typeLog.writeLog(message); // ����� ������� ����������� � ���������� ������
}

// ���������� ��������� ������������ � ��������� ����
void eventAndLog(uwebsock_t* ws,
	             const std::string logMsg,
	             const std::string userMsg,
	             IWriteLog& typeLog)
{
	// ���������� ���� � ����
	saveLog(logMsg, typeLog);

	// ������������ ������ ��� ������ ������������ � UTF-8
	StringConverter strConvert(userMsg);
	std::string eventMsg = strConvert.w1251ToUtf8();

	// ���������� ��������� ������������
	ws->send(eventMsg, uWS::OpCode::TEXT);
}
