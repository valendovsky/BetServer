#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>


// Названия файлов
// Файл с пользователями сервера
const std::string USER_DATA = "FileData\\UserData.csv";

// Файл спарсенных игр
const std::string TENNIS_GAME = "FileData\\TennisData.csv";

// Файл отработанных игр (частично или полностью)
const std::string TENNIS_ARCHIVE = "TennisResult\\TennisArchive_";

// Файл для комментариев к отмененным играм
const std::string CANCEL_ARCHIVE = "TennisResult\\CanselArchive_";

// Файл для сохранения логов сервера (приставка)
const std::string LOG_FILE = "LogData\\Log_";

// Файл рабочей страницы
const std::string TENNIS_HTML = "HTML\\tennis.htm";

// Расположения Телеграм-бота
const std::string CATALOG_SERVER = "C:\\tgbot"; // Укажите свой адрес!

// Запуск Телеграм-бота в отдельном окне
const std::string CALL_TG_BOT = " & start python.exe tgbot.py ";


// Константы
const int    g_port = 3001;                // Укажите свой порт!
/* Часть констант удалено */
const double g_timeFault = 0.0;            // время для двойной ошибки
const int    g_score = 1;                  // счёт в геймах (строго не равно 0)
/* Часть констант удалено */


// Общие константные выражения для разных команд и классов
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


// Константы для Телеграм-бота
namespace TgBot
{
	// Каналы для Телеграм-бота
	const std::string TEST_CHANNEL =    "0"; // тестовый канал
	const std::string SIGNAL_CHANNEL =  "1"; // канал для сигналов
	const std::string PREVIEW_CHANNEL = "2"; // канал предупреждений
	const std::string SIGNAL_PREVIEW =  "Высокая вероятность сигнала в матче:";

}

#endif // !CONSTANTS_H