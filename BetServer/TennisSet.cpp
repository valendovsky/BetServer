#include "TennisSet.h"

// ������ ����� ����
void TennisSet::newGames()
{
	// ��� ������������� m_countGames = 0, �� ������ ���� = 1
	m_curGames = ++m_countGames;

	// ��������� �������� ���������� ������
	if (m_curPlayer) // true - home player
	{
		m_dateGamesHome.push_back(m_curGames);
	}
	else // false - away player
	{
		m_dateGamesAway.push_back(m_curGames);
	}
}

// ������� ������� ���
void TennisSet::cancelCurGames()
{
	if (m_curGames) // ������ ���� ������� ����
	{
		if (m_curPlayer) // true - home player
		{
			m_dateGamesHome.pop_back();
		}
		else // false - away player
		{
			m_dateGamesAway.pop_back();
		}

		// �������� ������� ���� � ������ ����� �������� ������
		m_curGames = 0;
		--m_countGames;
	}
}

// ��������� �������� ����
TennisGames& TennisSet::getActivGames()
{
	// ���������� ��������������� ���� � ����������� �� ���������
	if (m_curPlayer)
		return m_dateGamesHome.back();
	else
		return m_dateGamesAway.back();
}

// ���������� ������ ��� ����������� ��������
const TennisGames& TennisSet::getActivGames() const
{
	// ���������� ��������������� ���� � ����������� �� ���������
	if (m_curPlayer)
		return m_dateGamesHome.back();
	else
		return m_dateGamesAway.back();
}

// ��������� ����
// � ���������� ���� �� ��������� ���
bool TennisSet::endGames(const bool winner)
{
	std::string winStr;
	// ��������� ���� ����������
	if (winner)
	{
		++m_gamesHome;

		winStr = ComPhr::HOME;
	}
	else
	{
		++m_gamesAway;

		winStr = ComPhr::AWAY;
	}

	// ��������� ���������� ���������
	if (m_curPlayer)
	{
		m_dateGamesHome.back().endGames(winStr);
	}
	else
	{
		m_dateGamesAway.back().endGames(winStr);
	}

	// ��� ��������� �����
	m_curGames = 0;

	// ���� �� ��������� ���
	if (checkEndSet(winner))
		return true; // ��������� ���

	// ������ ��������� ������
	m_curPlayer = !m_curPlayer;

	return false; // ��� ��������� �� ����
}

// ��������� ������� �������� ����
bool TennisSet::checkEndSet(const bool winner)
{
	/*
	* ������ ������� �������� ���� �������.
	* ������������ �������������!
	*/

	return true;
}

// ���������� ������� ���� � ����
std::string TennisSet::getScore() const
{
	std::string score = std::to_string(m_gamesHome) + " - " + std::to_string(m_gamesAway);

	return score;
}

// ��������� ���
void TennisSet::endSet()
{
	/* 
	* ������ �������� ���� �������.
	* ������������ ���� ������ �������� ����!
	*/
}

// ������� ������� ���������� ������ home �� ���� ��� �����
std::string TennisSet::getSetHeaderHome() const
{
	std::string header = 
		std::to_string(m_gamesHome) + "," +
		std::to_string(m_homeMedPoint) + "," +
		std::to_string(m_homeMedTime) + "," +
		std::to_string(m_homeMedTimePoint) + ",doubleFault"; // none - ����� ��� �������� ��������

	return header;
}

// ������� ������� ���������� ������ away �� ���� ��� �����
std::string TennisSet::getSetHeaderAway() const
{
	std::string header = 
		std::to_string(m_gamesAway) + "," +
		std::to_string(m_awayMedPoint) + "," +
		std::to_string(m_awayMedTime) + "," +
		std::to_string(m_awayMedTimePoint) + ",doubleFault";

	return header;
}
