#ifndef TENNISGAMES_H
#define TENNISGAMES_H

#include <string>

#include "Timer.h"
#include "Constants.h"


// Результаты гейма для обрабатываемых игр
class TennisGames
{
private:
	bool        m_emptyGames;  // флаг, если требуется вернуть пустой гейм
	int         m_gamesNum;    // общий номер гейма
	int         m_point;       // количество розыгрышей
	bool        m_pressButton; // флаг нажатия кнопки (true - кнопка нажата)
	double      m_startTime;   // начальное время периода
	double      m_endTime;     // конечное время периода
	double      m_prevTime;    // время без последнего розыгрыша
	double      m_lastTime;    // сумма времени всех розыгрышей
	double      m_timePoint;   // среднее время одного розыгрыша
	int         m_doubleFault; // счётчик двойных ошибок
	std::string m_winner;      // победитель в этом гейме

	// Методы изменяющие показатели гейма
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

	// Геттеры
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