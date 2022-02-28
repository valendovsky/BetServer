#include "Clients.h"

//Функция сверки хешей пароля
bool Clients::checkPass(  const std::string pass) const
{
	std::hash<std::string> hash;

	std::string hashPass = std::to_string(hash(pass));

	return m_pass == hashPass;
}

// Для тестирования
std::ostream& operator<< (std::ostream& out, 
	                      const Clients& users)
{
	out << "User login: " << users.m_login << ", status admin: " << users.m_admin << ", email: " 
		<< users.m_mail << ", check pass: " << users.checkPass("wrongPASS");

	return out;
}
