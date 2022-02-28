#ifndef PARSTENNIS_H
#define PARSTENNIS_H

#include <iostream>
#include <string>


// Класс для предварительно спарсенных игр
class ParsTennis
{
private:
	std::string m_gameId;
	std::string m_dateGame;
	std::string m_tour;
	std::string m_court;
	short int   m_timeBreak;
	std::string m_refGame;
	std::string m_timeGame;
	std::string m_playHome;
	std::string m_playAway;
	std::string m_worker;

public:
	ParsTennis()
	{

	}

	ParsTennis(std::string gameId, 
		       std::string dateGame, 
		       std::string tour, 
		       std::string court, 
		       short int timeBreak,
		       std::string refGame, 
		       std::string timeGame, 
		       std::string playHome, 
		       std::string playAway, 
		       std::string worker)
		       : m_gameId(gameId),
		       m_dateGame(dateGame),
		       m_tour(tour),
		       m_court(court),
		       m_timeBreak(timeBreak),
		       m_refGame(refGame),
		       m_timeGame(timeGame),
		       m_playHome(playHome),
		       m_playAway(playAway),
		       m_worker(worker)
	{

	}

	// Геттеры
	std::string getGameId()    { return m_gameId; }
	std::string getDateGame()  { return m_dateGame; }
	std::string getTour()      { return m_tour; }
	std::string getCourt()     { return m_court; }
	short int   getTimeBreak() { return m_timeBreak; }
	std::string getRefGame()   { return m_refGame; }
	std::string getTimeGame()  { return m_timeGame; }
	std::string getPlayHome()  { return m_playHome; }
	std::string getPlayAway()  { return m_playAway; }
	std::string getWorker()    { return m_worker; }

	friend std::ostream& operator<< (std::ostream& out, const ParsTennis& tennis);
};

#endif // !PARSTENNIS_H