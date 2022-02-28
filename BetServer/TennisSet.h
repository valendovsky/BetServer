#ifndef TENNISSET_H
#define TENNISSET_H

#include <vector>
#include <string>

#include "TennisGames.h"
#include "Constants.h"


// ��������� ����� �������������� ���
class TennisSet
{
private:
	int                      m_setNum;          // ����� ����
	int                      m_countGames;      // ������� ������
	int                      m_curGames;        // ����� �������� ����� (��� ���������� = 0)
	bool                     m_curPlayer;       // ������� ��������
	int                      m_gamesHome;       // ���� ��������� ������ ������ ������������
	int                      m_gamesAway;       // ���� ��������� ������ ������ �� ������
	std::vector<TennisGames> m_dateGamesHome;   // ���������� ������, ����� home
	std::vector<TennisGames> m_dateGamesAway;   // ���������� ������, ����� away

	// �������� ��� �������� ������� � �������
	double                   m_homePoint;
	double                   m_homeTime;
	double                   m_homeTimePoint;
	int                      m_homeMinGames;
	double                   m_awayPoint;
	double                   m_awayTime;
	double                   m_awayTimePoint;
	int                      m_awayMinGames;
	// ������� �������� �� ���:
	double                   m_homeMedPoint;     // ������� ���������� ����������
	double                   m_homeMedTime;      // ������� ����� ������ �����
	double                   m_homeMedTimePoint; // ������� �������� �������� ������� ����������
	double                   m_awayMedPoint;
	double                   m_awayMedTime;
	double                   m_awayMedTimePoint;

	std::string              m_signal;           // home, away, none


	// ������ �������� ����������� ����
	void newGames();
	void cancelCurGames();
	bool endGames(         const bool winner);
	bool checkEndSet(      const bool winner);
	void endSet();                               // ������������ ���� ������ �������� ����!

public:
	TennisSet()
	{

	}

	TennisSet(int setNum, 
		      bool curPlayer)
		: m_setNum(setNum),
		m_countGames(0),
		m_curGames(0),
		m_curPlayer(curPlayer),
		m_gamesHome(0),
		m_gamesAway(0),
		m_homePoint(0),
		m_homeTime(0),
		m_homeTimePoint(0),
		m_homeMinGames(0),
		m_awayPoint(0),
		m_awayTime(0),
		m_awayTimePoint(0),
		m_awayMinGames(0)
	{

	}

	// �������
	int                getSetNum()                   const { return m_setNum; }
	int                getCurGames()                 const { return m_curGames; }
	int                getGamesWinHome()             const { return m_gamesHome; }
	int                getGamesWinAway()             const { return m_gamesAway; }
	int                getGamesHome()                const { return m_dateGamesHome.size(); }
	int                getGamesAway()                const { return m_dateGamesAway.size(); }
	bool               getCurPlayer()                const { return m_curPlayer; }
	std::string        getSignal()                   const { return m_signal; }

	TennisGames&       getActivGames();
	const TennisGames& getActivGames()               const;
	const TennisGames& getHomeGames(const int index) const { return m_dateGamesHome.at(index); }
	const TennisGames& getAwayGames(const int index) const { return m_dateGamesAway.at(index); }

	std::string        getScore()                    const;
	std::string        getSetHeaderHome()            const;
	std::string        getSetHeaderAway()            const;

	friend class TennisMatch;
	friend class TennisOperations;

};

#endif // !TENNISSET_H