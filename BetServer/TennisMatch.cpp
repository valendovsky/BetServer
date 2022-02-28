#include "TennisMatch.h"

// ���������� �� ���� ��� ������ � ����
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

// ��������� ��� � ����
void TennisMatch::setSetNum(const int setNum, const bool player)
{
	m_curSet = setNum;

	// ��������� ������ � ��������� ���������� �� �����
	m_dataSet[setNum] = TennisSet(setNum, player);
}

// �������� ��� � ��������� ��������� �� ������
void TennisMatch::cancelSet(const int setNum, const std::string& message)
{
	// ���������� ����� �������� ���� ��� �������� ��������
	if (setNum == m_curSet)
		m_curSet = 0;

	// ������� ������ ���� �� ��������� ���������� �� �����
	m_dataSet.erase(setNum);

	// ������� ��������� � ����������� �����
	m_reportEnd.erase(setNum);

	// ��������� ��������� � ����������� ����
	m_reportCancel[setNum] = message;
}

// ��� ������ ���������� �� ���� ���������� �� ��������
std::string TennisMatch::forUser() const
{
	std::string forSend = m_dateGame + " / " + m_timeGame + "\n" + m_tour + ", "
		+ m_court + "\n" + m_playHome + " - " + m_playAway;

	return forSend;
}

// ��������� ������� ���� � ����������
bool TennisMatch::checkSet(const int setNum) const
{
	// ���� �� �������, �� ���������� 0
	return m_dataSet.count(setNum) > 0;
}

// ���������� ����� ����
std::string TennisMatch::endSetGetSignal(const std::string& message)
{
	// ��������� ��� � ��������� ����������
	m_dataSet.at(m_curSet).endSet();

	// �������� �������� ������� ��� ��������
	std::string signal = m_dataSet.at(m_curSet).getSignal();

	// ��������� ����������� ������������ � ����
	m_reportEnd[m_curSet] = message;

	// �������� ������� ��� (��� �������� �����)
	m_curSet = 0;

	return signal;
}

// ��������� ��� �������� ����, ��������� ��� ������
void TennisMatch::endTennis(const std::string& typeEnd)
{
	m_typeEnd = typeEnd;
}

// ��� ������������
std::ostream& operator<< (std::ostream& out, const TennisMatch& tennis)
{
	out << "Tennis game id: " << tennis.m_gameId << " " << tennis.m_dateGame << " " << tennis.m_tour 
		<< " " << tennis.m_court << " " << tennis.m_refGame << " " << tennis.m_timeGame << " " 
		<< tennis.m_playHome << " " << tennis.m_playAway << " " << tennis.m_worker;

	return out;
}
