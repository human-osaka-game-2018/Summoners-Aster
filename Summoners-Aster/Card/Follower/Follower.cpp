﻿#include "Follower.h"

namespace summonersaster
{
	using namespace gameframework;

	Follower::Follower(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint, const Ability& ability)
		: Card(TYPE::FOLLOWER, name, texturePath, cost, ability), m_attack(attack), m_hP(hitPoint)
	{
		InitializeStream();
	}

	Follower::Follower(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint, PLAYER_KIND owner, const TCHAR* pTextureKey, const Ability& ability)
		: Card(TYPE::FOLLOWER, name, texturePath, cost, owner, pTextureKey, ability), m_attack(attack), m_hP(hitPoint)
	{
		InitializeStream();
	}

	Follower::~Follower()
	{
		delete m_pAttackStream;
		delete m_pHPStream;
	}

	void Follower::CreateCopy(Card** ppCard, PLAYER_KIND owner)const
	{
		*ppCard = new Follower(m_name, m_texturePath, m_cost, m_attack, m_hP, owner, pTEXTURE_KEY, m_ability);
	}

	Follower& Follower::operator-=(const Follower* pFollower)
	{
		m_hP -= pFollower->Attack();

		return *this;
	}
	void Follower::Render(const D3DXVECTOR3& center, const RectSize& size, const Degree& rotationZ)
	{
		RenderCard(center, size, rotationZ);
		RenderHP(center, size);
		RenderAttack(center, size);
	}

	void Follower::RenderHP(const D3DXVECTOR3& center, const RectSize& size)
	{
		m_pRect->Render(m_rGameFramework.GetTexture(_T("HP")));
		m_pHPStream->SetTopLeft(D3DXVECTOR2(center.x - size.m_width * 0.38f, center.y + size.m_height * 0.34f));

		if (m_isInCemetery) return;

		int hPForRendering = algorithm::Tertiary(m_hP < 0, 0, m_hP);

		(*m_pHPStream) = totstring(hPForRendering);
		m_pHPStream->Render(m_rGameFramework.GetFont(_T("CARD")), DT_CENTER);
	}

	void Follower::RenderAttack(const D3DXVECTOR3& center, const RectSize& size)
	{
		m_pRect->Render(m_rGameFramework.GetTexture(_T("ATTACK")));
		m_pAttackStream->SetTopLeft(D3DXVECTOR2(center.x + size.m_width * 0.38f, center.y + size.m_height * 0.34f));

		if (m_isInCemetery) return;

		(*m_pAttackStream) = totstring(m_attack);
		m_pAttackStream->Render(m_rGameFramework.GetFont(_T("CARD")), DT_CENTER);
	}
} // namespace summonersaster
