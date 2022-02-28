#include "TennisSet.h"

// Создаёт новый гейм
void TennisSet::newGames()
{
	// При инициализации m_countGames = 0, но первый гейм = 1
	m_curGames = ++m_countGames;

	// Назначаем текущего раздающего игрока
	if (m_curPlayer) // true - home player
	{
		m_dateGamesHome.push_back(m_curGames);
	}
	else // false - away player
	{
		m_dateGamesAway.push_back(m_curGames);
	}
}

// Удаляет текущий сет
void TennisSet::cancelCurGames()
{
	if (m_curGames) // должен быть текущий гейм
	{
		if (m_curPlayer) // true - home player
		{
			m_dateGamesHome.pop_back();
		}
		else // false - away player
		{
			m_dateGamesAway.pop_back();
		}

		// Обнуляем текущий гейм и меняем общее значение геймов
		m_curGames = 0;
		--m_countGames;
	}
}

// Открывает активный гейм
TennisGames& TennisSet::getActivGames()
{
	// Возвращаем соответствующий гейм в зависимости от подающего
	if (m_curPlayer)
		return m_dateGamesHome.back();
	else
		return m_dateGamesAway.back();
}

// Перегрузка метода для константных объектов
const TennisGames& TennisSet::getActivGames() const
{
	// Возвращаем соответствующий гейм в зависимости от подающего
	if (m_curPlayer)
		return m_dateGamesHome.back();
	else
		return m_dateGamesAway.back();
}

// Закрывает гейм
// и определяет надо ли закрывать сет
bool TennisSet::endGames(const bool winner)
{
	std::string winStr;
	// Начисляем очко победителю
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

	// Фиксируем статистику подающего
	if (m_curPlayer)
	{
		m_dateGamesHome.back().endGames(winStr);
	}
	else
	{
		m_dateGamesAway.back().endGames(winStr);
	}

	// Нет активного гейма
	m_curGames = 0;

	// Надо ли закрывать сет
	if (checkEndSet(winner))
		return true; // закрываем сет

	// Меняем подающего игрока
	m_curPlayer = !m_curPlayer;

	return false; // сет закрывать не надо
}

// Проверяет условия закрытия сета
bool TennisSet::checkEndSet(const bool winner)
{
	/*
	* Логика условий закрытия сета удалена.
	* Предоставьте своинструкции!
	*/

	return true;
}

// Возвращает текущий счёт в сете
std::string TennisSet::getScore() const
{
	std::string score = std::to_string(m_gamesHome) + " - " + std::to_string(m_gamesAway);

	return score;
}

// Завершает сет
void TennisSet::endSet()
{
	/* 
	* Логика закрытия сета удалена.
	* Предоставьте свою логику закрытия сета!
	*/
}

// Выводит среднюю статистику игрока home по сету для файла
std::string TennisSet::getSetHeaderHome() const
{
	std::string header = 
		std::to_string(m_gamesHome) + "," +
		std::to_string(m_homeMedPoint) + "," +
		std::to_string(m_homeMedTime) + "," +
		std::to_string(m_homeMedTimePoint) + ",doubleFault"; // none - графа под двойными ошибками

	return header;
}

// Выводит среднюю статистику игрока away по сету для файла
std::string TennisSet::getSetHeaderAway() const
{
	std::string header = 
		std::to_string(m_gamesAway) + "," +
		std::to_string(m_awayMedPoint) + "," +
		std::to_string(m_awayMedTime) + "," +
		std::to_string(m_awayMedTimePoint) + ",doubleFault";

	return header;
}
