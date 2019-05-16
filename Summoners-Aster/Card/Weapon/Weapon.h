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

	private:
		Weapon(Weapon& weapon) = delete;

		Weapon& operator=(Weapon& weapon) = delete;

		int m_hP;
	};
} // namespace summonersaster

#endif // !WEAPON_H
