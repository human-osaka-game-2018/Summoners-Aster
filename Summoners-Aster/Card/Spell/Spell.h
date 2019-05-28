#ifndef SPELL_H
#define SPELL_H

#include "Card\Card.h"

namespace summonersaster
{
	class Spell :public Card
	{
	public:
		Spell(const tstring& name, const tstring& texturePath, int cost, std::vector<Ability> abilities);
		Spell(const tstring& name, const tstring& texturePath, int cost, PLAYER_KIND owner, const TCHAR* pTextureKey, std::vector<Ability> abilities);

		~Spell();
		
		/// <summary>
		/// 自身のコピーを動的確保する
		/// </summary>
		/// <param name="ppCard">コピーされるカードのポインタのポインタ</param>
		void CreateCopy(Card** ppCard, PLAYER_KIND owner) const override;

	protected:
		Spell(Spell& spell) = delete;

		Spell& operator=(Spell& spell) = delete;
	};
} // namespace summonersaster

#endif // !SPELL_H
