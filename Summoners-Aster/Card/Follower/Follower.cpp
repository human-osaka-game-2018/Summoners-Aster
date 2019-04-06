﻿#include "Follower.h"

namespace summonersaster
{
	Follower::Follower(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint)
		: Card(TYPE::FOLLOWER, name, texturePath, cost), m_attack(attack), m_hP(hitPoint)
	{
	}

	Follower::~Follower()
	{
	}

	void Follower::CreateCopy(Card** ppCard)const
	{
		*ppCard = new Follower(m_name, m_texturePath, m_cost, m_attack, m_hP);
	}

	Card& Follower::operator-=(Card* pCard)
	{
		if (pCard->CARD_TYPE == TYPE::FOLLOWER)
		{
			m_hP -= (dynamic_cast<Follower*>(pCard))->Attack();

			return *this;
		}

		return ReduceCost(*pCard);
	}

} // namespace summonersaster
