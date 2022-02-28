#include "TennisOperations.h"

// ���������, ��� ���� �������
bool TennisOperations::examGameID()
{
	// ���� ���� �� �������, �������� ������ ������ ID
	if (m_data->workGame.getGameId() != "")
		return true; // ���� �������� ����
	else
	{
		// ������������ ��� �� ������ ����
		// ��������� ���������
		std::string logCMD = m_header + TennisPhrase::TENNIS_NOT_CMD;

		// ��� � ���������, ��� ���� �� �������
		FileLog toFile;
		eventAndLog(m_ws, logCMD, TennisPhrase::TENNIS_NOT_CHOOSE, toFile);

		return false;
	}
}

// ��������� ���������� �� �������������� ��������
template <typename T>
bool examValue(T value,	T testValue)
{
	if (value != testValue)
	{
		// �������� �� �����, �������
		return true;
	}
	else
	{
		// �������� �����, ���������� �� �������
		return false;
	}
}

// ���������, ��� ������ ����������� �� ������
bool TennisOperations::examInactivPress()
{
	// ���� ���������� �������, �� true
	if (!m_data->workGame.getCurDataSet().getActivGames().getPressButton())
		return true; // ������� ���������� ����������
	else
	{
		// ���������� �������
		// ��������� ���������
		std::string logCMD = m_header + TennisPhrase::STOP_BYPOINT_CMD;

		// ��� � ��������� � ������������� ������� ���������� ����������
		FileLog toFile;
		eventAndLog(m_ws, logCMD, TennisPhrase::STOP_BYPOINT, toFile);

		return false;
	}
}

// ���������, ��� ���� ������������� ���
bool TennisOperations::examActivSet()
{
	// ��������� ��� ������� ��� �� ����� 0
	if (m_data->workGame.getCurSet())
		return true; // �������� ��� ����
	else
	{
		// ��������� ���� ���
		// ��������� ���������
		std::string logCMD = m_header + TennisPhrase::SET_NOT_CMD;

		// ��� � ���������, ��� ��� ��������� ����
		FileLog toFile;
		eventAndLog(m_ws, logCMD, TennisPhrase::SET_NOT_CHOOSE, toFile);

		return false;
	}
}

// ���������, ��� ��� ��������� �����
bool TennisOperations::examActivGames()
{
	// ������� ���� �� ����� 0
	if (m_data->workGame.getCurDataSet().getCurGames())
		return true; // ���� ������
	else
	{
		// ��������� ����� ���
		// ��������� ���������
		std::string logCMD = m_header + TennisPhrase::GAMES_NOT_CMD;

		// ��� � ���������, ��� ��� ��������� �����
		FileLog toFile;
		eventAndLog(m_ws, logCMD, TennisPhrase::GAMES_NOT_CHOOSE, toFile);

		return false;
	}
}



// ������������ ������� ����������� ������������
void TennisOperations::auth(const std::map<std::string, Clients>& allClients, std::map<unsigned int, PerSocketData*>& authUsers)
{
	// �������� �������:
	// {"command": "auth", "login": "sasha", "pass": "qwerty"}

	// ��������� event � json
	auto parsed = json::parse(m_message);

	// ������ ���� ��� �������
	std::string headerCMD = "User N " + std::to_string(m_data->userId);
	std::string logCMD;
	std::string forUser;

	// ���������� ��� ������� �������
	std::string command = parsed[Cmd::COMMAND];
	if (command == AuthPhrase::AUTH)
	{
		std::string userLogin = parsed[AuthPhrase::LOGIN];
		std::string userPass = parsed[AuthPhrase::PASS];

		// ���������� ������ � ������� ��������
		StringConverter strConvert(userLogin);
		userLogin = strConvert.toLower();

		// ���� �� ����� � ����
		if (allClients.find(userLogin) != allClients.end())
		{
			// ������� ����� � ������ � ����� �������������
			m_data->auth = allClients.at(userLogin).checkPass(userPass);

			// ������������� ����� � ������ ������, ���� ����������� ��������
			if (m_data->auth)
			{
				// �������� ��������� �����������
				for (auto const element : authUsers)
				{
					if (element.second->login == userLogin)
					{
						// ��������� � ��������� ���� ������ �����������
						TennisOperations::closeWsEndTennis(element.second);

						// �������� �����������
						element.second->auth = false;
						element.second->login = "";

						// ������� ������������ �� ������ ��������������
						authUsers.erase(element.first);

						break;
					}
				}

				// ������������ ������������
				m_data->login = allClients.at(userLogin).getLogin();
				m_data->is_admin = allClients.at(userLogin).getType();
				authUsers[m_data->userId] = m_data;
			}

			// ��������� ��������� � ����������� �����������
			std::string result;
			if (m_data->auth)
			{
				result = "TRUE.";
				headerCMD = headerCMD + " (login: " + m_data->login + ")";
				forUser = AuthPhrase::AUTH_TRUE;
			}
			else // ���� �����/������ �������
			{
				result = "FALSE.";
				forUser = AuthPhrase::AUTH_FALSE;
			}

			logCMD = headerCMD + AuthPhrase::AUTH_CMD + result;
		}
		else // ������ � ���� ���
		{
			// ��������� ��������� � ���������� �����������
			logCMD = headerCMD + AuthPhrase::AUTH_CMD + "FALSE.";
			forUser = AuthPhrase::AUTH_FALSE;
		}
	}
	else // ��� ����������� ������ ������� �� �����������
	{
		// ��������� ���������
		logCMD = headerCMD + AuthPhrase::NOT_AUTH_CMD;
		forUser = AuthPhrase::NOT_AUTH;
	}

	// ��� � ��������� � ����������� �����������
	ScreenFileLog toFileScreen;
	eventAndLog(m_ws, logCMD, forUser, toFileScreen);
}

