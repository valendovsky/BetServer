#include "FileLog.h"

// Сохраняет логи в файл
void FileLog::writeLog(const std::string& message) const
{
	Timer time;

	// Формируем сообщение логирования
	std::string logMsg = time.getFullDate() + message;

	// Записываем логи в файл
	IWriteLog::writeLog(logMsg);
}
