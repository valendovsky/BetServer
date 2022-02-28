#ifndef CLIENTS_H
#define CLIENTS_H

#include <iostream>
#include <string>
#include <functional>


// Зарегистрированные пользователи сервера
class Clients
{
private:
	std::string m_login;
	bool        m_admin;
	std::string m_mail;
	std::string m_pass;

public:
	Clients(const std::string& login,
		    bool admin,
		    const std::string& mail,
		    const std::string& pass)
		    : m_login(login),
		    m_admin(admin),
		    m_mail(mail),
		    m_pass(pass)
	{

	}

	Clients()
	{

	}


	// Геттеры
	std::string getLogin() const { return m_login; }
	bool        getType()  const { return m_admin; }
	std::string getMail()  const { return m_mail; }

	// Проверка пароля
	bool        checkPass(const std::string pass) const;

	friend std::ostream& operator<< (std::ostream& out, const Clients& users);
};

#endif // !CLIENTS_H