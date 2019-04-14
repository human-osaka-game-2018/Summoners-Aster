#include "Cemetery.h"

using namespace gameframework;
namespace summonersaster
{

Cemetery::Cemetery()
{
}

Cemetery::~Cemetery()
{
}

void Cemetery::Render()
{
	if (0 == m_Cards.size()) return;
#ifdef _DEBUG

	for (int i = 0; i < m_Cards.size(); ++i)
	{
		SetString(L"%d", m_Cards[i]->ID);
		WriteWords(D3DXVECTOR2(i * (Card::DEBUG_WORD_WIGTH * 1.5f) + Card::DEBUG_WORD_WIGTH * 2, 300.f), _T("Debug_str"), DT_RIGHT, (0xFF00FF00));
		
	}
#endif
	SetVertex(D3DXVECTOR3(m_TexturCenter.x, m_TexturCenter.y, 0.0f), RectSize(200.f, 260.f), Color());
	DrowTexture(_T("TEAM_LOGO"));

	SetString(L"%d", static_cast<int>(m_Cards.size()));
	WriteWords(D3DXVECTOR2(m_TexturCenter.x + 150.f, m_TexturCenter.y), _T("INPUT_PROMPT"), DT_RIGHT, (0xFF00FF00));


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

	m_Cards.emplace_back(card);
}
}
