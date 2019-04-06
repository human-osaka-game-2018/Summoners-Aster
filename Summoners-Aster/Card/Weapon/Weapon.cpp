#include "Weapon.h"

namespace summonersaster
{
	Weapon::Weapon(const tstring& Name, const tstring& TexturePath, int Cost, int Attack, int HitPoint) 
		: Card(TYPE::WEAPON, Name, TexturePath, Cost), m_attack(Attack), m_hP(HitPoint)
	{

	}

	Weapon::~Weapon()
	{

	}

	void Weapon::CreateCopy(Card** ppCard)const
	{
		*ppCard = new Weapon(m_name, m_texturePath, m_cost, m_attack, m_hP);
	}

} // namespace summonersaster
