#ifndef TENNISOPERATIONS_H
#define TENNISOPERATIONS_H

#include <string>
#include <string_view>
#include <map>
#include <uwebsockets/App.h>
#include <nlohmann/json.hpp>

#include "PerSocketData.h"
#include "Timer.h"
#include "ParsTennis.h"
#include "TennisMatch.h"
#include "ConstPhrase.h"
#include "IWriteLog.h"
#include "FileLog.h"
#include "ScreenFileLog.h"
#include "StringConverter.h"
#include "LogAndSend.h"
#include "Clients.h"

// Сокращения для удобства работы с json
using json       = nlohmann::json;
// и WebSocket
using uwebsock_t = uWS::WebSocket<false, true, PerSocketData>;


// Класс управления действиями пользователей в теннисных матчах
class TennisOperations
{
private:
	uwebsock_t*                         m_ws;
	const std::string_view              m_message;
	const Timer&                        m_comTime;
	std::map<std::string, ParsTennis>&  m_tennisGame;
	std::map<std::string, TennisMatch>& m_tennisArchive;
	PerSocketData*                      m_data;
	std::string                         m_header;

	// Методы каскадных проверок необходимых условий
	bool examGameID();
	bool examInactivPress();
	bool examActivSet();
	bool examActivGames();

	// Методы обработки событий
	void ifCancelSet(     const int setNum,
		                  const std::string& message);

	void endSet(          const std::string& message,
		                  PerSocketData* data,
		                  bool printMode = true);

	void sendSignal(      std::string& optionsCMD);

	void prevSignal(      const std::string& score);

	void closeTennis(     const std::string& typeEnd,
		                  PerSocketData* m_data,
		                  bool printMode = true);

	bool saveTennis(      const std::string& gameId);

	bool saveCanselReport(const std::string& gameId);

public:
	TennisOperations(     uwebsock_t* ws,
		                  const std::string_view message,
		                  const Timer& comTime,
		                  std::map<std::string, ParsTennis>& tennisGame,
		                  std::map<std::string, TennisMatch>& tennisArchive)
		: m_ws(ws),
		m_message(message),
		m_comTime(comTime),
		m_tennisGame(tennisGame),
		m_tennisArchive(tennisArchive)
	{
		// Получение данных из структуры пользователей
		m_data = ws->getUserData();

		// Формируем шапку лог-сообщения
		m_header = "User N " + std::to_string(m_data->userId) + " (login: " + m_data->login + ")";
	}

	//Геттеры
	std::string getCommand();
	std::string getHeader() { return m_header; }

	// Метод вывода
	void        eventLog(const std::string logMsg,
		                 const std::string userMsg,
		                 IWriteLog& typeLog)
	{
		eventAndLog(m_ws, logMsg, userMsg, typeLog);
	}

	// Оператор авторизации
	void        auth(    const std::map<std::string, Clients>& allClients,
		                 std::map<unsigned int, PerSocketData*>& authUsers);

	// Операторы игры
	void        commandSetTennis();
	void        commandSetSet();
	void        commandCancelSet();
	void        commandByPoint();
	void        commandSetPoint();
	void        commandCancelPoint();
	void        commandDoubleFault();
	void        commandEndGames();
	void        commandEndSet();
	void        commandEndTennis();
	void        closeWsEndTennis(PerSocketData* data);


	template <typename T>
	friend bool examValue(       T value,
		                         T testValue);

	friend void eventAndLog(     uwebsock_t* ws,
		                         const std::string logMsg,
		                         const std::string userMsg,
		                         IWriteLog& typeLog);

	friend void saveLog(         const std::string message,
		                         IWriteLog& typeLog);

};

#endif // !TENNISOPERATIONS_H