#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>


// ����� ��� ������ � ����� � ��������
class Timer
{
private:
	// ������� ������ ������� � ����
	enum TimeMode
	{
		TIMEMODE_FULL_DATE, // ����-�-�� ��:��:��
		TIMEMODE_HHMMSS,    // ��:��:��
		TIMEMODE_MD         //��
	};

	using clock_t  = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;

	std::chrono::time_point<clock_t> m_beg;

	// std::chrono::time_zone �� �������� � Windows Server 2016
	tm*         localTimeNow() const;
	std::string formatTimeDate(const TimeMode& mode) const;

public:
	Timer() : m_beg(clock_t::now())
	{

	}

	// ������ �������� ��������� ��������
	void        reset()              { m_beg = clock_t::now(); }
	double      elapsed()     const;

	// ��������������� ����� ������� � ����
	std::string getFullDate() const;
	std::string getTime()     const;
	std::string getMonthDay() const;
};

#endif // !TIMER_H