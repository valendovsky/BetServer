#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>


// Класс для работы с датой и временем
class Timer
{
private:
	// Форматы вывода времени и даты
	enum TimeMode
	{
		TIMEMODE_FULL_DATE, // гггг-м-дд чч:мм:сс
		TIMEMODE_HHMMSS,    // чч:мм:сс
		TIMEMODE_MD         //мд
	};

	using clock_t  = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;

	std::chrono::time_point<clock_t> m_beg;

	// std::chrono::time_zone не работает в Windows Server 2016
	tm*         localTimeNow() const;
	std::string formatTimeDate(const TimeMode& mode) const;

public:
	Timer() : m_beg(clock_t::now())
	{

	}

	// Методы фиксации временных отрезков
	void        reset()              { m_beg = clock_t::now(); }
	double      elapsed()     const;

	// Форматированный вывод времени и даты
	std::string getFullDate() const;
	std::string getTime()     const;
	std::string getMonthDay() const;
};

#endif // !TIMER_H