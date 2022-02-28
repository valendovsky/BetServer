#include "TennisMatch.h"

// Информация по игре для вывода в файл
std::string TennisMatch::getTennisHeader() const
{
	std::string header = m_gameId + "," +
		m_dateGame + "," +
		m_tour + "," +
		m_court + "," +
		m_refGame + "," +
		m_timeGame;

	return header;
}

// Добавляет сет к игре
void TennisMatch::setSetNum(const int setNum, const bool player)
{
	m_curSet = setNum;

	// Добавляем объект в структуру статистики по сетам
	m_dataSet[setNum] = TennisSet(setNum, player);
}

// Отменяет сет и добавляет пояснение по отмене
void TennisMatch::cancelSet(const int setNum, const std::string& message)
{
	// Сбрасываем номер текущего сета при удалении текущего
	if (setNum == m_curSet)
		m_curSet = 0;

	// Удаляем объект сета из структуры статистики по сетам
	m_dataSet.erase(setNum);

	// Удаляем пояснение к завершенным сетам
	m_reportEnd.erase(setNum);

	// Добавляем пояснение к отмененному сету
	m_reportCancel[setNum] = message;
}

// Для вывода информации по игре контролёрам на страницу
std::string TennisMatch::forUser() const
{
	std::string forSend = m_dateGame + " / " + m_timeGame + "\n" + m_tour + ", "
		+ m_court + "\n" + m_playHome + " - " + m_playAway;

	return forSend;
}

// Проверяет наличие сета в статистике
bool TennisMatch::checkSet(const int setNum) const
{
	// Если не найдено, то возвращает 0
	return m_dataSet.count(setNum) > 0;
}

// Обработака конца сета
std::string TennisMatch::endSetGetSignal(const std::string& message)
{
	// Завершаем сет и подбиваем статистику
	m_dataSet.at(m_curSet).endSet();

	// Получаем значение сигнала для возврата
	std::string signal = m_dataSet.at(m_curSet).getSignal();

	// Сохраняем комментарий пользователя к сету
	m_reportEnd[m_curSet] = message;

	// Обнуляем текущий сет (нет открытых сетов)
	m_curSet = 0;

	return signal;
}

// Фиксирует тип закрытия игры, временное или полное
void TennisMatch::endTennis(const std::string& typeEnd)
{
	m_typeEnd = typeEnd;
}

// Для тестирования
std::ostream& operator<< (std::ostream& out, const TennisMatch& tennis)
{
	out << "Tennis game id: " << tennis.m_gameId << " " << tennis.m_dateGame << " " << tennis.m_tour 
		<< " " << tennis.m_court << " " << tennis.m_refGame << " " << tennis.m_timeGame << " " 
		<< tennis.m_playHome << " " << tennis.m_playAway << " " << tennis.m_worker;

	return out;
}
