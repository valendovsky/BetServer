#include "TennisGames.h"

// Обработка нажатия кнопки "Пуск"
void TennisGames::pressing(const Timer& t)
{
	// Проверка положения кнопки
	if (m_pressButton)
	{
		// Кнопка нажата (отжимаем, конец отсчёта)
		m_endTime = t.elapsed();

		// Сохраняем время без этого розыгрыша (на случай отмены)
		m_prevTime = m_lastTime;

		// Суммируем полученный период со временем последнего розыгрыша
		m_lastTime += m_endTime - m_startTime;

		// Флаг - кнопка отжата
		m_pressButton = false;
	}
	else
	{
		// Кнопка не нажата (нажимаем, старт отсчёта)
		m_startTime = t.elapsed();

		// Флаг - кнопка нажата
		m_pressButton = true;
	}
}

// Увеличиваем число розыгрышей
int TennisGames::pointIncrement()
{
	++m_point;

	return m_point;
}

// Уменьшаем число розыгрышей
int TennisGames::pointDecrement()
{
	// Не уменьшаем количество розыгрышей меньше 0
	if (m_point)
	{
		--m_point;
	}

	return m_point;
}

// Отмена розыгрыша
void TennisGames::cancelPoint()
{
	// Возвращаем время до этого розыгрыша
	m_lastTime = m_prevTime;

	// Не обрабатывается случай нарушения последовательности отмены двойной ошибки и розыгрыша
	// будет происходить некорректный возврат времени при отмене розыгрыша
}

// Увеличиваем счётчик двойных ошибок
int TennisGames::incrFault()
{
	// Увеличиваем счётчик ошибок
	++m_doubleFault;
	// и число розыгрышей
	++m_point;

	// Прибавляем время
	m_lastTime += g_timeFault;

	return m_doubleFault;
}

// Уменьшаем двойные ошибки
int TennisGames::decrFault()
{
	// Не уменьшаем количество ошибок меньше 0
	if (m_doubleFault)
	{
		// Уменьшаем счётчик ошибок
		--m_doubleFault;
		// и количества розыгрышей, если они не равны 0
		if (m_point)
			--m_point;

		// Уменьшаем время
		m_lastTime -= g_timeFault;
	}

	return m_doubleFault;
}

// Подсчёты при завершении гейма
void TennisGames::endGames(const std::string& winner)
{
	// Объявляем победителя в гейме
	m_winner = winner;

	// Среднее время одного розыгрыша
	if (m_point) // на ноль делить нельзя
	{
		m_timePoint = m_lastTime / m_point;
	}
	else
		m_timePoint = 0;
}

// Информация по гейму для вывода в файл
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
