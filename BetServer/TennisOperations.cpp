#include "TennisOperations.h"

// Проверяет, что игра открыта
bool TennisOperations::examGameID()
{
	// Если игра не открыта, получаем пустую строку ID
	if (m_data->workGame.getGameId() != "")
		return true; // есть открытая игра
	else
	{
		// Пользователь ещё не выбрал игру
		// Формируем сообщения
		std::string logCMD = m_header + TennisPhrase::TENNIS_NOT_CMD;

		// Лог и сообщение, что игра не открыта
		FileLog toFile;
		eventAndLog(m_ws, logCMD, TennisPhrase::TENNIS_NOT_CHOOSE, toFile);

		return false;
	}
}

// Проверяет переменную на несоответствие значению
template <typename T>
bool examValue(T value,	T testValue)
{
	if (value != testValue)
	{
		// Значения не равны, отлично
		return true;
	}
	else
	{
		// Значения равны, переменная не валидна
		return false;
	}
}

// Проверяет, что кнопка секундомера не нажата
bool TennisOperations::examInactivPress()
{
	// Если секундомер запущен, то true
	if (!m_data->workGame.getCurDataSet().getActivGames().getPressButton())
		return true; // отлично секундомер остановлен
	else
	{
		// Секундомер запущен
		// Формируем сообщения
		std::string logCMD = m_header + TennisPhrase::STOP_BYPOINT_CMD;

		// Лог и сообщение о необходимости вначале остановить секундомер
		FileLog toFile;
		eventAndLog(m_ws, logCMD, TennisPhrase::STOP_BYPOINT, toFile);

		return false;
	}
}

// Проверяет, что есть незавершенный сет
bool TennisOperations::examActivSet()
{
	// Проверяем что текущий сет не равен 0
	if (m_data->workGame.getCurSet())
		return true; // активный сет есть
	else
	{
		// Активного сета нет
		// Формируем сообщения
		std::string logCMD = m_header + TennisPhrase::SET_NOT_CMD;

		// Лог и сообщение, что нет открытого сета
		FileLog toFile;
		eventAndLog(m_ws, logCMD, TennisPhrase::SET_NOT_CHOOSE, toFile);

		return false;
	}
}

// Проверяет, что нет открытого гейма
bool TennisOperations::examActivGames()
{
	// Текущий гейм не равен 0
	if (m_data->workGame.getCurDataSet().getCurGames())
		return true; // гейм открыт
	else
	{
		// Активного гейма нет
		// Формируем сообщения
		std::string logCMD = m_header + TennisPhrase::GAMES_NOT_CMD;

		// Лог и сообщение, что нет открытого гейма
		FileLog toFile;
		eventAndLog(m_ws, logCMD, TennisPhrase::GAMES_NOT_CHOOSE, toFile);

		return false;
	}
}



// Обрабатывает событие авторизации пользователя
void TennisOperations::auth(const std::map<std::string, Clients>& allClients, std::map<unsigned int, PerSocketData*>& authUsers)
{
	// Протокол команды:
	// {"command": "auth", "login": "sasha", "pass": "qwerty"}

	// Распарсим event в json
	auto parsed = json::parse(m_message);

	// Начало лога для консоли
	std::string headerCMD = "User N " + std::to_string(m_data->userId);
	std::string logCMD;
	std::string forUser;

	// Определяем вид команды события
	std::string command = parsed[Cmd::COMMAND];
	if (command == AuthPhrase::AUTH)
	{
		std::string userLogin = parsed[AuthPhrase::LOGIN];
		std::string userPass = parsed[AuthPhrase::PASS];

		// Приведение логина к нижнему регистру
		StringConverter strConvert(userLogin);
		userLogin = strConvert.toLower();

		// Есть ли логин в базе
		if (allClients.find(userLogin) != allClients.end())
		{
			// Сверяем логин и пароль с базой пользователей
			m_data->auth = allClients.at(userLogin).checkPass(userPass);

			// Устанавливаем логин и статус админа, если верификация пройдена
			if (m_data->auth)
			{
				// Проверка повторной авторизации
				for (auto const element : authUsers)
				{
					if (element.second->login == userLogin)
					{
						// Закрываем и сохраняем игры старой авторизации
						TennisOperations::closeWsEndTennis(element.second);

						// Отменяем авторизацию
						element.second->auth = false;
						element.second->login = "";

						// Удаляем пользователя из списка авторизованных
						authUsers.erase(element.first);

						break;
					}
				}

				// Регистрируем пользователя
				m_data->login = allClients.at(userLogin).getLogin();
				m_data->is_admin = allClients.at(userLogin).getType();
				authUsers[m_data->userId] = m_data;
			}

			// Формируем сообщения о результатах авторизации
			std::string result;
			if (m_data->auth)
			{
				result = "TRUE.";
				headerCMD = headerCMD + " (login: " + m_data->login + ")";
				forUser = AuthPhrase::AUTH_TRUE;
			}
			else // пара логин/пароль неверна
			{
				result = "FALSE.";
				forUser = AuthPhrase::AUTH_FALSE;
			}

			logCMD = headerCMD + AuthPhrase::AUTH_CMD + result;
		}
		else // логина в базе нет
		{
			// Формируем сообщения о неуспешной авторизации
			logCMD = headerCMD + AuthPhrase::AUTH_CMD + "FALSE.";
			forUser = AuthPhrase::AUTH_FALSE;
		}
	}
	else // Без верификации другие команды не принимаются
	{
		// Формируем сообщения
		logCMD = headerCMD + AuthPhrase::NOT_AUTH_CMD;
		forUser = AuthPhrase::NOT_AUTH;
	}

	// Лог и сообщение о результатах верификации
	ScreenFileLog toFileScreen;
	eventAndLog(m_ws, logCMD, forUser, toFileScreen);
}

