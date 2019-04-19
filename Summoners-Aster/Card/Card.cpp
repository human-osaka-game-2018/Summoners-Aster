﻿#include "Card.h"

using namespace gameframework;

namespace summonersaster
{
	Card::~Card()
	{
		Finalize();
	}

	void Card::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);

		LoadResource();
	}

	void Card::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("カシオペア"), m_texturePath.c_str());
	}

	void Card::Finalize()
	{
		Release();
	}

	void Card::Release()
	{
		delete m_pRect;
		//m_rGameFramework.ReleaseTexture(pTEXTURE_KEY);
	}

	void Card::Update()
	{

	}

	void Card::Render(const D3DXVECTOR3& center, const RectSize& size, const Degree& rotationZ)
	{
		m_pRect->GetCenter() = { center.x, center.y, center.z };
		m_pRect->SetSize(size);
		m_pRect->SetRotationZ(rotationZ);

		m_pRect->Render(m_rGameFramework.GetTexture(_T("カシオペア")));
	}

	Card::Card(TYPE type, const tstring& name, const tstring& texturePath, int cost)
		: CARD_TYPE(type), m_name(name), m_texturePath(texturePath), m_cost(cost), pTEXTURE_KEY(m_name.c_str())
	{
		Initialize();
	}
} // namespace summonersaster
