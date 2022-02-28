#include "TennisGames.h"

// ��������� ������� ������ "����"
void TennisGames::pressing(const Timer& t)
{
	// �������� ��������� ������
	if (m_pressButton)
	{
		// ������ ������ (��������, ����� �������)
		m_endTime = t.elapsed();

		// ��������� ����� ��� ����� ��������� (�� ������ ������)
		m_prevTime = m_lastTime;

		// ��������� ���������� ������ �� �������� ���������� ���������
		m_lastTime += m_endTime - m_startTime;

		// ���� - ������ ������
		m_pressButton = false;
	}
	else
	{
		// ������ �� ������ (��������, ����� �������)
		m_startTime = t.elapsed();

		// ���� - ������ ������
		m_pressButton = true;
	}
}

// ����������� ����� ����������
int TennisGames::pointIncrement()
{
	++m_point;

	return m_point;
}

// ��������� ����� ����������
int TennisGames::pointDecrement()
{
	// �� ��������� ���������� ���������� ������ 0
	if (m_point)
	{
		--m_point;
	}

	return m_point;
}

// ������ ���������
void TennisGames::cancelPoint()
{
	// ���������� ����� �� ����� ���������
	m_lastTime = m_prevTime;

	// �� �������������� ������ ��������� ������������������ ������ ������� ������ � ���������
	// ����� ����������� ������������ ������� ������� ��� ������ ���������
}

// ����������� ������� ������� ������
int TennisGames::incrFault()
{
	// ����������� ������� ������
	++m_doubleFault;
	// � ����� ����������
	++m_point;

	// ���������� �����
	m_lastTime += g_timeFault;

	return m_doubleFault;
}

// ��������� ������� ������
int TennisGames::decrFault()
{
	// �� ��������� ���������� ������ ������ 0
	if (m_doubleFault)
	{
		// ��������� ������� ������
		--m_doubleFault;
		// � ���������� ����������, ���� ��� �� ����� 0
		if (m_point)
			--m_point;

		// ��������� �����
		m_lastTime -= g_timeFault;
	}

	return m_doubleFault;
}

// �������� ��� ���������� �����
void TennisGames::endGames(const std::string& winner)
{
	// ��������� ���������� � �����
	m_winner = winner;

	// ������� ����� ������ ���������
	if (m_point) // �� ���� ������ ������
	{
		m_timePoint = m_lastTime / m_point;
	}
	else
		m_timePoint = 0;
}

// ���������� �� ����� ��� ������ � ����
std::string TennisGames::getGamesHeader() const
{
	std::string header = 
		std::to_string(m_gamesNum) + "," +
		std::to_string(m_point) + "," +
		std::to_string(m_lastTime) + "," +
		std::to_string(m_timePoint) + "," +
		std::to_string(m_doubleFault);

	return header;
}