// Определяет вид события
std::string TennisOperations::getCommand()
{
	// Распарсим event в json
	auto parsed = json::parse(m_message);

	// Определяем вид команды события
	std::string command = parsed[Cmd::COMMAND];

	return command;
}

// Закрепляет теннисную игру за пользователем для разбора
void TennisOperations::commandSetTennis()
{
	// Протокол команды:
	// {"command": "tennis", "tennis_id": "idGame"}

	// Распарсим событие в json
	auto parsed = json::parse(m_message);
	// ID инициализированной игры
	std::string gameId = parsed[Cmd::TENNIS_ID];

	// Сообщения логирования
	std::string logCMD;
	std::string forUser;

	// Каскадная проверка необходимых условий
	bool exam = false;
	exam = (m_data->workGame.getGameId() == ""); // игра не открыта?
	if (exam)
	{
		// Нет активных игр
		if (m_tennisGame.find(gameId) != m_tennisGame.end()) // Id игры есть в базе?
		{
			exam = (m_data->login == m_tennisGame.at(gameId).getWorker()); // этот пользователь назначен админом?
			if (exam)
			{
				// Пользователь выбрал свою игру, открываем в работу
				m_data->workGame = TennisMatch(m_tennisGame.at(gameId));

				// Формируем сообщения, что игра закреплена за пользователем
				logCMD = m_header + TennisPhrase::GAME_SET_CMD + gameId;

				// Определяем игроков с разделителем
				std::string players = m_data->workGame.getPlayHome() + "::" + m_data->workGame.getPlayAway();
				forUser = TennisPhrase::GAME_IS_SET_1 + players + TennisPhrase::GAME_IS_SET_2 + players + TennisPhrase::GAME_IS_SET_3
					+ gameId + TennisPhrase::GAME_IS_SET_4 + m_data->workGame.forUser() + TennisPhrase::GAME_IS_SET_5;
			}
			else // некорректный ID игры (или игра закреплена за другим пользователем)
			{
				// Формируем сообщения о введении некорректного ID игры
				logCMD = m_header + TennisPhrase::INCORRECT_GAME_CMD;
				forUser = TennisPhrase::INCORRECT_GAME_ID;
			}
		}
		else // id игры отсутствует в базе
		{
			// Формируем сообщения о введении некорректного ID игры
			logCMD = m_header + TennisPhrase::INCORRECT_GAME_CMD;
			forUser = TennisPhrase::INCORRECT_GAME_ID;
		}
	}
	else // у пользователя уже открыта игра
	{
		// Формируем сообщения о необходимости завершить открытую игру
		logCMD = m_header + TennisPhrase::CLOSE_TENNIS_CMD;
		forUser = TennisPhrase::CLOSE_TENNIS;
	}

	// Лог и сообщение пользователю
	FileLog toFile;
	eventAndLog(m_ws, logCMD, forUser, toFile);
}

