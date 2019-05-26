
#include "CardShow.h"
#include "SwitchEventMediatorBase.h"

void summonersaster::CardShow::Initialize()
{
	Load();

}

void summonersaster::CardShow::Finalize()
{
	delete m_pRect;
	delete m_pPolygon;
	for (auto& card : m_pCards)
	{
		delete card;
	}
	ReleaseResources();
}

void summonersaster::CardShow::LoadResources()
{
	CardFolder& rCardFolder = CardFolder::CreateAndGetRef();
	GameFrameworkFactory::Create(&m_pRect);
	GameFrameworkFactory::Create(&m_pPolygon);
	m_pCards[0] = rCardFolder.CreateCopy(L"フォロワー", PLAYER_KIND::NON_SELECTING);
	m_pCards[1] = rCardFolder.CreateCopy(L"ウェポン", PLAYER_KIND::NON_SELECTING);
	m_pCards[2] = rCardFolder.CreateCopy(L"スペル", PLAYER_KIND::NON_SELECTING);

	RectSize windowSize;
	gameframework::WindowParam::GetWindowSize(&windowSize);
	m_rGameFramework.CreateTexture(_T("TITLE_BACK"), _T("Textures/TitleBack.png"));

	CreateTexture(_T("CARD_BACK"), _T("Textures/Battle_cardBack.png"));

	CreateTexture(_T("MP_FRAME"), _T("Textures/Battle_mPFrame.png"));
	CreateTexture(_T("MP"), _T("Textures/Battle_mP.png"));

	CreateTexture(_T("SELECTING_CARD_FRAME"), _T("Textures/Battle_selectingCardFrame.png"));

	CreateTexture(_T("COST"), _T("Textures/Cost.png"));
	CreateTexture(_T("ATTACK"), _T("Textures/Attack.png"));
	CreateTexture(_T("HP"), _T("Textures/HP.png"));
	CreateTexture(_T("CARD_FRAME"), _T("Textures/CardFrame.png"));

	RectSize cardInfoFontSSize;
	cardInfoFontSSize.m_width = windowSize.m_width * 0.006f;
	cardInfoFontSSize.m_height = 2.0f * cardInfoFontSSize.m_width;
	CreateFont(_T("CARD_S"), cardInfoFontSSize, _T("IPAex明朝"));

	RectSize cardInfoFontMSize;
	cardInfoFontMSize.m_width = windowSize.m_width * 0.008f;
	cardInfoFontMSize.m_height = 2.0f * cardInfoFontMSize.m_width;
	CreateFont(_T("CARD_M"), cardInfoFontMSize, _T("IPAex明朝"));

	RectSize cardInfoFontLSize;
	cardInfoFontLSize.m_width = windowSize.m_width * 0.0165f;
	cardInfoFontLSize.m_height = 2.0f * cardInfoFontLSize.m_width;
	CreateFont(_T("CARD_L"), cardInfoFontLSize, _T("IPAex明朝"));

	const float HEGHT_MULTIPLY = 4.0f;
	RectSize cardInfoNameFontSSize;
	cardInfoNameFontSSize.m_width = windowSize.m_width * 0.002f;
	cardInfoNameFontSSize.m_height = HEGHT_MULTIPLY * cardInfoNameFontSSize.m_width;
	CreateFont(_T("NAME_S"), cardInfoNameFontSSize, _T("IPAex明朝"));

	RectSize cardInfoNameFontMSize;
	cardInfoNameFontMSize.m_width = windowSize.m_width * 0.0027f;
	cardInfoNameFontMSize.m_height = HEGHT_MULTIPLY * cardInfoNameFontMSize.m_width;
	CreateFont(_T("NAME_M"), cardInfoNameFontMSize, _T("IPAex明朝"));

	RectSize cardInfoNameFontLSize;
	cardInfoNameFontLSize.m_width = windowSize.m_width * 0.006f;
	cardInfoNameFontLSize.m_height = HEGHT_MULTIPLY * cardInfoNameFontLSize.m_width;
	CreateFont(_T("NAME_L"), cardInfoNameFontLSize, _T("IPAex明朝"));
	isLoadEnd = true;
}

void summonersaster::CardShow::Update()
{
	if (m_rGameFramework.MouseIsPressed(DirectX8Mouse::DIM_LEFT))
	{
		m_rGameFramework.OneShotStart(L"DRAW");

		SwapCards();
	}
}

void summonersaster::CardShow::Render()
{
	RectSize windowSize;
	gameframework::WindowParam::GetWindowSize(&windowSize);
	D3DXVECTOR3 windowCenter;
	windowCenter.x = windowSize.m_width * 0.5f;
	windowCenter.y = windowSize.m_height * 0.5f;

	m_pRect->GetCenter() = { windowCenter.x, windowCenter.y, 1.0f };
	m_pRect->SetSize(RectSize(windowSize.m_width, windowSize.m_height));

	m_pRect->Render(m_rGameFramework.GetTexture(_T("TITLE_BACK")));

	windowCenter.y = windowSize.m_height * 0.65f;
	windowCenter.z = 0.1f;

	RectSize cardSize;
	cardSize.m_height = 1.4f * (cardSize.m_width = 380.0f);

	m_pCards[1]->Render(D3DXVECTOR3(windowCenter.x + cardSize.m_width*1.1f, windowCenter.y - cardSize.m_width * 0.5f, 0.2f), cardSize,Card::RENDERING_TYPE::LARGE);
	m_pCards[2]->Render(D3DXVECTOR3(windowCenter.x - cardSize.m_width*1.1f, windowCenter.y - cardSize.m_width * 0.5f, 0.2f), cardSize,Card::RENDERING_TYPE::LARGE);
	
	m_pPolygon->SetSize(cardSize);
	m_pPolygon->SetColor(0x66000000);
	m_pPolygon->GetCenter() = { windowCenter.x - cardSize.m_width * 1.1f, windowCenter.y - cardSize.m_width * 0.5f, 0.0f };
	m_pPolygon->Render(m_rGameFramework.GetTexture(nullptr));
	m_pPolygon->GetCenter() = { windowCenter.x + cardSize.m_width * 1.1f, windowCenter.y - cardSize.m_width * 0.5f, 0.0f };
	m_pPolygon->Render(m_rGameFramework.GetTexture(nullptr));

	cardSize.m_height = 1.4f * (cardSize.m_width = 400.0f);
	m_pCards[1]->Rect().SetColor(0xFFFFFFFF);
	m_pCards[0]->Render(windowCenter, cardSize,Card::RENDERING_TYPE::LARGE);

}

void summonersaster::CardShow::SwapCards() {
	Card* buf = nullptr;
	buf = m_pCards[0];
	m_pCards[0] = m_pCards[1];
	m_pCards[1] = m_pCards[2];
	m_pCards[2] = buf;
}
