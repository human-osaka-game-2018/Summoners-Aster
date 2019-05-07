#ifndef EDIT_DECK_SCENE_H
#define EDIT_DECK_SCENE_H
#include "Scene/Scene.h"
#include "EditDeck/EditDeck.h"
#include "HavingCards/HavingCards.h"
#include "Button.h"

namespace summonersaster
{
using gameframework::RectSize;
using gameframework::LPTEXTURE;
using gameframework::TextureUVs;
using gameframework::GameFramework;
using gameframework::Color;
using gameframework::Vertices;
using gameframework::Stream;

class DeckEditScene :public Scene
{
public:
	DeckEditScene();
	~DeckEditScene();

	/// <summary>
	/// 初期化を行う
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 終了処理を行う
	/// </summary>
	void Finalize()override;

	/// <summary>
	/// 更新を行う
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画を行う
	/// </summary>
	void Render()override;

	void LoadResources();
	void LocaleButton();
private:
	DeckEditScene(DeckEditScene& deckEditScene) = delete;

	DeckEditScene& operator=(DeckEditScene& deckEditScene) = delete;
	EditDeck* m_pDeck = nullptr;
	HavingCards* m_pHavingCards = nullptr;

	RectSize m_windowSize;
	D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

	GameFramework& m_rGameFramework = GameFramework::GetRef();
	gameframework::Vertices* m_pRect = nullptr;

	Button* m_pExitButton = nullptr;
	Button* m_pSaveButton = nullptr;

};
}
#endif
