#ifndef FILELOG_H
#define FILELOG_H

#include <string>

#include "IWriteLog.h"
#include "Timer.h"


// ����� ��� ����������� ���������� � ����
class FileLog : public IWriteLog
{
public:
	virtual void writeLog(const std::string& message) const override;

	// ����������� ����������
	virtual      ~FileLog() {}
};

#endif // !FILELOG_H