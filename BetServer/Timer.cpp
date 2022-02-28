#include "Timer.h"

// ���������� ����� ���������� ���������
double Timer::elapsed() const
{
	return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
}

// ���������� ������� ��������� ����� � ���� �������
tm* Timer::localTimeNow() const
{
	// ������� �����
	time_t seconds = time(NULL);

	// ��������� �����
#pragma warning(suppress : 4996)
	tm* timeinfo = std::localtime(&seconds);

	return timeinfo;
}

// ���������� ����������������� ��������� ����� � ���� �������
std::string Timer::formatTimeDate(const Timer::TimeMode& mode) const
{
#pragma warning(suppress : 4996)
	std::string time_asc(std::asctime(localTimeNow()));

	// ��������� �� �������: <����_������ ����� ���� ��:��:�� ���>
	std::stringstream convertTime;
	convertTime << time_asc;

	// ���������� ����������
	std::string weekDay;
	std::string month;
	std::string day;
	std::string h_m_s;
	std::string year;

	convertTime >> weekDay >> month >> day >> h_m_s >> year;

	// ���������� �������� ������� �������� ����
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

// ���������� ������� ������ ���� � �����
std::string Timer::getFullDate() const
{
	return formatTimeDate(TIMEMODE_FULL_DATE);
}

// ���������� ������� �����
std::string Timer::getTime() const
{
	return formatTimeDate(TIMEMODE_HHMMSS);
}

// ���������� ������� ����� � ����
std::string Timer::getMonthDay() const
{
	return formatTimeDate(TIMEMODE_MD);
}