// Открывает сет для работы
void TennisOperations::commandSetSet()
{
	// Протокол команды:
	// {"command": "set_set", "set_num": 1, "side_play": "true/false"}

	// Сообщения логирования
	std::string logCMD;
	std::string forUser;

	// Каскадная проверка необходимых условий
	bool exam = false;
	exam = TennisOperations::examGameID(); // игра открыта?
	if (exam)
	{
		// Распарсим событие в json
		auto parsed = json::parse(m_message);
		std::string convertStr = parsed[Cmd::SET_NUM];
		std::stringstream convert;

		// Номер сета в std::string
		convert << convertStr;
		int setNum;
		convert >> setNum;

		// Очищаем и сбрасываем флаги ошибок
		convert.str("");
		convert.clear();

		// Подающая сторона должна быть выбрана обязательно (true или false)
		convertStr = parsed[Cmd::SIDE_PLAY];
		std::string emptyStr = "";
		exam = examValue(convertStr, emptyStr) && (setNum != 0); // сет должен быть выбран (не равен 0)
		if (exam)
		{
			// Подающий игрок в std::string
			convert << convertStr;
			bool player;
			convert >> player;

			exam = !m_data->workGame.getCurSet(); // открытый сет отсутствует (= 0)?
			if (exam)
			{
				// Активных сетов нет

				// Проверяем есть ли этот сет уже в статистике и валидность номера сета
				if (m_data->workGame.checkSet(setNum))
				{
					// Cет сыгран, его вначале необходимо отменить
					// Формируем сообщения
					logCMD = m_header + TennisPhrase::COMPL_SET_CMD + std::to_string(setNum);
					forUser = TennisPhrase::COMPLET_SET;
				}
				else // сет не игрался
				{
					// Открываем этот сет для работы
					m_data->workGame.setSetNum(setNum, player);

					// Формируем сообщения, что сет выбран
					if (player)
					{
						logCMD = m_header + TennisPhrase::CHOSEN_SET_CMD + std::to_string(setNum) 
							+ TennisPhrase::CHOOSE_PLAYER_CMD + m_data->workGame.getPlayHome() + " (play home).";
						forUser = TennisPhrase::CHOOSE_PLAYER_HOME + std::to_string(setNum) + TennisPhrase::CHOOSE_PLAYER_END;
					}
					else
					{
						logCMD = m_header + TennisPhrase::CHOSEN_SET_CMD + std::to_string(setNum) 
							+ TennisPhrase::CHOOSE_PLAYER_CMD + m_data->workGame.getPlayAway() + " (play away).";
						forUser = TennisPhrase::CHOOSE_PLAYER_AWAY + std::to_string(setNum) + TennisPhrase::CHOOSE_PLAYER_END;
					}
				}
			}
			else // когда есть активный сет
			{
				// Формируем сообщения, что вначале надо завершить текущий сет
				logCMD = m_header + TennisPhrase::ALREADY_SET_CMD;
				forUser = TennisPhrase::ALREADY_SET + std::to_string(m_data->workGame.getCurSet());
			}
		}
		else // обязательный элемент не валидный
		{
			// Формируем сообщения
			logCMD = m_header + TennisPhrase::NOT_VALID_CMD;
			forUser = TennisPhrase::NOT_VALID;
		}

		// Лог и сообщение пользователю
		FileLog toFile;
		eventAndLog(m_ws, logCMD, forUser, toFile);
	}
}

// Отменяет сет
void TennisOperations::commandCancelSet()
{
	// Протокол команды:
	// {"command": "cancel_set", "set_num": 1, "cancel_message": "Сет так себе!"(опционно)}

	// Распарсим событие в json
	auto parsed = json::parse(m_message);

	std::string convertStr = parsed[Cmd::SET_NUM];
	// Номер сета в std::string
	std::stringstream convert;
	int setNum;
	convert << convertStr;
	convert >> setNum;

	std::string cancelMessage = parsed[Cmd::CANCEL_MESSAGE];
	// Если строка комментария не пустая, конвертируем ее в формать Windows 1251
	std::string emptyStr = "";
	if (examValue(cancelMessage, emptyStr))
	{
		StringConverter strConvert(cancelMessage);
		cancelMessage = strConvert.utf8ToW1251();
	}

	// Каскадная проверка необходимых условий
	bool exam = false;
	exam = TennisOperations::examGameID(); // игра открыта?
	if (exam)
	{
		int testSetNum = m_data->workGame.getCurSet(); // текущий сет
		exam = testSetNum; // если сет открыт (!= 0)

		if (exam && testSetNum == setNum) // отменяется текущий открытый сет
		{
			// Сет открыт
			exam = m_data->workGame.getCurDataSet().getCurGames(); // если гейм открыт (!= 0)
			if (exam)
			{
				// Гейм открыт
				exam = TennisOperations::examInactivPress(); // секундомер не активирован?
				if (exam)
					// Обработка отмены сета (с условием)
					TennisOperations::ifCancelSet(setNum, cancelMessage);
			}
			else // когда гейм закрыт
			{
				// Обработка отмены сета (с условием)
				TennisOperations::ifCancelSet(setNum, cancelMessage);
			}
		}
		else // когда сет закрыт или отменяется не текущий
		{
			// Обработка отмены сета (с условием)
			TennisOperations::ifCancelSet(setNum, cancelMessage);
		}
	}
}

