﻿#include "Spell.h"

namespace summonersaster
{
	Spell::Spell(const tstring& name, const tstring& texturePath, int cost, PLAYER_KIND owner)
		: Card(TYPE::SPELL, name, texturePath, cost, owner)
	{
	}

	Spell::Spell(const tstring& name, const tstring& texturePath, int cost, PLAYER_KIND owner, const TCHAR* pTextureKey)
		: Card(TYPE::SPELL, name, texturePath, cost, owner, pTextureKey)
	{
	}

	Spell::~Spell()
	{
	}

	void Spell::CreateCopy(Card** ppCard, PLAYER_KIND owner)const
	{
		*ppCard = new Spell(m_name, m_texturePath, m_cost, owner, pTEXTURE_KEY);
	}

} // namespace summonersaster
