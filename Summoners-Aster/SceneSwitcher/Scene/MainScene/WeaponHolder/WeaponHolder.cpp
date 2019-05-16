#include "WeaponHolder.h"

namespace summonersaster
{
	WeaponHolder::WeaponHolder(const D3DXVECTOR3& centerWindowMulti) 
		:Object(centerWindowMulti.z)
	{
		D3DXVECTOR3 center =
		{
			m_windowCenter.x * centerWindowMulti.x,
			m_windowCenter.y * centerWindowMulti.y,
			m_z
		};

		Initialize();
		Locale(center);
	}

	WeaponHolder::~WeaponHolder()
	{
		Finalize();
	}

	void WeaponHolder::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);
	}

	void WeaponHolder::Finalize()
	{
		delete m_pWeapon;
		delete m_pRect;
	}

	void WeaponHolder::Render()
	{
		m_pRect->Render(nullptr);

		if (!m_pWeapon) return;

		m_pWeapon->Render(m_pRect->GetCenter(), m_pRect->GetSize());
	}

	void WeaponHolder::ActivateWeapon()
	{
		if (!m_pWeapon) return;

		AbilityExecutor::Execute(m_pWeapon);

		m_pWeapon->DecrementHP();
	}

	void WeaponHolder::Locale(const D3DXVECTOR3& center)
	{
		RectSize cardSize;
		cardSize.m_height = 1.4f * (cardSize.m_width = m_windowSize.m_height * 0.15f);

		m_pRect->SetCenterAndSize(center, cardSize);

		m_pRect->SetColor(0xAA000000);
	}
}