// Обрабатывает условия отмены сета
void TennisOperations::ifCancelSet(const int setNum, const std::string& message)
{
	std::string logCMD;
	std::string forUser;

	// Если сет есть в m_dataSet (игрался), то != 0
	if (m_data->workGame.checkSet(setNum))
	{
		// Если сет сигнальный или уже в архиве, то отменять нельзя

		std::string signal = m_data->workGame.getDataSet(setNum).getSignal(); // какой сигнал
		int setNumArch = m_data->workGame.getSetNumArch(); // номер последнего сета отправленного в архив

		if (signal == ComPhr::HOME || signal == ComPhr::AWAY || setNum <= setNumArch)
		{
			// Формируем сообщения, что сигнальный или архивный сет отменить нельзя
			logCMD = m_header + TennisPhrase::SIGNAL_SET_CMD + std::to_string(setNum);
			forUser = TennisPhrase::SIGNAL_SET;
		}
		else
		{
			// Отменяем не сигнальный сет
			m_data->workGame.cancelSet(setNum, message);

			// Формируем сообщения об отмене этого сета
			if (m_data->workGame.getCurSet() == 0)
			{
				// Когда удалили текущий сет
				logCMD = m_header + TennisPhrase::CANC_SET_CMD + std::to_string(setNum);
				forUser = TennisPhrase::CANCELED_SET + std::to_string(setNum) + TennisPhrase::CANCELED_SET_END;
			}
			else
			{
				// Удалили сет из архива (не текущий)
				logCMD = m_header + TennisPhrase::CANC_SET_CMD + std::to_string(setNum);
				forUser = TennisPhrase::CANC_SET_BASE + std::to_string(setNum) + TennisPhrase::CANC_SET_BASE_END;
			}
		}
	}
	else // если сет ещё не сыгран
	{
		// Формируем сообщения, что этот сет отменить нельзя
		logCMD = TennisPhrase::UNPLAY_SET_CMD + std::to_string(setNum);
		forUser = TennisPhrase::UNPLAYED_SET + std::to_string(setNum);
	}

	// Лог и сообщение пользователю
	FileLog toFile;
	eventAndLog(m_ws, logCMD, forUser, toFile);
}

// Фиксирует время активного мяча, открывает гейм, если требуется
void TennisOperations::commandByPoint()
{
	// Протокол команды:
	// {"command": "by_point"}

	// Каскадная проверка необходимых условий
	bool exam = false;
	exam = TennisOperations::examGameID(); // игра открыта?
	if (exam)
		exam = TennisOperations::examActivSet(); // сет открыт?
	if (exam)
	{
		std::string logCMD;
		std::string forUser;

		// Открыаем гейм, если необходимо
		if (!m_data->workGame.getCurDataSet().getCurGames()) // открытый гейм отсутствует (= 0)?
		{
			m_data->workGame.getCurDataSet().newGames();
		}

		// Обрабатываем нажатие кнопки секундомера
		m_data->workGame.getCurDataSet().getActivGames().pressing(m_comTime);

		// Формируем сообщения о положении кнопки и количестве розыгрышей
		bool position = m_data->workGame.getCurDataSet().getActivGames().getPressButton(); // положение кнопки
		if (position)
		{
			// Кнопка нажата
			logCMD = m_header + TennisPhrase::PRESS_BUT_CMD + std::to_string(position);
			forUser = TennisPhrase::PRESSED_BUTTON_OFF;
		}
		else
		{
			// Кнопка отжата
			logCMD = m_header + TennisPhrase::PRESS_BUT_CMD + std::to_string(position);
			forUser = TennisPhrase::PRESSED_BUTTON_ON;
		}

		// Лог и сообщение пользователю
		FileLog toFile;
		eventAndLog(m_ws, logCMD, forUser, toFile);
	}
}

// Меняет значение счётчика количества розыгрышей
void TennisOperations::commandSetPoint()
{
	// Протокол команды:
	// {"command": "set_point", "type_point": "increment/decrement"}

	// Каскадная проверка необходимых условий
	bool exam = false;
	exam = TennisOperations::examGameID(); // игра открыта?
	if (exam)
		exam = TennisOperations::examActivSet(); // сет открыт?
	if (exam)
		exam = TennisOperations::examActivGames(); // гейм открыт?
	if (exam)
		exam = TennisOperations::examInactivPress(); // секундомер остановлен?
	if (exam)
	{
		// Распарсим событие в json
		auto parsed = json::parse(m_message);
		std::string point = parsed[Cmd::TYPE_POINT];

		std::string logCMD;
		std::string forUser;


		if (point == ComPhr::INCREMENT)
		{
			// Увеличиваем счётчик розыгрышей и получаем их количество
			int pointNum = m_data->workGame.getCurDataSet().getActivGames().pointIncrement();

			// Формируем сообщения
			logCMD = m_header + TennisPhrase::UP_POINT_CMD + std::to_string(pointNum);
			forUser = TennisPhrase::POINT_COUNT_PREV + std::to_string(pointNum) + TennisPhrase::POINT_COUNT_END;
		}
		else // варианта для DECREMENT
		{
			// Уменьшаем счётчик розыгрышей и получаем их количество
			int pointNum = m_data->workGame.getCurDataSet().getActivGames().pointDecrement();

			// Формируем сообщения
			logCMD = m_header + TennisPhrase::DOWN_POINT_CMD + std::to_string(pointNum);
			forUser = TennisPhrase::POINT_COUNT_PREV + std::to_string(pointNum) + TennisPhrase::POINT_COUNT_END;

		}

		// Лог и сообщение
		FileLog toFile;
		eventAndLog(m_ws, logCMD, forUser, toFile);
	}
}

