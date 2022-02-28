// BetServer.cpp : серверное приложение для ОС Windows и Windows Server
// Программа для мануальной фиксации статистики теннисных матчей через браузер
// И автоматической отправки результатов через Telegram-бот

#include <iostream>
#include <uwebsockets/App.h>
#include <nlohmann/json.hpp>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <cstdio>
#include <string_view>
#include <exception>


#include "PerSocketData.h"
#include "Clients.h"
#include "StringConverter.h"
#include "ParsTennis.h"
#include "IWriteLog.h"
#include "FileLog.h"
#include "ScreenFileLog.h"
#include "LogAndSend.h"
#include "TennisOperations.h"
#include "TennisMatch.h"
#include "Constants.h"
#include "ConstPhrase.h"
#include "Timer.h"


// Сокращения для удобства работы с json
using json = nlohmann::json;
// и WebSocket
using uwebsock_t = uWS::WebSocket<false, true, PerSocketData>;


// Загружает базу данных с пользователями сервера
bool loadingUserData(std::map <std::string, Clients>& allClients, const std::string str)
{
	// Структура строки файла с данными пользователей:
	// login,admin,mail,pass

	// Переменные обработки полученной строки
	std::string strCount;
	std::string delim(","); // делитель позиций
	size_t prev(0);
	size_t next;
	size_t delta(delim.length());
	std::stringstream convert;

	// Переменные для хранения данных из строки
	std::string login;
	bool admin;
	std::string mail;
	std::string pass;

	int index(0); // отсчёт считываемой позиции
	while ((next = str.find(delim, prev)) != std::string::npos) // проверка нахождения
	{
		if (index >= 3) // 3 позиция читается вне цикла, в конце строки нет запятой
		{
			std::cout << "Error in the file: ";

			return false;
		}

		strCount = str.substr(prev, (next - prev));
		StringConverter strConvert(strCount);
		// Удаляем кавычки
		std::string strReady = strConvert.deleteQuotes();

		switch (index)
		{
		case 0:
			// Переводим все символы в строчные
			login = strConvert.toLower();
			break;
		case 1:
			convert << strReady;
			convert >> admin;
			break;
		case 2:
			mail = strReady;
			break;
		}

		// Очищаем и сбрасываем флаги
		convert.str("");
		convert.clear();

		++index;

		prev = next + delta;
	}
	// Case 3:
	// Фиксация конца строки без "," (пароль)
	// Без проверки на кавычки, берём пароль как есть
	pass = str.substr(prev, (next - prev));

	// Записываем пользователя в базу сервера
	allClients[login] = Clients(login, admin, mail, pass);

	return true;
}

// Загружает спарсенные игры на сервер
bool loadingTennisGame(std::map<std::string, ParsTennis>& tennisGame, const std::string str)
{
	// Структура строки файла с предварительно спарсенными играми:
	// game_id,tour,court,break,ref,time,home,away,worker
	// 
	// worker - выставляет админ


	// Переменные обработки полученной строки
	std::string strCount;
	std::string delim(","); // делитель позиций
	size_t prev(0);
	size_t next;
	size_t delta(delim.length());
	std::stringstream convert;

	// Переменные для хранения данных из строки
	std::string gameId;
	std::string dateGame;
	std::string tour;
	std::string court;
	short timeBreak;
	std::string refGame;
	std::string timeGame;
	std::string playHome;
	std::string playAway;
	std::string worker;

	int index(0); // отсчёт считываемой позиции
	while ((next = str.find(delim, prev)) != std::string::npos) // проверка нахождения
	{
		if (index >= 9) // 9 позиция читается вне цикла, в конце строки нет запятой
		{
			std::cout << "Error in the file: ";

			return false;
		}

		strCount = str.substr(prev, (next - prev));
		StringConverter strConvert(strCount);
		// Удаляем кавычки
		std::string strReady = strConvert.deleteQuotes();

		int lengthCount;
		switch (index)
		{
		case 0:
			gameId = strReady;
			break;
		case 1:
			dateGame = strReady;
			break;
		case 2:
			tour = strReady;
			break;
		case 3:
			court = strReady;
			break;
		case 4:
			convert << strReady;
			convert >> timeBreak;
			break;
		case 5:
			refGame = strReady;
			break;
		case 6:
			timeGame = strReady;
			break;
		case 7:
			playHome = strReady;
			break;
		case 8:
			playAway = strReady;
			break;
		}

		// Очищаем и сбрасываем флаги
		convert.str("");
		convert.clear();

		++index;

		prev = next + delta;
	}

	// Case 9:
	// Фиксация конца строки без "," (исполнитель)
	strCount = str.substr(prev, (next - prev));
	// Удаляем кавычки
	StringConverter strConvert(strCount);
	worker = strConvert.deleteQuotes();


	// Сохраняем игру в базу сервера
	tennisGame[gameId] = ParsTennis(gameId, dateGame, tour, court, timeBreak, refGame, timeGame, playHome, playAway, worker);

	return true;
}

