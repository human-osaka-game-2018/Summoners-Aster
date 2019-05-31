#ifndef WEAPON_H
#define WEAPON_H

#include "Card\Card.h"
#include "Field.h"

namespace summonersaster
{
	class Weapon :public Card
	{
	public:
		Weapon(const tstring& name, const tstring& texturePath, int cost, int hitPoint, std::vector<Ability> abilities);
		Weapon(const tstring& name, const tstring& texturePath, int cost, int hitPoint, PLAYER_KIND owner, const TCHAR* pTextureKey, std::vector<Ability> abilitiesy);

		~Weapon();

		/// <summary>
		/// 自身のコピーを動的確保する
		/// </summary>
		/// <param name="ppCard">コピーされるカードのポインタのポインタ</param>
		void CreateCopy(Card** ppCard, PLAYER_KIND owner) const override;

		inline void DecrementHP()
		{
			if (--m_hP > 0) return;

			m_shouldDestroyed = true;
		}

		inline FollowerData* GetAttackingFollower()
		{
			return m_pAttackingFollower;
		}

		inline void SetAttackingFollower(FollowerData* pAttackingFollower)
		{
			m_pAttackingFollower = pAttackingFollower;
		}

		void Render(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType = RENDERING_TYPE::MIDDLE, const Degree& rotationZ = Degree(0))override;

	private:
		Weapon(Weapon& weapon) = delete;

		Weapon& operator=(Weapon& weapon) = delete;

		void RenderHP(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType);

		Stream* m_pHPStream = nullptr;

		int m_hP;

		//! このウェポンに攻撃してきたフォロワーのインデックス、カード効果で使う
		FollowerData* m_pAttackingFollower = nullptr;
	};
} // namespace summonersaster

#endif // !WEAPON_H
