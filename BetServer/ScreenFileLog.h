#ifndef SCREENFILELOG_H
#define SCREENFILELOG_H

#include <iostream>
#include <string>

#include "IWriteLog.h"
#include "Timer.h"


// Класс для вывода логов на экран и сохранения в файл
class ScreenFileLog : public IWriteLog
{
public:
	virtual void writeLog(const std::string& message) const override;

	// Виртуальный деструктор
	virtual      ~ScreenFileLog() {}
};

#endif // !SCREENFILELOG_H