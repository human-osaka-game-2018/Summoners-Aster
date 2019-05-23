#ifndef WEAPON_H
#define WEAPON_H

#include "Card\Card.h"

namespace summonersaster
{
	class Weapon :public Card
	{
	public:
		Weapon(const tstring& name, const tstring& texturePath, int cost, int hitPoint, const Ability& ability);
		Weapon(const tstring& name, const tstring& texturePath, int cost, int hitPoint, PLAYER_KIND owner, const TCHAR* pTextureKey, const Ability& ability);
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

		void Render(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType = RENDERING_TYPE::MIDDLE, const Degree& rotationZ = Degree(0))override;

	private:
		Weapon(Weapon& weapon) = delete;

		Weapon& operator=(Weapon& weapon) = delete;

		void RenderHP(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType);

		Stream* m_pHPStream = nullptr;

		int m_hP;
	};
} // namespace summonersaster

#endif // !WEAPON_H
