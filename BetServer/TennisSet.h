#ifndef TENNISSET_H
#define TENNISSET_H

#include <vector>
#include <string>

#include "TennisGames.h"
#include "Constants.h"


// Статистка сетов обрабатываемых игр
class TennisSet
{
private:
	int                      m_setNum;          // номер сета
	int                      m_countGames;      // счётчик геймов
	int                      m_curGames;        // номер текущего гейма (при отсутствии = 0)
	bool                     m_curPlayer;       // текущий подающий
	int                      m_gamesHome;       // счёт выиграных геймов игрока принимающего
	int                      m_gamesAway;       // счёт выиграных геймов игрока на выезде
	std::vector<TennisGames> m_dateGamesHome;   // статистика геймов, подаёт home
	std::vector<TennisGames> m_dateGamesAway;   // статистика геймов, подаёт away

	// Значения для принятия решения о сигнале
	double                   m_homePoint;
	double                   m_homeTime;
	double                   m_homeTimePoint;
	int                      m_homeMinGames;
	double                   m_awayPoint;
	double                   m_awayTime;
	double                   m_awayTimePoint;
	int                      m_awayMinGames;
	// Средние значения за сет:
	double                   m_homeMedPoint;     // среднее количество розыгрышей
	double                   m_homeMedTime;      // среднее время одного гейма
	double                   m_homeMedTimePoint; // среднее значение среднего времени розыгрышей
	double                   m_awayMedPoint;
	double                   m_awayMedTime;
	double                   m_awayMedTimePoint;

	std::string              m_signal;           // home, away, none


	// Методы фиксации показателей сета
	void newGames();
	void cancelCurGames();
	bool endGames(         const bool winner);
	bool checkEndSet(      const bool winner);
	void endSet();                               // Предоставьте свою логику закрытия сета!

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

	// Геттеры
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