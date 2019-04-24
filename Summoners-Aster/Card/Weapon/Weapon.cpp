#include "Weapon.h"

namespace summonersaster
{
	Weapon::Weapon(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint, PLAYER_KIND owner)
		: Card(TYPE::WEAPON, name, texturePath, cost, owner), m_attack(attack), m_hP(hitPoint)
	{
	}

	Weapon::Weapon(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint, PLAYER_KIND owner, const TCHAR* pTextureKey)
		: Card(TYPE::WEAPON, name, texturePath, cost, owner, pTextureKey), m_attack(attack), m_hP(hitPoint)
	{
	}

	Weapon::~Weapon()
	{
	}

	void Weapon::CreateCopy(Card** ppCard, PLAYER_KIND owner)const
	{
		*ppCard = new Weapon(m_name, m_texturePath, m_cost, m_attack, m_hP, owner, pTEXTURE_KEY);
	}

} // namespace summonersaster