// Отменяет последнеий активный мяч
void TennisOperations::commandCancelPoint()
{
	// Протокол команды:
	// {"command": "cancel_point"}

	// Каскадная проверка необходимых условий
	bool exam = false;
	exam = TennisOperations::examGameID(); // игра открыта?
	if (exam)
		exam = TennisOperations::examActivSet(); // сет открыт?
	if (exam)
		exam = TennisOperations::examActivGames(); // гейм открыт?
	if (exam)
		exam = TennisOperations::examInactivPress(); // секундомер остановлен?
	if (exam)
	{
		// Обрабатываем отмену розыгрыша
		m_data->workGame.getCurDataSet().getActivGames().cancelPoint();

		// Формируем сообщения
		std::string logCMD = m_header + TennisPhrase::CANC_POINT_CMD;

		// Лог и сообщение
		FileLog toFile;
		eventAndLog(m_ws, logCMD, TennisPhrase::CANCELED_POINT, toFile);
	}
}

// Меняет значение счётчика двойных ошибок
void TennisOperations::commandDoubleFault()
{
	// Протокол команды:
	// {"command": "double_fault", "type_fault": "increment/decrement"}

	// Каскадная проверка необходимых условий
	bool exam = false;
	exam = TennisOperations::examGameID(); // игра открыта?
	if (exam)
		exam = TennisOperations::examActivSet(); // сет открыт?
	if (exam)
		exam = TennisOperations::examActivGames(); // гейм открыт?
	if (exam)
		exam = TennisOperations::examInactivPress(); // секундомер остановлен?
	if (exam)
	{
		// Распарсим событие в json
		auto parsed = json::parse(m_message);
		std::string fault = parsed[Cmd::TYPE_FAULT];

		int countDouble;
		std::string logCMD;
		std::string forUser;

		if (fault == ComPhr::INCREMENT) // увеличиваем количество ошибок
		{
			// Формируем сообщения о двойной ошибке и их текущем числе
			countDouble = m_data->workGame.getCurDataSet().getActivGames().incrFault();
			int pointNum = m_data->workGame.getCurDataSet().getActivGames().getPoint(); // количество розыгрышей

			logCMD = m_header + TennisPhrase::INCR_CMD + std::to_string(countDouble) + " and" + TennisPhrase::UP_POINT_CMD + std::to_string(pointNum);
			forUser = TennisPhrase::DOUBLE_VALUE_PREV + std::to_string(pointNum) + "::" + std::to_string(countDouble) + TennisPhrase::DOUBLE_VALUE_END;
		}
		else // уменьшенее ошибок (DECREMENT)
		{
			// Формируем сообщения об отмене двойной ошибке и их текущем числе
			countDouble = m_data->workGame.getCurDataSet().getActivGames().decrFault();
			int pointNum = m_data->workGame.getCurDataSet().getActivGames().getPoint(); // количество розыгрышей

			logCMD = m_header + TennisPhrase::DECR_CMD + std::to_string(countDouble) + " and" + TennisPhrase::DOWN_POINT_CMD + std::to_string(pointNum);
			forUser = TennisPhrase::DOUBLE_VALUE_PREV + std::to_string(pointNum) + "::" + std::to_string(countDouble) + TennisPhrase::DOUBLE_VALUE_END;
		}

		// Лог и сообщение
		FileLog toFile;
		eventAndLog(m_ws, logCMD, forUser, toFile);
	}
}

// Закрывает гейм
void TennisOperations::commandEndGames()
{
	// Протокол команды:
	// {"command": "end_games", "games_win": "true/false"}

	// Каскадная проверка необходимых условий
	bool exam = false;
	exam = TennisOperations::examGameID(); // игра открыта?
	if (exam)
		exam = TennisOperations::examActivSet(); // сет открыт?
	if (exam)
		exam = TennisOperations::examActivGames(); // гейм открыт?
	if (exam)
		exam = TennisOperations::examInactivPress(); // секундомер остановлен?
	if (exam)
	{
		std::string logCMD;
		std::string forUser;
		FileLog toFile;

		// Распарсим событие в json
		auto parsed = json::parse(m_message);
		std::string convertStr = parsed[Cmd::GAMES_WIN];

		// Значение в GAMES_WIN не должно быть пустым (обязательное значение)
		std::string emptyStr = "";
		exam = examValue(convertStr, emptyStr);
		if (exam)
		{
			std::stringstream convert;

			convert << convertStr;
			bool winner;
			convert >> winner;

			// Закрываем гейм
			exam = m_data->workGame.getCurDataSet().endGames(winner); // надо закрывать и сет?
			// Сет закрываем тоже
			if (exam)
			{
				TennisOperations::endSet(TennisPhrase::AUTO_CLOSE, m_data);
			}
			else // продолжаем игру
			{
				// Формируем сообщения о завершении гейма и счёте
				std::string score = m_data->workGame.getCurDataSet().getScore(); // счёт в сете
				std::string playerWinner;
				if (winner)
					playerWinner = m_data->workGame.getPlayHome();               // игрок 1 (дома)
				else
					playerWinner = m_data->workGame.getPlayAway();               // игрок 2 (на выезде)

				// Определяем подающего
				std::string curPlayer;
				if (m_data->workGame.getCurDataSet().getCurPlayer())
					curPlayer = TennisPhrase::GAME_HOME;
				else
					curPlayer = TennisPhrase::GAME_AWAY;

				// Формируем сообщения
				logCMD = m_header + TennisPhrase::FINISH_GAME_CMD + score + TennisPhrase::WINNER_CMD + playerWinner;
				forUser = TennisPhrase::FINISH_GAME_1 + curPlayer + score + TennisPhrase::FINISH_GAME_2 + playerWinner + TennisPhrase::FINISH_GAME_3;

				// Лог и сообщение
				eventAndLog(m_ws, logCMD, forUser, toFile);

				// Сообщение о предварительном сигнале, если потребуется
				TennisOperations::prevSignal(score);
			}
		}
		else // обязательный элемент не валидный
		{
			// Формируем сообщения
			logCMD = m_header + TennisPhrase::NOT_VALID_CMD;

			// Лог и сообщение, что игра не открыта
			eventAndLog(m_ws, logCMD, TennisPhrase::WIN_NOT_VALID, toFile);
		}
	}
}

