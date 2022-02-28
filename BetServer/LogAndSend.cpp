#include "LogAndSend.h"

// Функция логирования событий 
void saveLog(    const std::string message,
	             IWriteLog& typeLog)
{
	typeLog.writeLog(message); // время события фиксируется в логирующем классе
}

// Отправляет сообщение пользователю и сохраняет логи
void eventAndLog(uwebsock_t* ws,
	             const std::string logMsg,
	             const std::string userMsg,
	             IWriteLog& typeLog)
{
	// Записываем логи в файл
	saveLog(logMsg, typeLog);

	// Конвертируем строку для ответа пользователю в UTF-8
	StringConverter strConvert(userMsg);
	std::string eventMsg = strConvert.w1251ToUtf8();

	// Отправляем сообщение пользователю
	ws->send(eventMsg, uWS::OpCode::TEXT);
}
