#include "HP.h"

namespace summonersaster
{


HP::HP()
{
}


HP::~HP()
{
}

void HP::Render()
{
}

void HP::Damaged(unsigned int damage)
{
	m_Hp -= damage;
	if (m_Hp < 0) 
	{
		m_Hp = 0;
		//死亡通知を流す
	}
}

void HP::Recover(unsigned int heal)
{
	m_Hp += heal;
	if (m_Hp > MAX_CAPACITY) 
	{
		m_Hp = MAX_CAPACITY;
	}
}
}