// Считывает информацию из файлов
template <typename T>
bool readFile(const std::string fileName, std::map<std::string, T>& mapT, bool (*fnc)(std::map<std::string, T>&, const std::string))
{
	std::ifstream in(fileName);
	std::string logMsg;
	ScreenFileLog toFileScreen;

	// Проверяем, что файл открылся
	if (!in.is_open())
	{
		// Записываем логи
		logMsg = "Error open file: " + fileName;
		saveLog(logMsg, toFileScreen);

		return false;
	}

	std::string str;
	while (!in.eof())
	{
		std::getline(in, str);

		// Пропускаем пустые строки
		if (str == "")
			continue;

		// Проверяем успешность загрузки файла
		if (!fnc(mapT, str))
		{
			// Записываем логи
			logMsg = "File upload error: " + fileName;
			saveLog(logMsg, toFileScreen);

			return false;
		}
	}

	// Записываем логи
	logMsg = "The file downloaded. Uploaded by " + std::to_string(mapT.size()) + " positions.";
	saveLog(logMsg, toFileScreen);

	return true;
}

// Формирует ответ пользователю на http запрос (конвертируем страницу для передачи)
std::string getHTML(const std::string fileName)
{
	// Формируем тело ответа (HTML)
	std::string response;

	std::ifstream in(fileName);

	// Если страницы нет, будет отправляться заглушка
	if (!in.is_open())
		response = "404 NOT FOUND";
	else
	{
		// Записываем код из html в строку
		std::string str;
		while (!in.eof())
		{
			std::getline(in, str);
			response = response + "\n" + str;
		}
	}

	// Переводим в формат UTF-8
	StringConverter htmlConvert(response);
	std::string htmlUtf8 = htmlConvert.w1251ToUtf8();

	return htmlUtf8;
}

// Определяет действие пользователя
void tennisAction(TennisOperations& operation)
{
	// Определяем вид события
	std::string command = operation.getCommand();

	// Обрабатываем поступившую команду
	if (command == Cmd::SET_TENNIS)
	{
		// Закрепляем игру за пользователем для разбора
		operation.commandSetTennis();
	}
	else if (command == Cmd::SET_SET)
	{
		// Устанавливаем текущий сет для разбираемой игры
		operation.commandSetSet();
	}
	else if (command == Cmd::CANCEL_SET)
	{
		// Отмена выбранного сета
		operation.commandCancelSet();
	}
	else if (command == Cmd::BY_POINT)
	{
		// Запуск и остановка отсчёта времени
		// Запуск гейма, если требуется
		operation.commandByPoint();
	}
	else if (command == Cmd::SET_POINT)
	{
		// Изменяем количество розыгрышей
		operation.commandSetPoint();
	}
	else if (command == Cmd::CANCEL_POINT)
	{
		// Отмена времени последнего активного мяча
		operation.commandCancelPoint();
	}
	else if (command == Cmd::DOUBLE_FAULT)
	{
		// Изменение счётчика двойных ошибок
		operation.commandDoubleFault();
	}
	else if (command == Cmd::END_GAMES)
	{
		// Конец гейма
		operation.commandEndGames();
	}
	else if (command == Cmd::END_SET)
	{
		// Завершение сета
		operation.commandEndSet();
	}
	else if (command == Cmd::END_TENNIS)
	{
		// Закрываем игру полностью или на время и сохраняем статистику
		operation.commandEndTennis();
	}
	else if (command == AuthPhrase::AUTH)
	{
		// Формируем сообщения
		std::string logCMD = operation.getHeader() + AuthPhrase::AUTH_EARLIER_CMD;

		// Лог и сообщение, что пользователь уже авторизовался
		FileLog toFile;
		operation.eventLog(logCMD, AuthPhrase::AUTH_EARLIER, toFile);
	}
	else
	{
		// Формируем сообщения
		std::string logCMD = operation.getHeader() + AuthPhrase::COM_UNKNOWN_CMD;

		// Сообщение пользователю и лог в файл и на экран о неизвестной команде
		ScreenFileLog toFileScreen;
		operation.eventLog(logCMD, AuthPhrase::COM_UNKNOWN, toFileScreen);
	}
}


