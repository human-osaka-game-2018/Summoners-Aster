﻿#ifndef WEAPON_HOLDER_H
#define WEAPON_HOLDER_H

#include <vector>
#include <functional>

#include <d3dx9.h>

#include <Gameframework.h>

#include "Object.h"
#include "Card.h"
#include "Weapon/Weapon.h"
#include "MovableCard/MovableCard.h"
#include "Ability/AbilityExecutor.h"

namespace summonersaster
{
	using gameframework::GameFrameworkFactory;
	using gameframework::DirectX8Mouse;
	using gameframework::Vertices;
	using gameframework::RectSize;

	/// <summary>
	/// ウェポンを保管する場所
	/// </summary>
	class WeaponHolder :public Object
	{
	public:
		explicit WeaponHolder(const D3DXVECTOR3& centerWindowMulti);

		~WeaponHolder();

		/// <summary>
		/// 初期化を行う
		/// </summary>
		void Initialize()override;

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		void Finalize()override;

		/// <summary>
		/// 描画を行う
		/// </summary>
		void Render()override;

		void ActivateWeapon();
		
		inline Card* HCard()
		{
			return m_pWeapon;
		}

		inline Weapon* HWeapon()
		{
			return m_pWeapon;
		}

		inline void HWeapon(Weapon* pWeapon)
		{
			m_pWeapon = pWeapon;
		}

		inline Weapon** HHolder()
		{
			return &m_pWeapon;
		}

		inline const tstring HavingWeaponName()
		{
			if (!m_pWeapon) return _T("");

			return m_pWeapon->Name();
		}

		inline bool ShouldDestroyed()
		{
			return m_pWeapon->ShouldDestroyed();
		}

		inline Vertices* HCollisionRect()
		{
			return m_pRect;
		}

		inline Card* LeaveCard()
		{
			Card* pCard = m_pWeapon;
			m_pWeapon = nullptr;

			return pCard;
		}

	private:
		WeaponHolder(WeaponHolder& movableCard) = delete;

		WeaponHolder& operator=(WeaponHolder& movableCard) = delete;

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();

		void Locale(const D3DXVECTOR3& center);

		Vertices* m_pRect = nullptr;

		Weapon* m_pWeapon = nullptr;

	};
} // namespace summonersaster

#endif // !WEAPON_HOLDER_H
