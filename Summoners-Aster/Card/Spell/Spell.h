#ifndef SPELL_H
#define SPELL_H

#include "Card\Card.h"

namespace summonersaster
{
	class Spell :public Card
	{
	public:
		Spell(const tstring& name, const tstring& texturePath, int cost);
		~Spell();
		
		/// <summary>
		/// 自身のコピーを動的確保する
		/// </summary>
		/// <param name="ppCard">コピーされるカードのポインタのポインタ</param>
		void CreateCopy(Card** ppCard) const override;

	protected:
		Spell(Spell& spell) = delete;

		Spell& operator=(Spell& spell) = delete;
	};
} // namespace summonersaster

#endif // !SPELL_H
