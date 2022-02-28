#include "ParsTennis.h"

// Для тестирования
std::ostream& operator<< (std::ostream& out, const ParsTennis& tennis)
{
	out << "Tennis game id: " << tennis.m_gameId << " " << tennis.m_dateGame << " " 
		<< tennis.m_tour << " " << tennis.m_court << " " << tennis.m_timeBreak << " " << tennis.m_refGame << " "
		<< tennis.m_timeGame << " " << tennis.m_playHome << " " << tennis.m_playAway << " " << tennis.m_worker;

	return out;
}