int main()
{
	// Распознование консолью стандарта UTF-8
	SetConsoleOutputCP(CP_UTF8);
	// Включаем буферизацию, чтобы не разбивались байты
	setvbuf(stdout, nullptr, _IOFBF, 1000);


	// Записываем логи в файл и на экран
	FileLog toFile;
	ScreenFileLog toFileScreen;
	saveLog("START BET SERVER!", toFileScreen);


	// Загрузка базы с пользователями сервера
	std::map<std::string, Clients> allClients;
	bool loadResult = readFile(USER_DATA, allClients, loadingUserData);

	// Проверка инициализации базы пользователей
	if (!loadResult)
	{
		// Записываем логи
		saveLog(ERROR_CLIENTS, toFileScreen);

		std::cin.get();

		return -1;
	}


	// Загрузка игр для работы
	std::map<std::string, ParsTennis> tennisGame;
	loadResult = readFile(TENNIS_GAME, tennisGame, loadingTennisGame);

	// Проверка загрузки теннисных игр
	if (!loadResult)
	{
		// Записываем логи
		saveLog(ERROR_TENNIS, toFileScreen);

		std::cin.get();

		return -1;
	}


	// Архивные, полностью или частично отработанные игры
	std::map<std::string, TennisMatch> tennisArchive;

	// Формируем код html-страницы для отправки
	std::string tennisPage = getHTML(TENNIS_HTML);

	// Запуск общего таймера
	Timer comTime;

	// Авторизованные пользователи
	std::map<unsigned int, PerSocketData*> authUsers;

	// Счётчик используемых id
	unsigned int latestdId = 10;


	// Запускаем вебсервер
	uWS::App().get("/tennis", [&tennisPage](auto* res, auto* req) {
		// Отправляем пользователю страницу при обращении к серверу
		res->end(tennisPage.c_str());
		}).get("/*", [](auto* res, auto* req) {
			// Страница не найдена
			res->end("404 NOT FOUND");
		}).ws<PerSocketData>("/*", {
		/* Settings */
		.idleTimeout = 3600,
		/* Handlers */
		.open = [&latestdId, &toFileScreen](auto* ws) {
			// Получаем информацию о пользователе
			PerSocketData* data = ws->getUserData();

			// Назначаем id пользователю
			data->userId = latestdId++;

			// Записываем логи
			std::string logMsg = "New user N " + std::to_string(data->userId) + " connected.";
			saveLog(logMsg, toFileScreen);
		},
		.message = [&allClients, &comTime, &tennisGame, &tennisArchive, &authUsers, &toFile, &toFileScreen](auto* ws, std::string_view message, uWS::OpCode opCode) {
			// Получаем информацию о пользователе
			PerSocketData* data = ws->getUserData();

			// Записываем логи
			std::string convViewStr{ message };

			std::string logMsg = "Event from user N " + std::to_string(data->userId) + ": " + convViewStr;
			saveLog(logMsg, toFile);

			// Исключаем отказ сервера
			try
			{
				// Проверка json на корректность
				auto parsed = json::parse(message);

				// Инициализируем объект управления теннисными событиями
				TennisOperations operation(ws, message, comTime, tennisGame, tennisArchive);

				// Обработка ивента в зависимости от авторизации
				if (data->auth)
				{
					// Авторизация пройдена
					tennisAction(operation);
				}
				else
				{
					operation.auth(allClients, authUsers);
				}
			}
			catch (std::exception& exception)
			{
				// Записываем логи
				std::string excepMsg(exception.what());
				std::string logMsg = "Standard exception: " + excepMsg;
				saveLog(logMsg, toFileScreen);
			}
			catch (...)
			{
				// Записываем логи
				std::string logMsg = "The server threw an error: " + convViewStr;
				saveLog(logMsg, toFileScreen);
			}
		},
		.close = [&comTime, &tennisGame, &tennisArchive, &toFileScreen](auto* ws, int /*code*/, std::string_view message) {
			// Получаем информацию о пользователе
			PerSocketData* data = ws->getUserData();

			// Записываем логи
			std::string logMsg = "User N " + std::to_string(data->userId) + " disconnected.";
			saveLog(logMsg, toFileScreen);

			// Инициализируем объект управления теннисными событиями
			TennisOperations operation(ws, message, comTime, tennisGame, tennisArchive);

			// Закрытие и сохранение активной игры, если такая есть
			operation.closeWsEndTennis(data);
		}
	}).listen(g_port, [&toFileScreen](auto* listen_socket) {
		if (listen_socket)
		{
			// Записываем логи
			std::string logMsg = "Listening on port " + std::to_string(g_port);
			saveLog(logMsg, toFileScreen);
		}
	}).run();

	// Записываем логи
	std::string logMsg = "Failed to listen on port " + std::to_string(g_port);
	saveLog(logMsg, toFileScreen);

	std::cin.get();

	return 0;
}
