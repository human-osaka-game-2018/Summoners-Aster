#include "Cemetery.h"

using namespace gameframework;
namespace summonersaster
{
Cemetery::Cemetery(const D3DXVECTOR2& texturCenter) :m_TexturCenter(texturCenter)
{
}

Cemetery::~Cemetery()
{
}

void Cemetery::Render()
{
	const RectSize CARD_SIZE(100.f, 141.f);
	const Degree ROTATION_Z(-90.0f);
	const D3DXVECTOR3 POS(m_TexturCenter.x, m_TexturCenter.y, 0.91f);

	SetVertex(POS, CARD_SIZE, 0xAA000000);
	m_pRect->SetRotationZ(ROTATION_Z);

	DrawTexture(_T("CARD_BACK"));

	for (auto& pCard : m_Cards)
	{
		pCard->Rect().SetColor(0xFFFFFFFF);

		pCard->Render(POS, CARD_SIZE, Card::RENDERING_TYPE::MIDDLE, ROTATION_Z);
	}
}

void Cemetery::Destroy()
{
	//外部からの読み込み時に動的確保するため
	for (auto card : m_Cards)
	{
		delete card;
	}
	m_Cards.clear();
}

void Cemetery::PreserveCard(Card* card)
{
	if (nullptr == card) return;

	card->IsInCemetery(true);

	m_Cards.emplace_back(card);
}
}
