#ifndef HAVINGCARDS_H
#define HAVINGCARDS_H
#include <vector>
#include "Scene/MainScene/BattleObject.h"
#include "Card.h"
#include "Spell/Spell.h"
#include "Follower/Follower.h"
#include "Weapon/Weapon.h"
#include "CardFolder.h"
#include "Button.h"

namespace summonersaster
{
	class HavingCards :public BattleObject
{
public:
	struct Having
	{
	public:
		Card* pCard = nullptr;
		Button* m_pSendDeckButton = nullptr;

		Having(Card* card, Button* button)
		{
			pCard = card;
			m_pSendDeckButton = button;
		}
	};

	HavingCards(PLAYER_KIND owner, const D3DXVECTOR2& texturCenter);
	~HavingCards();
	void Load(PLAYER_KIND owner);

	void Render();

	void Update();

	Card* OnButton();

	void LocaleButton();

private:
	std::vector<Having*> m_HavingCards;
	D3DXVECTOR2 m_TexturCenter = { 0.0f, 0.0f };

	RectSize m_windowSize;
	D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

	GameFramework& m_rGameFramework = GameFramework::GetRef();

};
}
#endif
