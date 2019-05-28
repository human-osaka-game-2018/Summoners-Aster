#include "HavingCards.h"
using namespace gameframework;

namespace summonersaster
{
HavingCards::HavingCards(PLAYER_KIND owner, const D3DXVECTOR2& texturCenter): m_TexturCenter(texturCenter)
{
	Load(owner);
	WindowParam::GetWindowSize(&m_windowSize);

	m_windowCenter.x = m_windowSize.m_width * 0.5f;
	m_windowCenter.y = m_windowSize.m_height * 0.5f;
}

HavingCards::~HavingCards()
{
	for (auto card : m_HavingCards)
	{
		delete card->m_pSendDeckButton;
		delete card->pCard;
		delete card;
	}
	m_HavingCards.clear();

}

void HavingCards::Load(PLAYER_KIND owner)
{
	CardFolder& rCardFolder = CardFolder::CreateAndGetRef();

	int KindNum = rCardFolder.GetQuantity();
	m_HavingCards.resize(KindNum);
	for (int i = 0; i < KindNum; ++i)
	{
		Card* card = rCardFolder.CreateCopy(rCardFolder.GetCardName(i), owner);
		Having* having = new Having(card, new Button());
		m_HavingCards[i] = having;
	}
}

void HavingCards::Render()
{
	RectSize cardSize;
	cardSize.m_height = 1.4f * (cardSize.m_width = 135.0f);
	LocaleButton();
	LPTEXTURE pTexture = m_rGameFramework.GetTexture(_T("CARDSENDER_BUTTON"));

	for (int i = 0; i < m_HavingCards.size(); ++i)
	{
		m_HavingCards[i]->pCard->Render(D3DXVECTOR3(m_TexturCenter.x + (175 * i + 1), m_TexturCenter.y, 0.0f), cardSize);
		m_HavingCards[i]->m_pSendDeckButton->Render(pTexture);
	}
}

void HavingCards::Update()
{
	POINT currentCursorPos = { 0, 0 };
	m_rGameFramework.CursorPos(&currentCursorPos);
	long wheelScroll = m_rGameFramework.MouseWheelScrolling();

	if (currentCursorPos.y < 500) return;
	if (currentCursorPos.x > 1500.f || wheelScroll > 0)
	{
		if ((m_TexturCenter.x + 175 * (m_HavingCards.size() - 1)) > 1500.f)
		{
			m_TexturCenter.x -= 10.f;
		}
	}
	else if (currentCursorPos.x < 200.f || wheelScroll < 0)
	{
		if (m_TexturCenter.x < 100.f)
		{
			m_TexturCenter.x += 10.f;
		}
	}
}

Card* HavingCards::OnButton()
{
	for (auto& card : m_HavingCards)
	{
		if (card->m_pSendDeckButton->IsReleased())
		{
			m_rGameFramework.OneShotStart(L"DRAW");

			OutputDebugString(L"Deckに送ります\n");
			CardFolder& rCardFolder = CardFolder::CreateAndGetRef();
			Card* buf = card->pCard;
			PLAYER_KIND owner = algorithm::Tertiary(
				PLAYER_KIND::PROPONENT== buf->Owner(),
				PLAYER_KIND::OPPONENT, PLAYER_KIND::PROPONENT);
			return rCardFolder.CreateCopy(buf->Name(), owner);
		}
	}
	return nullptr;
}

void HavingCards::LocaleButton()
{
	float buttonPosY = m_windowCenter.y * 1.5f;
	float distanceByCenter = m_windowSize.m_width * 0.18f;
	RectSize buttonSize;
	for (auto& card : m_HavingCards)
	{
		Vertices& vertices(card->pCard->Rect());
		Vertices& buttonVertex(card->m_pSendDeckButton->GetFrame());

		buttonVertex.SetCenter(D3DXVECTOR3(vertices.GetCenter().x, vertices.GetCenter().y - vertices.GetSize().m_height*0.6f, vertices.GetCenter().z));
		buttonSize.m_width = buttonSize.m_height = m_windowSize.m_width * 0.03f;
		buttonVertex.GetSize() = buttonSize;
		buttonVertex.SetColor(0xFFFF0000);
		buttonVertex.SetRotationZ(270.f);

	}
}
}