// Закрывает сет
void TennisOperations::endSet(const std::string& message, PerSocketData* data, bool printMode)
{
	// Сохраняем номер сета
	int setNum = data->workGame.getCurSet();

	// Закрываем сет
	std::string signal = data->workGame.endSetGetSignal(message);

	std::string logCMD;
	std::string forUser;

	// Определяем как выводить логи
	ScreenFileLog toFileScreen;
	FileLog toFile;
	IWriteLog* typeLog = &toFileScreen;

	if (signal == ComPhr::NONE)
	{
		// Нет сигнала
		// Формируем сообщение лога, что нет сигнала
		std::string header;
		if (m_data->login != data->login)
		{
			// При автоматическом закрытии сессии
			header = "User N " + std::to_string(m_data->userId) + " (login: " 
				+ data->login + ", old user N " + std::to_string(data->userId) + ")";
		}
		else
			header = m_header;

		logCMD = header + TennisPhrase::NONE_SIGNAL_CMD + std::to_string(setNum);

		// Не выводить лог на экран
		typeLog = &toFile;
	}
	else
	{
		// Получаем информацию для сообщения
		std::string tour = data->workGame.getTour();
		std::string homePlayer = data->workGame.getPlayHome();
		std::string awayPlayer = data->workGame.getPlayAway();
		std::string winner;

		// Определяем победителя
		if (signal == ComPhr::HOME)
			winner = homePlayer;
		else if (signal == ComPhr::AWAY)
			winner = awayPlayer;
		else
			winner = ComPhr::NONE; // для подстраховки


		// Отправляем сигнал на сервер и в Телеграм-бот:
		std::string channel = TgBot::SIGNAL_CHANNEL; // для тестов заменить SIGNAL_CHANNEL на TEST_CHANNEL

		// Получаем московское время (локальное время сервера)
		Timer time;
		std::string timeMsk = time.getTime() + " Msk";

		// Формируем опции для Телеграм-бота
		std::string signalMessage = "My message"; // Сформируйте своё сообщение!

		// Отправляем сообщение в Телеграм-бот 
		TennisOperations::sendSignal(signalMessage);

		// Формируем сообщение для лога
		logCMD = m_header + TennisPhrase::HAVE_SIGNAL + " My message options"; // Сформируйте свои дополнительные опции!
	}

	// Только сохраняем логи (файл и на экран) или ещё отправляем сообщение пользователю
	if (printMode)
	{
		// Формируем сообщение пользователю
		forUser = TennisPhrase::END_SET_PREV + std::to_string(setNum) + TennisPhrase::END_SET_END;

		// Записываем в файл и выводим на экран, отправляем сообщение пользователю
		eventAndLog(m_ws, logCMD, forUser, *typeLog);
	}
	else // для автоматического дисконекта в .close
	{
		ScreenFileLog toFileScreen;
		saveLog(logCMD, toFileScreen);
	}
}

// Передаёт сообщения Telegram-боту
void TennisOperations::sendSignal(std::string& optionsCMD)
{
	// Создаём команду для cmd в формате:
	//system("cd C:\\Users\\каталог_с_Telegram-ботом & start python.exe tgbot.py 'опции_для_бота'");
	std::string commandCMD = "cd " + CATALOG_SERVER + CALL_TG_BOT + optionsCMD;

	system(commandCMD.c_str());
}