// ���������� ��� �������
std::string TennisOperations::getCommand()
{
	// ��������� event � json
	auto parsed = json::parse(m_message);

	// ���������� ��� ������� �������
	std::string command = parsed[Cmd::COMMAND];

	return command;
}

// ���������� ��������� ���� �� ������������� ��� �������
void TennisOperations::commandSetTennis()
{
	// �������� �������:
	// {"command": "tennis", "tennis_id": "idGame"}

	// ��������� ������� � json
	auto parsed = json::parse(m_message);
	// ID ������������������ ����
	std::string gameId = parsed[Cmd::TENNIS_ID];

	// ��������� �����������
	std::string logCMD;
	std::string forUser;

	// ��������� �������� ����������� �������
	bool exam = false;
	exam = (m_data->workGame.getGameId() == ""); // ���� �� �������?
	if (exam)
	{
		// ��� �������� ���
		if (m_tennisGame.find(gameId) != m_tennisGame.end()) // Id ���� ���� � ����?
		{
			exam = (m_data->login == m_tennisGame.at(gameId).getWorker()); // ���� ������������ �������� �������?
			if (exam)
			{
				// ������������ ������ ���� ����, ��������� � ������
				m_data->workGame = TennisMatch(m_tennisGame.at(gameId));

				// ��������� ���������, ��� ���� ���������� �� �������������
				logCMD = m_header + TennisPhrase::GAME_SET_CMD + gameId;

				// ���������� ������� � ������������
				std::string players = m_data->workGame.getPlayHome() + "::" + m_data->workGame.getPlayAway();
				forUser = TennisPhrase::GAME_IS_SET_1 + players + TennisPhrase::GAME_IS_SET_2 + players + TennisPhrase::GAME_IS_SET_3
					+ gameId + TennisPhrase::GAME_IS_SET_4 + m_data->workGame.forUser() + TennisPhrase::GAME_IS_SET_5;
			}
			else // ������������ ID ���� (��� ���� ���������� �� ������ �������������)
			{
				// ��������� ��������� � �������� ������������� ID ����
				logCMD = m_header + TennisPhrase::INCORRECT_GAME_CMD;
				forUser = TennisPhrase::INCORRECT_GAME_ID;
			}
		}
		else // id ���� ����������� � ����
		{
			// ��������� ��������� � �������� ������������� ID ����
			logCMD = m_header + TennisPhrase::INCORRECT_GAME_CMD;
			forUser = TennisPhrase::INCORRECT_GAME_ID;
		}
	}
	else // � ������������ ��� ������� ����
	{
		// ��������� ��������� � ������������� ��������� �������� ����
		logCMD = m_header + TennisPhrase::CLOSE_TENNIS_CMD;
		forUser = TennisPhrase::CLOSE_TENNIS;
	}

	// ��� � ��������� ������������
	FileLog toFile;
	eventAndLog(m_ws, logCMD, forUser, toFile);
}

