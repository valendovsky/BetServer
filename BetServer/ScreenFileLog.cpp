#include "ScreenFileLog.h"

// Выводит логи на экран и сохраняет в файл
void ScreenFileLog::writeLog(const std::string& message) const
{
	Timer time;

	// Формируем сообщение логирования
	std::string logMsg = time.getFullDate() + message;

	// Выводим сообщение на экран
	std::cout << logMsg << std::endl;

	// Записываем логи в файл
	IWriteLog::writeLog(logMsg);
}