// Функция определения необходимости предварительного сигнала
void TennisOperations::prevSignal(const std::string& score)
{
	// Условие предварительного сигнала
	if (score == "") // Укажите ваше условие!
	{
		// Формируем сообщение для Телеграм-бота
		std::string tour = m_data->workGame.getTour();
		std::string homePlayer = m_data->workGame.getPlayHome();
		std::string awayPlayer = m_data->workGame.getPlayAway();
		int setNum = m_data->workGame.getCurSet();

		// Сообщение, что сигнал предварительный
		std::string prevMsg = TgBot::SIGNAL_PREVIEW;

		// Указатель канала для отправки
		std::string channel = TgBot::PREVIEW_CHANNEL; // для тестов заменить PREVIEW_CHANNEL на TEST_CHANNEL

		// Получаем московское время (локальное время сервера)
		Timer time;
		std::string timeMsk = time.getTime() + " Msk";

		std::string signalMessage = "My options " + prevMsg + "/ my options."; // Сформируйте своё сообщение!

		// Отправляем сообщение в Телеграм-бот 
		TennisOperations::sendSignal(signalMessage);

		// Лог в файл и на экран о предварительном сигнале
		std::string logCMD = m_header + TennisPhrase::PREV_SIGN_CMD + " My message options"; // Сформируйте свои опции к сообщению
		ScreenFileLog toFileScreen;
		saveLog(logCMD, toFileScreen);
	}
}

// Завершает сет
void TennisOperations::commandEndSet()
{
	// Протокол команды:
	// {"command": "end_set", "end_message": "Сет норм!"}

	// Каскадная проверка необходимых условий
	bool exam = false;
	exam = TennisOperations::examGameID(); // игра открыта?
	if (exam)
		exam = TennisOperations::examActivSet(); // сет открыт?
	if (exam)
	{
		// Распарсим событие в json
		auto parsed = json::parse(m_message);
		std::string endMessage = parsed[Cmd::END_MESSAGE];

		// Если строка не пустая конвертируем ее в формать Windows 1251
		std::string emptyStr = "";
		if (examValue(endMessage, emptyStr))
		{
			StringConverter strConvert(endMessage);
			endMessage = strConvert.utf8ToW1251();
		}

		std::string logCMD;

		exam = m_data->workGame.getCurDataSet().getCurGames(); // гейм открыт? (!=0)
		if (exam)
		{
			// Удаляем текущий открытый гейм
			m_data->workGame.getCurDataSet().cancelCurGames();

			// Сохраняем логи об отмене текущего гейма
			logCMD = m_header + TennisPhrase::CANC_GAMES;
			FileLog toFile;
			saveLog(logCMD, toFile);
		}

		// Закрываем сет
		TennisOperations::endSet(endMessage, m_data);
	}
}

// Закрывает игру и сохраняет статистику
void TennisOperations::commandEndTennis()
{
	// Протокол команды:
	// {"command": "end_tennis", "type_end": "interim/totally"}

	// Каскадная проверка необходимых условий
	bool exam = false;
	exam = TennisOperations::examGameID(); // игра открыта?
	if (exam)
	{
		std::string logCMD;

		// Распарсим событие в json
		auto parsed = json::parse(m_message);
		std::string typeEnd = parsed[Cmd::TYPE_END];

		// Проверка на наличие обязательного элемента команды
		std::string emptyStr = "";
		exam = examValue(typeEnd, emptyStr);
		if (exam)
		{
			exam = !m_data->workGame.getCurSet(); // если сет закрыт (= 0)
			if (exam)
			{
				// Сохраняем и закрываем игру, отправляем сообщения
				TennisOperations::closeTennis(typeEnd, m_data);
			}
			else // сет открыт
			{
				// Формируем сообщение, что необходимо закрыть сет
				logCMD = m_header + TennisPhrase::FINISH_SET_CMD;

				// Лог и сообщение пользователю
				FileLog toFile;
				eventAndLog(m_ws, logCMD, TennisPhrase::FINISH_SET, toFile);
			}
		}
		else // обязательный элемент не валидный
		{
			// Формируем сообщения
			logCMD = m_header + TennisPhrase::NOT_VALID_CMD;

			// Лог и сообщение пользователю, что игра не открыта
			FileLog toFile;
			eventAndLog(m_ws, logCMD, TennisPhrase::NOT_VALID_SAVE, toFile);
		}
	}
}