// ��������� ��� ��� ������
void TennisOperations::commandSetSet()
{
	// �������� �������:
	// {"command": "set_set", "set_num": 1, "side_play": "true/false"}

	// ��������� �����������
	std::string logCMD;
	std::string forUser;

	// ��������� �������� ����������� �������
	bool exam = false;
	exam = TennisOperations::examGameID(); // ���� �������?
	if (exam)
	{
		// ��������� ������� � json
		auto parsed = json::parse(m_message);
		std::string convertStr = parsed[Cmd::SET_NUM];
		std::stringstream convert;

		// ����� ���� � std::string
		convert << convertStr;
		int setNum;
		convert >> setNum;

		// ������� � ���������� ����� ������
		convert.str("");
		convert.clear();

		// �������� ������� ������ ���� ������� ����������� (true ��� false)
		convertStr = parsed[Cmd::SIDE_PLAY];
		std::string emptyStr = "";
		exam = examValue(convertStr, emptyStr) && (setNum != 0); // ��� ������ ���� ������ (�� ����� 0)
		if (exam)
		{
			// �������� ����� � std::string
			convert << convertStr;
			bool player;
			convert >> player;

			exam = !m_data->workGame.getCurSet(); // �������� ��� ����������� (= 0)?
			if (exam)
			{
				// �������� ����� ���

				// ��������� ���� �� ���� ��� ��� � ���������� � ���������� ������ ����
				if (m_data->workGame.checkSet(setNum))
				{
					// C�� ������, ��� ������� ���������� ��������
					// ��������� ���������
					logCMD = m_header + TennisPhrase::COMPL_SET_CMD + std::to_string(setNum);
					forUser = TennisPhrase::COMPLET_SET;
				}
				else // ��� �� �������
				{
					// ��������� ���� ��� ��� ������
					m_data->workGame.setSetNum(setNum, player);

					// ��������� ���������, ��� ��� ������
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
			else // ����� ���� �������� ���
			{
				// ��������� ���������, ��� ������� ���� ��������� ������� ���
				logCMD = m_header + TennisPhrase::ALREADY_SET_CMD;
				forUser = TennisPhrase::ALREADY_SET + std::to_string(m_data->workGame.getCurSet());
			}
		}
		else // ������������ ������� �� ��������
		{
			// ��������� ���������
			logCMD = m_header + TennisPhrase::NOT_VALID_CMD;
			forUser = TennisPhrase::NOT_VALID;
		}

		// ��� � ��������� ������������
		FileLog toFile;
		eventAndLog(m_ws, logCMD, forUser, toFile);
	}
}

// �������� ���
void TennisOperations::commandCancelSet()
{
	// �������� �������:
	// {"command": "cancel_set", "set_num": 1, "cancel_message": "��� ��� ����!"(��������)}

	// ��������� ������� � json
	auto parsed = json::parse(m_message);

	std::string convertStr = parsed[Cmd::SET_NUM];
	// ����� ���� � std::string
	std::stringstream convert;
	int setNum;
	convert << convertStr;
	convert >> setNum;

	std::string cancelMessage = parsed[Cmd::CANCEL_MESSAGE];
	// ���� ������ ����������� �� ������, ������������ �� � ������� Windows 1251
	std::string emptyStr = "";
	if (examValue(cancelMessage, emptyStr))
	{
		StringConverter strConvert(cancelMessage);
		cancelMessage = strConvert.utf8ToW1251();
	}

	// ��������� �������� ����������� �������
	bool exam = false;
	exam = TennisOperations::examGameID(); // ���� �������?
	if (exam)
	{
		int testSetNum = m_data->workGame.getCurSet(); // ������� ���
		exam = testSetNum; // ���� ��� ������ (!= 0)

		if (exam && testSetNum == setNum) // ���������� ������� �������� ���
		{
			// ��� ������
			exam = m_data->workGame.getCurDataSet().getCurGames(); // ���� ���� ������ (!= 0)
			if (exam)
			{
				// ���� ������
				exam = TennisOperations::examInactivPress(); // ���������� �� �����������?
				if (exam)
					// ��������� ������ ���� (� ��������)
					TennisOperations::ifCancelSet(setNum, cancelMessage);
			}
			else // ����� ���� ������
			{
				// ��������� ������ ���� (� ��������)
				TennisOperations::ifCancelSet(setNum, cancelMessage);
			}
		}
		else // ����� ��� ������ ��� ���������� �� �������
		{
			// ��������� ������ ���� (� ��������)
			TennisOperations::ifCancelSet(setNum, cancelMessage);
		}
	}
}

// ������������ ������� ������ ����
void TennisOperations::ifCancelSet(const int setNum, const std::string& message)
{
	std::string logCMD;
	std::string forUser;

	// ���� ��� ���� � m_dataSet (�������), �� != 0
	if (m_data->workGame.checkSet(setNum))
	{
		// ���� ��� ���������� ��� ��� � ������, �� �������� ������

		std::string signal = m_data->workGame.getDataSet(setNum).getSignal(); // ����� ������
		int setNumArch = m_data->workGame.getSetNumArch(); // ����� ���������� ���� ������������� � �����

		if (signal == ComPhr::HOME || signal == ComPhr::AWAY || setNum <= setNumArch)
		{
			// ��������� ���������, ��� ���������� ��� �������� ��� �������� ������
			logCMD = m_header + TennisPhrase::SIGNAL_SET_CMD + std::to_string(setNum);
			forUser = TennisPhrase::SIGNAL_SET;
		}
		else
		{
			// �������� �� ���������� ���
			m_data->workGame.cancelSet(setNum, message);

			// ��������� ��������� �� ������ ����� ����
			if (m_data->workGame.getCurSet() == 0)
			{
				// ����� ������� ������� ���
				logCMD = m_header + TennisPhrase::CANC_SET_CMD + std::to_string(setNum);
				forUser = TennisPhrase::CANCELED_SET + std::to_string(setNum) + TennisPhrase::CANCELED_SET_END;
			}
			else
			{
				// ������� ��� �� ������ (�� �������)
				logCMD = m_header + TennisPhrase::CANC_SET_CMD + std::to_string(setNum);
				forUser = TennisPhrase::CANC_SET_BASE + std::to_string(setNum) + TennisPhrase::CANC_SET_BASE_END;
			}
		}
	}
	else // ���� ��� ��� �� ������
	{
		// ��������� ���������, ��� ���� ��� �������� ������
		logCMD = TennisPhrase::UNPLAY_SET_CMD + std::to_string(setNum);
		forUser = TennisPhrase::UNPLAYED_SET + std::to_string(setNum);
	}

	// ��� � ��������� ������������
	FileLog toFile;
	eventAndLog(m_ws, logCMD, forUser, toFile);
}

// ��������� ����� ��������� ����, ��������� ����, ���� ���������
void TennisOperations::commandByPoint()
{
	// �������� �������:
	// {"command": "by_point"}

	// ��������� �������� ����������� �������
	bool exam = false;
	exam = TennisOperations::examGameID(); // ���� �������?
	if (exam)
		exam = TennisOperations::examActivSet(); // ��� ������?
	if (exam)
	{
		std::string logCMD;
		std::string forUser;

		// �������� ����, ���� ����������
		if (!m_data->workGame.getCurDataSet().getCurGames()) // �������� ���� ����������� (= 0)?
		{
			m_data->workGame.getCurDataSet().newGames();
		}

		// ������������ ������� ������ �����������
		m_data->workGame.getCurDataSet().getActivGames().pressing(m_comTime);

		// ��������� ��������� � ��������� ������ � ���������� ����������
		bool position = m_data->workGame.getCurDataSet().getActivGames().getPressButton(); // ��������� ������
		if (position)
		{
			// ������ ������
			logCMD = m_header + TennisPhrase::PRESS_BUT_CMD + std::to_string(position);
			forUser = TennisPhrase::PRESSED_BUTTON_OFF;
		}
		else
		{
			// ������ ������
			logCMD = m_header + TennisPhrase::PRESS_BUT_CMD + std::to_string(position);
			forUser = TennisPhrase::PRESSED_BUTTON_ON;
		}

		// ��� � ��������� ������������
		FileLog toFile;
		eventAndLog(m_ws, logCMD, forUser, toFile);
	}
}

// ������ �������� �������� ���������� ����������
void TennisOperations::commandSetPoint()
{
	// �������� �������:
	// {"command": "set_point", "type_point": "increment/decrement"}

	// ��������� �������� ����������� �������
	bool exam = false;
	exam = TennisOperations::examGameID(); // ���� �������?
	if (exam)
		exam = TennisOperations::examActivSet(); // ��� ������?
	if (exam)
		exam = TennisOperations::examActivGames(); // ���� ������?
	if (exam)
		exam = TennisOperations::examInactivPress(); // ���������� ����������?
	if (exam)
	{
		// ��������� ������� � json
		auto parsed = json::parse(m_message);
		std::string point = parsed[Cmd::TYPE_POINT];

		std::string logCMD;
		std::string forUser;


		if (point == ComPhr::INCREMENT)
		{
			// ����������� ������� ���������� � �������� �� ����������
			int pointNum = m_data->workGame.getCurDataSet().getActivGames().pointIncrement();

			// ��������� ���������
			logCMD = m_header + TennisPhrase::UP_POINT_CMD + std::to_string(pointNum);
			forUser = TennisPhrase::POINT_COUNT_PREV + std::to_string(pointNum) + TennisPhrase::POINT_COUNT_END;
		}
		else // �������� ��� DECREMENT
		{
			// ��������� ������� ���������� � �������� �� ����������
			int pointNum = m_data->workGame.getCurDataSet().getActivGames().pointDecrement();

			// ��������� ���������
			logCMD = m_header + TennisPhrase::DOWN_POINT_CMD + std::to_string(pointNum);
			forUser = TennisPhrase::POINT_COUNT_PREV + std::to_string(pointNum) + TennisPhrase::POINT_COUNT_END;

		}

		// ��� � ���������
		FileLog toFile;
		eventAndLog(m_ws, logCMD, forUser, toFile);
	}
}

// �������� ���������� �������� ���
void TennisOperations::commandCancelPoint()
{
	// �������� �������:
	// {"command": "cancel_point"}

	// ��������� �������� ����������� �������
	bool exam = false;
	exam = TennisOperations::examGameID(); // ���� �������?
	if (exam)
		exam = TennisOperations::examActivSet(); // ��� ������?
	if (exam)
		exam = TennisOperations::examActivGames(); // ���� ������?
	if (exam)
		exam = TennisOperations::examInactivPress(); // ���������� ����������?
	if (exam)
	{
		// ������������ ������ ���������
		m_data->workGame.getCurDataSet().getActivGames().cancelPoint();

		// ��������� ���������
		std::string logCMD = m_header + TennisPhrase::CANC_POINT_CMD;

		// ��� � ���������
		FileLog toFile;
		eventAndLog(m_ws, logCMD, TennisPhrase::CANCELED_POINT, toFile);
	}
}

// ������ �������� �������� ������� ������
void TennisOperations::commandDoubleFault()
{
	// �������� �������:
	// {"command": "double_fault", "type_fault": "increment/decrement"}

	// ��������� �������� ����������� �������
	bool exam = false;
	exam = TennisOperations::examGameID(); // ���� �������?
	if (exam)
		exam = TennisOperations::examActivSet(); // ��� ������?
	if (exam)
		exam = TennisOperations::examActivGames(); // ���� ������?
	if (exam)
		exam = TennisOperations::examInactivPress(); // ���������� ����������?
	if (exam)
	{
		// ��������� ������� � json
		auto parsed = json::parse(m_message);
		std::string fault = parsed[Cmd::TYPE_FAULT];

		int countDouble;
		std::string logCMD;
		std::string forUser;

		if (fault == ComPhr::INCREMENT) // ����������� ���������� ������
		{
			// ��������� ��������� � ������� ������ � �� ������� �����
			countDouble = m_data->workGame.getCurDataSet().getActivGames().incrFault();
			int pointNum = m_data->workGame.getCurDataSet().getActivGames().getPoint(); // ���������� ����������

			logCMD = m_header + TennisPhrase::INCR_CMD + std::to_string(countDouble) + " and" + TennisPhrase::UP_POINT_CMD + std::to_string(pointNum);
			forUser = TennisPhrase::DOUBLE_VALUE_PREV + std::to_string(pointNum) + "::" + std::to_string(countDouble) + TennisPhrase::DOUBLE_VALUE_END;
		}
		else // ���������� ������ (DECREMENT)
		{
			// ��������� ��������� �� ������ ������� ������ � �� ������� �����
			countDouble = m_data->workGame.getCurDataSet().getActivGames().decrFault();
			int pointNum = m_data->workGame.getCurDataSet().getActivGames().getPoint(); // ���������� ����������

			logCMD = m_header + TennisPhrase::DECR_CMD + std::to_string(countDouble) + " and" + TennisPhrase::DOWN_POINT_CMD + std::to_string(pointNum);
			forUser = TennisPhrase::DOUBLE_VALUE_PREV + std::to_string(pointNum) + "::" + std::to_string(countDouble) + TennisPhrase::DOUBLE_VALUE_END;
		}

		// ��� � ���������
		FileLog toFile;
		eventAndLog(m_ws, logCMD, forUser, toFile);
	}
}

// ��������� ����
void TennisOperations::commandEndGames()
{
	// �������� �������:
	// {"command": "end_games", "games_win": "true/false"}

	// ��������� �������� ����������� �������
	bool exam = false;
	exam = TennisOperations::examGameID(); // ���� �������?
	if (exam)
		exam = TennisOperations::examActivSet(); // ��� ������?
	if (exam)
		exam = TennisOperations::examActivGames(); // ���� ������?
	if (exam)
		exam = TennisOperations::examInactivPress(); // ���������� ����������?
	if (exam)
	{
		std::string logCMD;
		std::string forUser;
		FileLog toFile;

		// ��������� ������� � json
		auto parsed = json::parse(m_message);
		std::string convertStr = parsed[Cmd::GAMES_WIN];

		// �������� � GAMES_WIN �� ������ ���� ������ (������������ ��������)
		std::string emptyStr = "";
		exam = examValue(convertStr, emptyStr);
		if (exam)
		{
			std::stringstream convert;

			convert << convertStr;
			bool winner;
			convert >> winner;

			// ��������� ����
			exam = m_data->workGame.getCurDataSet().endGames(winner); // ���� ��������� � ���?
			// ��� ��������� ����
			if (exam)
			{
				TennisOperations::endSet(TennisPhrase::AUTO_CLOSE, m_data);
			}
			else // ���������� ����
			{
				// ��������� ��������� � ���������� ����� � �����
				std::string score = m_data->workGame.getCurDataSet().getScore(); // ���� � ����
				std::string playerWinner;
				if (winner)
					playerWinner = m_data->workGame.getPlayHome();               // ����� 1 (����)
				else
					playerWinner = m_data->workGame.getPlayAway();               // ����� 2 (�� ������)

				// ���������� ���������
				std::string curPlayer;
				if (m_data->workGame.getCurDataSet().getCurPlayer())
					curPlayer = TennisPhrase::GAME_HOME;
				else
					curPlayer = TennisPhrase::GAME_AWAY;

				// ��������� ���������
				logCMD = m_header + TennisPhrase::FINISH_GAME_CMD + score + TennisPhrase::WINNER_CMD + playerWinner;
				forUser = TennisPhrase::FINISH_GAME_1 + curPlayer + score + TennisPhrase::FINISH_GAME_2 + playerWinner + TennisPhrase::FINISH_GAME_3;

				// ��� � ���������
				eventAndLog(m_ws, logCMD, forUser, toFile);

				// ��������� � ��������������� �������, ���� �����������
				TennisOperations::prevSignal(score);
			}
		}
		else // ������������ ������� �� ��������
		{
			// ��������� ���������
			logCMD = m_header + TennisPhrase::NOT_VALID_CMD;

			// ��� � ���������, ��� ���� �� �������
			eventAndLog(m_ws, logCMD, TennisPhrase::WIN_NOT_VALID, toFile);
		}
	}
}

// ��������� ���
void TennisOperations::endSet(const std::string& message, PerSocketData* data, bool printMode)
{
	// ��������� ����� ����
	int setNum = data->workGame.getCurSet();

	// ��������� ���
	std::string signal = data->workGame.endSetGetSignal(message);

	std::string logCMD;
	std::string forUser;

	// ���������� ��� �������� ����
	ScreenFileLog toFileScreen;
	FileLog toFile;
	IWriteLog* typeLog = &toFileScreen;

	if (signal == ComPhr::NONE)
	{
		// ��� �������
		// ��������� ��������� ����, ��� ��� �������
		std::string header;
		if (m_data->login != data->login)
		{
			// ��� �������������� �������� ������
			header = "User N " + std::to_string(m_data->userId) + " (login: " 
				+ data->login + ", old user N " + std::to_string(data->userId) + ")";
		}
		else
			header = m_header;

		logCMD = header + TennisPhrase::NONE_SIGNAL_CMD + std::to_string(setNum);

		// �� �������� ��� �� �����
		typeLog = &toFile;
	}
	else
	{
		// �������� ���������� ��� ���������
		std::string tour = data->workGame.getTour();
		std::string homePlayer = data->workGame.getPlayHome();
		std::string awayPlayer = data->workGame.getPlayAway();
		std::string winner;

		// ���������� ����������
		if (signal == ComPhr::HOME)
			winner = homePlayer;
		else if (signal == ComPhr::AWAY)
			winner = awayPlayer;
		else
			winner = ComPhr::NONE; // ��� ������������


		// ���������� ������ �� ������ � � ��������-���:
		std::string channel = TgBot::SIGNAL_CHANNEL; // ��� ������ �������� SIGNAL_CHANNEL �� TEST_CHANNEL

		// �������� ���������� ����� (��������� ����� �������)
		Timer time;
		std::string timeMsk = time.getTime() + " Msk";

		// ��������� ����� ��� ��������-����
		std::string signalMessage = "My message"; // ����������� ��� ���������!

		// ���������� ��������� � ��������-��� 
		TennisOperations::sendSignal(signalMessage);

		// ��������� ��������� ��� ����
		logCMD = m_header + TennisPhrase::HAVE_SIGNAL + " My message options"; // ����������� ���� �������������� �����!
	}

	// ������ ��������� ���� (���� � �� �����) ��� ��� ���������� ��������� ������������
	if (printMode)
	{
		// ��������� ��������� ������������
		forUser = TennisPhrase::END_SET_PREV + std::to_string(setNum) + TennisPhrase::END_SET_END;

		// ���������� � ���� � ������� �� �����, ���������� ��������� ������������
		eventAndLog(m_ws, logCMD, forUser, *typeLog);
	}
	else // ��� ��������������� ���������� � .close
	{
		ScreenFileLog toFileScreen;
		saveLog(logCMD, toFileScreen);
	}
}

// ������� ��������� Telegram-����
void TennisOperations::sendSignal(std::string& optionsCMD)
{
	// ������ ������� ��� cmd � �������:
	//system("cd C:\\Users\\�������_�_Telegram-����� & start python.exe tgbot.py '�����_���_����'");
	std::string commandCMD = "cd " + CATALOG_SERVER + CALL_TG_BOT + optionsCMD;

	system(commandCMD.c_str());
}

// ������� ����������� ������������� ���������������� �������
void TennisOperations::prevSignal(const std::string& score)
{
	// ������� ���������������� �������
	if (score == "") // ������� ���� �������!
	{
		// ��������� ��������� ��� ��������-����
		std::string tour = m_data->workGame.getTour();
		std::string homePlayer = m_data->workGame.getPlayHome();
		std::string awayPlayer = m_data->workGame.getPlayAway();
		int setNum = m_data->workGame.getCurSet();

		// ���������, ��� ������ ���������������
		std::string prevMsg = TgBot::SIGNAL_PREVIEW;

		// ��������� ������ ��� ��������
		std::string channel = TgBot::PREVIEW_CHANNEL; // ��� ������ �������� PREVIEW_CHANNEL �� TEST_CHANNEL

		// �������� ���������� ����� (��������� ����� �������)
		Timer time;
		std::string timeMsk = time.getTime() + " Msk";

		std::string signalMessage = "My options " + prevMsg + "/ my options."; // ����������� ��� ���������!

		// ���������� ��������� � ��������-��� 
		TennisOperations::sendSignal(signalMessage);

		// ��� � ���� � �� ����� � ��������������� �������
		std::string logCMD = m_header + TennisPhrase::PREV_SIGN_CMD + " My message options"; // ����������� ���� ����� � ���������
		ScreenFileLog toFileScreen;
		saveLog(logCMD, toFileScreen);
	}
}

// ��������� ���
void TennisOperations::commandEndSet()
{
	// �������� �������:
	// {"command": "end_set", "end_message": "��� ����!"}

	// ��������� �������� ����������� �������
	bool exam = false;
	exam = TennisOperations::examGameID(); // ���� �������?
	if (exam)
		exam = TennisOperations::examActivSet(); // ��� ������?
	if (exam)
	{
		// ��������� ������� � json
		auto parsed = json::parse(m_message);
		std::string endMessage = parsed[Cmd::END_MESSAGE];

		// ���� ������ �� ������ ������������ �� � ������� Windows 1251
		std::string emptyStr = "";
		if (examValue(endMessage, emptyStr))
		{
			StringConverter strConvert(endMessage);
			endMessage = strConvert.utf8ToW1251();
		}

		std::string logCMD;

		exam = m_data->workGame.getCurDataSet().getCurGames(); // ���� ������? (!=0)
		if (exam)
		{
			// ������� ������� �������� ����
			m_data->workGame.getCurDataSet().cancelCurGames();

			// ��������� ���� �� ������ �������� �����
			logCMD = m_header + TennisPhrase::CANC_GAMES;
			FileLog toFile;
			saveLog(logCMD, toFile);
		}

		// ��������� ���
		TennisOperations::endSet(endMessage, m_data);
	}
}

// ��������� ���� � ��������� ����������
void TennisOperations::commandEndTennis()
{
	// �������� �������:
	// {"command": "end_tennis", "type_end": "interim/totally"}

	// ��������� �������� ����������� �������
	bool exam = false;
	exam = TennisOperations::examGameID(); // ���� �������?
	if (exam)
	{
		std::string logCMD;

		// ��������� ������� � json
		auto parsed = json::parse(m_message);
		std::string typeEnd = parsed[Cmd::TYPE_END];

		// �������� �� ������� ������������� �������� �������
		std::string emptyStr = "";
		exam = examValue(typeEnd, emptyStr);
		if (exam)
		{
			exam = !m_data->workGame.getCurSet(); // ���� ��� ������ (= 0)
			if (exam)
			{
				// ��������� � ��������� ����, ���������� ���������
				TennisOperations::closeTennis(typeEnd, m_data);
			}
			else // ��� ������
			{
				// ��������� ���������, ��� ���������� ������� ���
				logCMD = m_header + TennisPhrase::FINISH_SET_CMD;

				// ��� � ��������� ������������
				FileLog toFile;
				eventAndLog(m_ws, logCMD, TennisPhrase::FINISH_SET, toFile);
			}
		}
		else // ������������ ������� �� ��������
		{
			// ��������� ���������
			logCMD = m_header + TennisPhrase::NOT_VALID_CMD;

			// ��� � ��������� ������������, ��� ���� �� �������
			FileLog toFile;
			eventAndLog(m_ws, logCMD, TennisPhrase::NOT_VALID_SAVE, toFile);
		}
	}
}

// ��������� � ��������� ����
void TennisOperations::closeTennis(const std::string& typeEnd, PerSocketData* data,	bool printMode)
{
	// ����� � �������� ����
	data->workGame.endTennis(typeEnd);

	std::string logCMD;
	std::string forUser;

	// ���������� ����������
	std::string gameId = data->workGame.getGameId();
	if (typeEnd == ComPhr::TOTALLY) // �������� ����������
	{
		// ��������� � �����
		m_tennisArchive[gameId] = data->workGame;

		// ������� ���� �� ��������
		data->workGame = TennisMatch();

		// ������� ���� �� ���� ��� ��� ������
		m_tennisGame.erase(gameId);
	}
	else // ������������� ����������
	{
		// ��������� � �����
		m_tennisArchive[gameId] = data->workGame;

		// ������� ���� �� ��������
		data->workGame = TennisMatch();
	}

	// ��������� ���������� � ����
	bool saveResult = TennisOperations::saveTennis(gameId);

	// ���������� ������������ � ���������� �����
	bool cancelResult = TennisOperations::saveCanselReport(gameId);

	// ��������� ��� ��������� � ���������� ��������� �����
	std::string logCMDplus;
	std::string forUserplus;
	if (cancelResult)
	{
		// �������� ���������� ������
		logCMDplus = TennisPhrase::CANS_REP_CMD;
		forUserplus = TennisPhrase::CANS_REP;
	}
	else
	{
		// ��������� ����� �� �������
		logCMDplus = TennisPhrase::CANS_REP_FAIL_CMD;
		forUserplus = TennisPhrase::CANS_REP_FAIL;
	}


	// �������� ���������� ����������
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

	// ��������� ��������� � ����������� �������� ����
	std::string header;
	if (m_data->login != data->login)
	{
		// �������������� ��������
		header = "User N " + std::to_string(m_data->userId) + " (login: " + data->login 
			+ ", old user N " + std::to_string(data->userId) + ")";
	}
	else
		header = m_header;

	logCMD = header + TennisPhrase::SAVE_RESULT_CMD + resCMD + " " + logCMDplus;
	forUser = TennisPhrase::SAVE_RESULT_PREV + resUser + " " + forUserplus + TennisPhrase::SAVE_RESULT_END;

	if (printMode)
	{
		// ��� � ��������� ������������
		FileLog toFile;
		eventAndLog(m_ws, logCMD, forUser, toFile);
	}
	else // ��� ��������������� �������� � .close
	{
		ScreenFileLog toFileScreen;
		saveLog(logCMD, toFileScreen);
	}
}

// ���������� ���������� ������������ ��� � ����
bool TennisOperations::saveTennis(const std::string& gameId)
{
	/*
	* ���������� ���������� ���������� �������.
	* ������������ ���� �������!
	*/

	return false;
}

// ��������� ������ �� ������ ���� � ����
bool TennisOperations::saveCanselReport(const std::string& gameId)
{
	// �������� ����� �������� ����� � ���� ���� ������ ����
	std::string fileOut = CANCEL_ARCHIVE + m_comTime.getMonthDay() + ".csv";

	std::ofstream out(fileOut, std::ios::app);

	// ��������� �������� �� ����
	if (!out.is_open())
	{
		std::string logCMD = "Cancel report archiving ERROR! Game ID: " + gameId;
		ScreenFileLog toFileScreen;
		saveLog(logCMD, toFileScreen);

		return false;
	}

	// ���� ���� ��������� ���� � ���� ����
	if (!m_tennisArchive.at(gameId).getReportCancel().empty())
	{
		for (auto element : m_tennisArchive.at(gameId).getReportCancel())
		{
			out << gameId << "," << std::to_string(element.first) << "," << element.second << std::endl;
		}
	}

	// ��������� ����
	out.close();

	return true;
}

// �������� ���� (INTERIM) � ������ ������������ ������ .close ��� ��������� �����������
void TennisOperations::closeWsEndTennis(PerSocketData* data)
{
	/*
	* ������������ PerSocketData* data ������ ������� ������ m_data
	* �� ������� ����, ��� ��� ���������� �������� ����� ����������� � ����������
	* � m_data �� �������� ���� ������� ����������� ������������,
	* � ��� ������ ������� � ������� ������������ � ����������
	*/

	// ���� ���� ��� �������
	if (data->workGame.getGameId() != "")
	{
		// ���������� ����
		std::string logMsg = "Automatic closing of the game of the user with the LOGIN: " + data->login;
		ScreenFileLog toFileScreen;
		saveLog(logMsg, toFileScreen);

		if (data->workGame.getCurSet()) // ������� ��� != 0, ������ ��� �����
		{
			if (data->workGame.getCurDataSet().getCurGames()) // ������� ���� != 0, ������ ���� �����
			{
				// ������� ����
				data->workGame.getCurDataSet().cancelCurGames();

				// ��������� ����
				logMsg = "The game is removed automatically.";
				ScreenFileLog toFileScreen;
				saveLog(logMsg, toFileScreen);
			}

			// ��������� ��� � ��������� ����
			TennisOperations::endSet(TennisPhrase::AUTO_CLOSE, data, false); // false - ������ ��������� ����
		}

		// ��������� � ��������� ����
		TennisOperations::closeTennis(ComPhr::INTERIM, data, false); // false - ������ ��������� ����
	}
	else
	{
		// ���������� ����
		std::string logMsg = "The game was saved earlier.";
		ScreenFileLog toFileScreen;
		saveLog(logMsg, toFileScreen);
	}
}
