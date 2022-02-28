#ifndef TENNISGAMES_H
#define TENNISGAMES_H

#include <string>

#include "Timer.h"
#include "Constants.h"


// ���������� ����� ��� �������������� ���
class TennisGames
{
private:
	bool        m_emptyGames;  // ����, ���� ��������� ������� ������ ����
	int         m_gamesNum;    // ����� ����� �����
	int         m_point;       // ���������� ����������
	bool        m_pressButton; // ���� ������� ������ (true - ������ ������)
	double      m_startTime;   // ��������� ����� �������
	double      m_endTime;     // �������� ����� �������
	double      m_prevTime;    // ����� ��� ���������� ���������
	double      m_lastTime;    // ����� ������� ���� ����������
	double      m_timePoint;   // ������� ����� ������ ���������
	int         m_doubleFault; // ������� ������� ������
	std::string m_winner;      // ���������� � ���� �����

	// ������ ���������� ���������� �����
	void        pressing(const Timer& t);
	int         pointIncrement();
	int         pointDecrement();
	void        cancelPoint();
	int         incrFault();
	int         decrFault();
	void        endGames(const std::string& winner);

public:
	TennisGames() : m_emptyGames(true)
	{

	}

	TennisGames(int gamesNum)
		: m_emptyGames(false),
		m_gamesNum(gamesNum),
		m_point(0),
		m_pressButton(false),
		m_prevTime(0),
		m_lastTime(0),
		m_timePoint(0),
		m_doubleFault(0)
	{

	}

	// �������
	bool        getEmpty()       const { return m_emptyGames; }
	int         getPoint()       const { return m_point; }
	double      getLastTime()    const { return m_lastTime; }
	double      getTimePoint()   const { return m_timePoint; }
	bool        getPressButton() const { return m_pressButton; }
	int         getDoubleFault() const { return m_doubleFault; }
	std::string getWinner()      const { return m_winner; }
	std::string getGamesHeader() const;

	friend class TennisSet;
	friend class TennisOperations;

};

#endif // !TENNISGAMES_H