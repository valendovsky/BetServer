#include "IWriteLog.h"


// Функция по умолчанию для логирования событий
void IWriteLog::writeLog(const std::string& message) const
{
	Timer time;

	// Название файла содержит месяц и день даты записи лога
	std::string fileOut = LOG_FILE + time.getMonthDay() + ".txt";

	// Открываем в режиме дозаписи
	std::ofstream logOut(fileOut, std::ios::app);

	if (!logOut.is_open())
	{
		// Если файл не удалось открыть, выводим сообщение на экран
		std::cerr << time.getFullDate() << "ERROR OPENING A LOG FILE! Message:" << std::endl;
		std::cerr << message << std::endl;

		return;
	}

	logOut << message << std::endl;

	logOut.close();
}
