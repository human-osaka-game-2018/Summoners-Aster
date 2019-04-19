#ifndef WEAPON_H
#define WEAPON_H

#include "Card\Card.h"

namespace summonersaster
{
	class Weapon :public Card
	{
	public:
		Weapon(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint);
		~Weapon();

		/// <summary>
		/// 自身のコピーを動的確保する
		/// </summary>
		/// <param name="ppCard">コピーされるカードのポインタのポインタ</param>
		void CreateCopy(Card** ppCard) const override;

	private:
		Weapon(Weapon& weapon) = delete;

		Weapon& operator=(Weapon& weapon) = delete;

		int m_hP;
		int m_attack;
	};
} // namespace summonersaster

#endif // !WEAPON_H
