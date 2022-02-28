#ifndef FILELOG_H
#define FILELOG_H

#include <string>

#include "IWriteLog.h"
#include "Timer.h"


// Класс для логирования информации в файл
class FileLog : public IWriteLog
{
public:
	virtual void writeLog(const std::string& message) const override;

	// Виртуальный деструктор
	virtual      ~FileLog() {}
};

#endif // !FILELOG_H