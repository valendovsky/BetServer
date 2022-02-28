#ifndef IWRITELOG_H
#define IWRITELOG_H

#include <iostream>
#include <string>
#include <fstream>

#include "Constants.h"
#include "Timer.h"


// Интерфейсный класс для сохранения логов
class IWriteLog
{
public:
	// Чистая виртуальная функция для сохранения логов
	virtual void writeLog(const std::string& message) const = 0;

	// Виртуальный деструктор
	virtual      ~IWriteLog() {}
};

#endif // !IWRITELOG_H