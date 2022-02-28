#ifndef LOGANDSEND_H
#define LOGANDSEND_H

#include <string>
#include <uwebsockets/App.h>

#include "PerSocketData.h"
#include "IWriteLog.h"
#include "FileLog.h"
#include "ScreenFileLog.h"
#include "StringConverter.h"

// ���������� ��� �������� ������ � WebSocket
using uwebsock_t = uWS::WebSocket<false, true, PerSocketData>;


// ������� ����������� ������� 
void saveLog(    const std::string message,
	             IWriteLog& typeLog);

// ���������� ��������� ������������ � ��������� ����
void eventAndLog(uwebsock_t* ws,
	             const std::string logMsg,
	             const std::string userMsg,
	             IWriteLog& typeLog);

#endif // !LOGANDSEND_H