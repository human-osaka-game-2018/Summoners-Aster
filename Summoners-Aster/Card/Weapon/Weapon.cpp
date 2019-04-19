#include "Weapon.h"

namespace summonersaster
{
	Weapon::Weapon(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint)
		: Card(TYPE::WEAPON, name, texturePath, cost), m_attack(attack), m_hP(hitPoint)
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
