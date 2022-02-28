#include "Timer.h"

// Возвращает время прошедшего интервала
double Timer::elapsed() const
{
	return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
}

// Возвращает текущие локальное время и дату сервера
tm* Timer::localTimeNow() const
{
	// Текущее время
	time_t seconds = time(NULL);

	// Локальное время
#pragma warning(suppress : 4996)
	tm* timeinfo = std::localtime(&seconds);

	return timeinfo;
}

// Возвращает отформатированное локальное время и дату сервера
std::string Timer::formatTimeDate(const Timer::TimeMode& mode) const
{
#pragma warning(suppress : 4996)
	std::string time_asc(std::asctime(localTimeNow()));

	// Сортируем из формата: <день_недели месяц день чч:мм:сс год>
	std::stringstream convertTime;
	convertTime << time_asc;

	// Переменные извлечения
	std::string weekDay;
	std::string month;
	std::string day;
	std::string h_m_s;
	std::string year;

	convertTime >> weekDay >> month >> day >> h_m_s >> year;

	// Возвращаем значение времени согласно моду
	std::string localTime;
	switch (mode)
	{
	case TIMEMODE_FULL_DATE:
		localTime = year + "-" + month + "-" + day + " " + h_m_s + " MSK ";
		break;
	case TIMEMODE_HHMMSS:
		localTime = h_m_s;
		break;
	case TIMEMODE_MD:
		localTime = month + day;
		break;
	default:
		localTime = year + "-" + month + "-" + day + " " + h_m_s + " MSK";
		break;
	}

	return localTime;
}

// Возвращает текущую полную дату и время
std::string Timer::getFullDate() const
{
	return formatTimeDate(TIMEMODE_FULL_DATE);
}

// Возвращает текущее время
std::string Timer::getTime() const
{
	return formatTimeDate(TIMEMODE_HHMMSS);
}

// Возвращает текущий месяц и дату
std::string Timer::getMonthDay() const
{
	return formatTimeDate(TIMEMODE_MD);
}
