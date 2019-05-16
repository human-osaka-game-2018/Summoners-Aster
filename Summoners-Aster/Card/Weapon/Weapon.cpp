#include "Weapon.h"

namespace summonersaster
{
	Weapon::Weapon(const tstring& name, const tstring& texturePath, int cost, int hitPoint, const Ability& ability)
		: Card(TYPE::WEAPON, name, texturePath, cost, ability), m_hP(hitPoint)
	{
	}

	Weapon::Weapon(const tstring& name, const tstring& texturePath, int cost, int hitPoint, PLAYER_KIND owner, const TCHAR* pTextureKey, const Ability& ability)
		: Card(TYPE::WEAPON, name, texturePath, cost, owner, pTextureKey, ability), m_hP(hitPoint)
	{
	}

	Weapon::~Weapon()
	{
	}

	void Weapon::CreateCopy(Card** ppCard, PLAYER_KIND owner)const
	{
		*ppCard = new Weapon(m_name, m_texturePath, m_cost, m_hP, owner, pTEXTURE_KEY, m_ability);
	}

} // namespace summonersaster
