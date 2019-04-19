#include "Spell.h"

namespace summonersaster
{
	Spell::Spell(const tstring& name, const tstring& texturePath, int cost) 
		: Card(TYPE::SPELL, name, texturePath, cost)
	{
	}

	Spell::~Spell()
	{
	}

	void Spell::CreateCopy(Card** ppCard)const
	{
		*ppCard = new Spell(m_name, m_texturePath, m_cost);
	}

} // namespace summonersaster
