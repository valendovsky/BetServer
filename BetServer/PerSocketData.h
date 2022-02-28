#ifndef PERSOCKETDATA_H
#define PERSOCKETDATA_H

#include <string>

#include "TennisMatch.h"


// »нформаци€ о пользователе сервера
struct PerSocketData
{
	unsigned int userId;           // »Ќ пользовател€ вебсервера
	std::string  login;            // логин из базы зарегистрированных пользователей
	bool         auth =     false; // пометка о пройденой авторизации
	bool         is_admin = false; // пометка о статусе администратора
	TennisMatch   workGame;        // открыта€ игра
};

#endif // !PERSOCKETDATA_H