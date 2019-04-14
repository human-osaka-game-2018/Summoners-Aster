#include "MP.h"


namespace summonersaster
{

MP::MP()
{
}


MP::~MP()
{
}

void MP::Render()
{
}

void MP::IncreaseCapacity()
{
	if (m_Capacity == MAX_CAPACITY) return;
	++m_Capacity;
}

bool MP::Paid(const unsigned int paidMp)
{
	if (paidMp > m_UsablePoint) return false;
	m_UsablePoint -= paidMp;
	return true;
}

void MP::RenewUsablePoints()
{
	m_UsablePoint = m_Capacity;
}

}
