#include "Spell.h"

namespace summonersaster
{
	Spell::Spell(const tstring& name, const tstring& texturePath, int cost, std::vector<Ability> abilities)
		: Card(TYPE::SPELL, name, texturePath, cost, abilities)
	{
	}

	Spell::Spell(const tstring& name, const tstring& texturePath, int cost, PLAYER_KIND owner, const TCHAR* pTextureKey, std::vector<Ability> abilities)
		: Card(TYPE::SPELL, name, texturePath, cost, owner, pTextureKey, abilities)
	{
	}

	Spell::~Spell()
	{
	}

	void Spell::CreateCopy(Card** ppCard, PLAYER_KIND owner)const
	{
		*ppCard = new Spell(m_name, m_texturePath, m_cost, owner, pTEXTURE_KEY, m_abilities);
	}

} // namespace summonersaster
