#include "DeckEditScene.h"
#include "SwitchEventMediatorBase.h"

namespace summonersaster
{
using namespace gameframework;


DeckEditScene::DeckEditScene()
{
	gameframework::WindowParam::GetWindowSize(&m_windowSize);

	m_windowCenter.x = m_windowSize.m_width * 0.5f;
	m_windowCenter.y = m_windowSize.m_height * 0.5f;
}


DeckEditScene::~DeckEditScene()
{
}

void DeckEditScene::Initialize()
{
	GameFrameworkFactory::Create(&m_pRect);

	LoadResources();
	m_pDeck = new EditDeck(_T("SHION"),D3DXVECTOR2(100.f,300.f));
	m_pDeck->Load(PLAYER_KIND::OPPONENT);
	m_pHavingCards = new HavingCards(PLAYER_KIND::PROPONENT, D3DXVECTOR2(100.f, 700.f));
	m_pExitButton = new Button(0xFF888888,false,_T("CARD"), RectSize(10.f, 20.f));
	m_pSaveButton = new Button(0xFF888888,false,_T("CARD"), RectSize(10.f, 20.f));
	LocaleButton();
	m_rGameFramework.LoopStart(L"EDIT");

}

void DeckEditScene::Finalize()
{
	delete m_pRect;
	m_pRect = nullptr;
	delete m_pDeck;
	m_pDeck = nullptr;
	delete m_pHavingCards;
	m_pHavingCards = nullptr;
	delete m_pExitButton;
	m_pExitButton = nullptr;
	delete m_pSaveButton;
	m_pSaveButton = nullptr;
	m_rGameFramework.Stop(L"EDIT");
	//GameFramework& rGameFramework = GameFramework::GetRef();

	//rGameFramework.ReleaseAllTexture();
	//rGameFramework.ReleaseAllFont();

}

void DeckEditScene::Update()
{
	gameframework::GameFramework& rGameFramework = gameframework::GameFramework::CreateAndGetRef();
	m_pDeck->AddCard(m_pHavingCards->OnButton());
	m_pDeck->Update();
	m_pHavingCards->Update();
	if (m_pExitButton->IsClicked())
	{
		rGameFramework.OneShotStart(L"CLICK");

		SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND::HOME);
	}
	if (m_pSaveButton->IsClicked())
	{
		rGameFramework.OneShotStart(L"CLICK");
		m_pDeck->SaveDack();
	}

	if (rGameFramework.KeyboardIsPressed(DIK_F))
	{
		rGameFramework.OneShotStart(L"CLICK");

		SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND::HOME);
	}


}

void DeckEditScene::Render()
{
	LPTEXTURE pTexture = m_rGameFramework.GetTexture(_T("BLOCK"));
	m_pRect->GetCenter() = { m_windowCenter.x, m_windowCenter.y, 1.0f };
	m_pRect->SetSize(RectSize(m_windowSize.m_width, m_windowSize.m_height));

	m_pRect->Render(m_rGameFramework.GetTexture(_T("EDIT_BACK")));

	m_pDeck->Render();
	m_pHavingCards->Render();

	m_pExitButton->Render(pTexture);
	m_pSaveButton->Render(pTexture);
}

void DeckEditScene::LoadResources()
{
	GameFramework& rGameFramework = GameFramework::GetRef();

	RectSize windowSize;
	gameframework::WindowParam::GetWindowSize(&windowSize);

	m_rGameFramework.CreateTexture(_T("EDIT_BACK"), _T("Textures/HomeBack.png"));

	rGameFramework.CreateTexture(_T("CARD_BACK"), _T("Textures/Battle_cardBack.png"));

	rGameFramework.CreateTexture(_T("SELECTING_CARD_FRAME"), _T("Textures/Battle_selectingCardFrame.png"));
	rGameFramework.CreateTexture(_T("CARDSENDER_BUTTON"), _T("Textures/DeckEditButtonR.png"));
	rGameFramework.CreateTexture(_T("BLOCK"), _T("Textures/block.png"));
	rGameFramework.CreateTexture(_T("COST"), _T("Textures/Cost.png"));
	rGameFramework.CreateTexture(_T("ATTACK"), _T("Textures/Attack.png"));
	rGameFramework.CreateTexture(_T("HP"), _T("Textures/HP.png"));
	rGameFramework.CreateTexture(_T("CARD_FRAME"), _T("Textures/CardFrame.png"));

	RectSize turnFontSize;
	turnFontSize.m_width = windowSize.m_width * 0.035f;
	turnFontSize.m_height = 2.0f * turnFontSize.m_width;
	rGameFramework.CreateFont(_T("TURN_NUM"), turnFontSize, _T("IPAex明朝"));

	RectSize resultFontSize;
	resultFontSize.m_width = windowSize.m_width * 0.01f;
	resultFontSize.m_height = 2.0f * resultFontSize.m_width;
	rGameFramework.CreateFont(_T("RESULT"), resultFontSize, _T("IPAex明朝"));

	RectSize playerNameFontSize;
	playerNameFontSize.m_width = windowSize.m_width * 0.0156f;
	playerNameFontSize.m_height = 2.0f * playerNameFontSize.m_width;
	rGameFramework.CreateFont(_T("PLAYER_INFO"), playerNameFontSize, _T("IPAex明朝"));

	RectSize mPFontSize;
	mPFontSize.m_height = 2.0f * (mPFontSize.m_width = 18.0f);
	rGameFramework.CreateFont(_T("MP"), mPFontSize, _T("IPAex明朝"));

	RectSize cardInfoFontSize;
	cardInfoFontSize.m_width = windowSize.m_width * 0.008f;
	cardInfoFontSize.m_height = 2.0f * cardInfoFontSize.m_width;
	rGameFramework.CreateFont(_T("CARD"), cardInfoFontSize, _T("IPAex明朝"));

}

void DeckEditScene::LocaleButton()
{
	float buttonPosY = 100.f;
	m_pExitButton->GetFrame().GetCenter() = m_pSaveButton->GetFrame().GetCenter() =
	{ m_windowCenter.x, buttonPosY, 0.87f };

	float distanceByCenter = m_windowSize.m_width * 0.4f;
	m_pExitButton->GetFrame().GetCenter().x -= distanceByCenter;
	m_pSaveButton->GetFrame().GetCenter().x += distanceByCenter;

	RectSize buttonSize;
	buttonSize.m_width = buttonSize.m_height = m_windowSize.m_width * 0.1f;
	m_pExitButton->GetStream() = _T("EXIT");
	m_pSaveButton->GetStream() = _T("SAVE");

	m_pExitButton->GetFrame().GetSize() = m_pSaveButton->GetFrame().GetSize() = buttonSize;
}


}
