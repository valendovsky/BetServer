#ifndef TENNISMATCH_H
#define TENNISMATCH_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "ParsTennis.h"
#include "TennisSet.h"
#include "Constants.h"


// Класс для обрабатываемых игр
class TennisMatch
{
private:
	std::string                m_gameId;       // id игры
	std::string                m_dateGame;     // дата проведения игры
	std::string                m_tour;         // турнир
	std::string                m_court;        // покрытие
	std::string                m_refGame;      // ссылка на игру на сайте
	std::string                m_timeGame;     // Время игры
	std::string                m_playHome;     // игрок играющий дома
	std::string                m_playAway;     // игрок играющий в гостях
	std::string                m_worker;       // контролёр отсматривающий игру
	int                        m_curSet;       // номер текущего сета (при отсутствии = 0)
	std::map<int, TennisSet>   m_dataSet;      // статистика по не отменённым сетам
	std::map<int, std::string> m_reportCancel; // пояснения к отменённым сетам
	std::map<int, std::string> m_reportEnd;    // пояснения для конца сета

	// Данные о закрытии игры и сохранении статистики
	std::string                m_typeEnd;
	int                        m_setNumArch;


	// Методы фиксирующие игровые показатели
	void        setSetNum(      const int setNum,
		                        const bool player);

	void        setSetNumArch(  const int newSetNumArch)    { m_setNumArch = newSetNumArch; }

	void        cancelSet(      const int setNum,
		                        const std::string& message);

	std::string forUser()                                   const;

	bool        checkSet(       const int setNum)           const;

	std::string endSetGetSignal(const std::string& message);

	void        endTennis(      const std::string& typeEnd);

public:
	TennisMatch()
	{

	}

	TennisMatch(const std::string& gameId,
		       const std::string& dateGame,
		       const std::string& tour,
		       const std::string& court,
		       const std::string& refGame,
		       const std::string& timeGame,
		       const std::string& playHome,
		       const std::string& playAway,
		       const std::string& worker)
		: m_gameId(gameId),
		m_dateGame(dateGame),
		m_tour(tour),
		m_court(court),
		m_refGame(refGame),
		m_timeGame(timeGame),
		m_playHome(playHome),
		m_playAway(playAway),
		m_worker(worker),
		m_curSet(0),
		m_typeEnd(ComPhr::NO_SAVE),
		m_setNumArch(0)
	{

	}

	// Создание объекта через данные из спарсенных игр
	TennisMatch(ParsTennis& pars)
		: m_gameId(pars.getGameId()),
		m_dateGame(pars.getDateGame()),
		m_tour(pars.getTour()),
		m_court(pars.getCourt()),
		m_refGame(pars.getRefGame()),
		m_timeGame(pars.getTimeGame()),
		m_playHome(pars.getPlayHome()),
		m_playAway(pars.getPlayAway()),
		m_worker(pars.getWorker()),
		m_curSet(0),
		m_typeEnd(ComPhr::NO_SAVE),
		m_setNumArch(0)
	{

	}

	// Геттеры
	std::string                 getGameId()                      const { return m_gameId; }
	std::string                 getDateGame()                    const { return m_dateGame; }
	std::string                 getTour()                        const { return m_tour; }
	std::string                 getCourt()                       const { return m_court; }
	std::string                 getRefGame()                     const { return m_refGame; }
	std::string                 getTimeGame()                    const { return m_timeGame; }
	std::string                 getPlayHome()                    const { return m_playHome; }
	std::string                 getPlayAway()                    const { return m_playAway; }
	std::string                 getWorker()                      const { return m_worker; }
	int                         getCurSet()                      const { return m_curSet; }
	int                         getSetNumArch()                  const { return m_setNumArch; }

	TennisSet&                  getCurDataSet()                        { return m_dataSet.at(m_curSet); }
	const TennisSet&            getCurDataSet()                  const { return m_dataSet.at(m_curSet); } // перегрузка
	TennisSet&                  getDataSet(     const int setNum)      { return m_dataSet.at(setNum); }
	std::map<int, TennisSet>&   getData()                              { return m_dataSet; }
	std::map<int, std::string>& getReportCancel()                      { return m_reportCancel; }

	std::string                 getTennisHeader()                const;
	std::string                 getEndReport(   const int index) const { return m_reportEnd.at(index); }


	friend std::ostream& operator<< (std::ostream& out, const TennisMatch& tennis);
	friend class TennisOperations;

};

#endif // !TENNISMATCH_H