#ifndef EDIT_DECK_H
#define EDIT_DECK_H

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

class EditDeck :public BattleObject
{
public:
	struct Editor
	{
	public:
		Card* pCard = nullptr;
		Button* pEraseButton = nullptr;

		Editor(Card* card, Button* button)
		{
			pCard = card;
			pEraseButton = button;
		}
	};

	EditDeck(const tstring& deckName, const D3DXVECTOR2& texturCenter = D3DXVECTOR2(1529.0f, 640.0f));
	~EditDeck();
	void Render();
	void Update();
	void Destroy();

	/// <summary>
	/// デッキのロード
	/// </summary>
	/// <param name="owner">カードの所有者</param>
	void Load(PLAYER_KIND owner);

	/// <summary>
	/// カード追加
	/// </summary>
	/// <param name="card">もらうカードクラスポインタ</param>
	void AddCard(Card* card);

	/// <summary>
	/// カード枚数を数えてデッキに追加できるか判定する
	/// </summary>
	/// <param name="card">数えてほしいカード</param>
	/// <returns>デッキに入れることが可能ならtrue</returns>
	bool CountCard(Card* card);

	/// <summary>
	/// デッキからカードを取り除く
	/// </summary>
	/// <param name="editor">取り除く編集カード構造体</param>
	void CardErase(Editor* editor);

	/// <summary>
	/// ボタン位置の設定
	/// </summary>
	void LocaleButton();

	/// <summary>
	/// デッキのセーブ
	/// </summary>
	void SaveDack();

	inline int GetQuantites() const
	{
		return static_cast<int>(m_EditCards.size());
	}

	inline Card* GetCards(int i)
	{
		return m_EditCards[i]->pCard;
	}

private:
	std::vector<Editor*> m_EditCards;
	const int LIMIT_CAPACITY = 40;
	const int LIMIT_CARD_CAPACITY = 6;

	const tstring& DECK_NAME;

	D3DXVECTOR2 m_TexturCenter = { 0.0f, 0.0f };

	RectSize m_windowSize;
	D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

	GameFramework& m_rGameFramework = GameFramework::GetRef();
	HWND m_Hwnd;
};
}
#endif