// Закрывает и сохраняет игру
void TennisOperations::closeTennis(const std::string& typeEnd, PerSocketData* data,	bool printMode)
{
	// Флаги о закрытие игры
	data->workGame.endTennis(typeEnd);

	std::string logCMD;
	std::string forUser;

	// Сохранение статистики
	std::string gameId = data->workGame.getGameId();
	if (typeEnd == ComPhr::TOTALLY) // итоговое сохранение
	{
		// Сохраняем в архив
		m_tennisArchive[gameId] = data->workGame;

		// Удаляем игру из открытой
		data->workGame = TennisMatch();

		// Удаляем игру из базы игр для работы
		m_tennisGame.erase(gameId);
	}
	else // промежуточное сохранение
	{
		// Сохраняем в архив
		m_tennisArchive[gameId] = data->workGame;

		// Удаляем игру из открытой
		data->workGame = TennisMatch();
	}

	// Сохраняем статистику в файл
	bool saveResult = TennisOperations::saveTennis(gameId);

	// Сохранение комментариев к отмененным сетам
	bool cancelResult = TennisOperations::saveCanselReport(gameId);

	// Формируем доп сообщения о сохранении отменённых сетов
	std::string logCMDplus;
	std::string forUserplus;
	if (cancelResult)
	{
		// Успешное сохранение отчёта
		logCMDplus = TennisPhrase::CANS_REP_CMD;
		forUserplus = TennisPhrase::CANS_REP;
	}
	else
	{
		// Сохранить отчёт не удалось
		logCMDplus = TennisPhrase::CANS_REP_FAIL_CMD;
		forUserplus = TennisPhrase::CANS_REP_FAIL;
	}


	// Проверка успешности сохранения
	std::string resCMD;
	std::string resUser;
	if (saveResult)
	{
		resCMD = TennisPhrase::SUCCESS;
		resUser = TennisPhrase::SUCCESS_USER;
	}
	else
	{
		resCMD = TennisPhrase::FAIL;
		resUser = TennisPhrase::FAIL_USER;
	}

	// Формируем сообщения о результатах закрытия игры
	std::string header;
	if (m_data->login != data->login)
	{
		// Автоматическое закрытие
		header = "User N " + std::to_string(m_data->userId) + " (login: " + data->login 
			+ ", old user N " + std::to_string(data->userId) + ")";
	}
	else
		header = m_header;

	logCMD = header + TennisPhrase::SAVE_RESULT_CMD + resCMD + " " + logCMDplus;
	forUser = TennisPhrase::SAVE_RESULT_PREV + resUser + " " + forUserplus + TennisPhrase::SAVE_RESULT_END;

	if (printMode)
	{
		// Лог и сообщение пользователю
		FileLog toFile;
		eventAndLog(m_ws, logCMD, forUser, toFile);
	}
	else // для автоматического закрытия в .close
	{
		ScreenFileLog toFileScreen;
		saveLog(logCMD, toFileScreen);
	}
}

// Сохранение статистики обработанных игр в файл
bool TennisOperations::saveTennis(const std::string& gameId)
{
	/*
	* Инструкции сохранения статистики удалены.
	* Предоставьте свои команды!
	*/

	return false;
}

// Сохраняет отчёты об отмене сета в файл
bool TennisOperations::saveCanselReport(const std::string& gameId)
{
	// Название файла содержит месяц и день даты записи лога
	std::string fileOut = CANCEL_ARCHIVE + m_comTime.getMonthDay() + ".csv";

	std::ofstream out(fileOut, std::ios::app);

	// Проверяем открылся ли файл
	if (!out.is_open())
	{
		std::string logCMD = "Cancel report archiving ERROR! Game ID: " + gameId;
		ScreenFileLog toFileScreen;
		saveLog(logCMD, toFileScreen);

		return false;
	}

	// Если есть отменённые сеты в базе игры
	if (!m_tennisArchive.at(gameId).getReportCancel().empty())
	{
		for (auto element : m_tennisArchive.at(gameId).getReportCancel())
		{
			out << gameId << "," << std::to_string(element.first) << "," << element.second << std::endl;
		}
	}

	// Закрываем файл
	out.close();

	return true;
}

// Закрытие игры (INTERIM) в случае срабатывания метода .close или повторной авторизации
void TennisOperations::closeWsEndTennis(PerSocketData* data)
{
	/*
	* Используется PerSocketData* data вместо объекта класса m_data
	* по причине того, что при перелогине создаётся новое подключение к вебсерверу
	* и m_data не содержит игру прошлой авторизации пользователя,
	* и все данные связаны с прошлым подключением к вебсерверу
	*/

	// Если игра ещё открыта
	if (data->workGame.getGameId() != "")
	{
		// Записываем логи
		std::string logMsg = "Automatic closing of the game of the user with the LOGIN: " + data->login;
		ScreenFileLog toFileScreen;
		saveLog(logMsg, toFileScreen);

		if (data->workGame.getCurSet()) // текущий сет != 0, значит сет окрыт
		{
			if (data->workGame.getCurDataSet().getCurGames()) // текущий гейм != 0, значит гейм окрыт
			{
				// Удаляем гейм
				data->workGame.getCurDataSet().cancelCurGames();

				// Сохраняем логи
				logMsg = "The game is removed automatically.";
				ScreenFileLog toFileScreen;
				saveLog(logMsg, toFileScreen);
			}

			// Закрываем сет и сохраняем логи
			TennisOperations::endSet(TennisPhrase::AUTO_CLOSE, data, false); // false - только сохраняем логи
		}

		// Сохраняем и закрываем игру
		TennisOperations::closeTennis(ComPhr::INTERIM, data, false); // false - только сохраняем логи
	}
	else
	{
		// Записываем логи
		std::string logMsg = "The game was saved earlier.";
		ScreenFileLog toFileScreen;
		saveLog(logMsg, toFileScreen);
	}
}
