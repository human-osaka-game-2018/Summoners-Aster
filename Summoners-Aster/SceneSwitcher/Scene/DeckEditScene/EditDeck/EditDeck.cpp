#include "EditDeck.h"

#include <iostream>
#include <fstream> 

using namespace gameframework;
namespace summonersaster
{

EditDeck::EditDeck(const tstring& deckName, const D3DXVECTOR2& texturCenter) :DECK_NAME(deckName), m_TexturCenter(texturCenter)
{
	WindowParam::GetWindowSize(&m_windowSize);
	WindowParam::GetWindowHandle(&m_Hwnd);
	m_windowCenter.x = m_windowSize.m_width * 0.5f;
	m_windowCenter.y = m_windowSize.m_height * 0.5f;

}

EditDeck::~EditDeck()
{
	Destroy();
}

void EditDeck::Render()
{
	RectSize cardSize;
	cardSize.m_height = 1.4f * (cardSize.m_width = 135.0f);
	LPTEXTURE pTexture = m_rGameFramework.GetTexture(_T("CARDSENDER_BUTTON"));
	LocaleButton();

	for (int i=0;i< m_EditCards.size();++i)
	{
		m_EditCards[i]->pCard->Render(D3DXVECTOR3(m_TexturCenter.x + 175 * i , m_TexturCenter.y, 0.0f),cardSize);
		m_EditCards[i]->pEraseButton->Render(pTexture);
		Vertices& vertices(m_EditCards[i]->pCard->Rect());
		(*m_pStream) = totstring(i);
		WriteWords(D3DXVECTOR2(vertices.GetCenter().x, vertices.GetCenter().y + vertices.GetSize().m_height * 0.7f), _T("CARD"), DT_CENTER);
	}
}

void EditDeck::Update()
{
	POINT currentCursorPos = { 0, 0 };
	m_rGameFramework.CursorPos(&currentCursorPos);
	long wheelScroll = m_rGameFramework.MouseWheelScrolling();

	if (currentCursorPos.y > 500 || currentCursorPos.y < 200) return;
	if (currentCursorPos.x > 1500.f || wheelScroll > 0)
	{
		if ((m_TexturCenter.x + 175 * (m_EditCards.size() - 1)) > 1500.f)
		{
			m_TexturCenter.x -= 10.f;
		}
	}
	else if (currentCursorPos.x < 200.f|| wheelScroll<0)
	{
		if (m_TexturCenter.x < 100.f)
		{
			m_TexturCenter.x += 10.f;
		}
	}
	for (auto& card : m_EditCards) 
	{
		if (card->pEraseButton->IsReleased())
		{
			m_rGameFramework.OneShotStart(L"ERASE_FOLLOWER");

			CardErase(card);
			OutputDebugString(L"Deckから取り除きます\n");
		}
	}
}

void EditDeck::Destroy()
{
	//外部からの読み込み時に動的確保するため
	for (auto card : m_EditCards)
	{
		delete card->pEraseButton;
		delete card->pCard;
		delete card;
	}
	m_EditCards.clear();
}

void EditDeck::Load(PLAYER_KIND owner)
{
	CardFolder& rCardFolder = CardFolder::CreateAndGetRef();

	m_EditCards.resize(LIMIT_CAPACITY);
	std::string filename = "DeckDate/Deck.csv";
	std::ifstream readingFile;
	readingFile.open(filename, std::ios::in);

	for (int i = 0; i < LIMIT_CAPACITY; ++i)
	{
		std::string readingBuffer;
		if (!std::getline(readingFile, readingBuffer))
		{
			m_EditCards.resize(i);
			break;
		}
		replace(readingBuffer.begin(), readingBuffer.end(), ',', '\0');
		const char* ch = readingBuffer.c_str();
		TCHAR tch[64];
		MultiByteToWideChar(CP_ACP, 0, ch, -1, tch, MultiByteToWideChar(CP_ACP, 0, ch, -1, NULL, 0));
		Card* card = rCardFolder.CreateCopy(tch, owner);
		Editor* editor = new Editor(card, new Button());
		m_EditCards[i] = editor;
		m_EditCards[i]->pCard->SetAbility(Ability(Ability::ROTATE, Ability::DRAWCARD));
	}
	if (LIMIT_CAPACITY != m_EditCards.size())
	{
		ShowCursor(true);
		m_rGameFramework.OneShotStart(L"ERROR");
		MessageBox(m_Hwnd, _T("デッキ枚数が40枚ではありません"), _T("ERRROR"), MB_OK);
		ShowCursor(false);
	}

	//デッキ読み込み
	//読み込み枚数が規定枚数でない場合エラーを吐かせる
}


void EditDeck::AddCard(Card* card)
{
	if (nullptr == card) return;
	if (LIMIT_CAPACITY <= m_EditCards.size())
	{
		ShowCursor(true);
		m_rGameFramework.OneShotStart(L"ERROR");
		MessageBox(m_Hwnd, _T("デッキ枚数が40枚を超えるので追加できませんでした"), _T("ERRROR"), MB_OK);
		ShowCursor(false);
		return;
	}
	if (!CountCard(card)) return;
	//種類枚数検索して制限枚数以上なら失敗
	m_EditCards.push_back(new Editor(card, new Button()));
}

bool EditDeck::CountCard(Card* card)
{
	int count = 0;
	for (auto& deckCard : m_EditCards)
	{
		if (card->Name() == deckCard->pCard->Name())
		{
			++count;
		}
		if (count > LIMIT_CARD_CAPACITY)
		{
			ShowCursor(true);
			m_rGameFramework.OneShotStart(L"ERROR");
			MessageBox(m_Hwnd, _T("同一カード枚数が制限枚数を超えるので追加できませんでした"), _T("ERRROR"), MB_OK);
			ShowCursor(false);
			return false;
		}
	}
	return true;
}

void EditDeck::CardErase(Editor* editor)
{
	m_EditCards.erase(remove(m_EditCards.begin(), m_EditCards.end(), editor), m_EditCards.end());
	delete editor;
}

void EditDeck::LocaleButton()
{
	float buttonPosY = m_windowCenter.y * 1.5f;
	float distanceByCenter = m_windowSize.m_width * 0.18f;
	RectSize buttonSize;
	for (auto& card : m_EditCards)
	{
		Vertices& vertices(card->pCard->Rect());
		Vertices& buttonVertex(card->pEraseButton->GetFrame());

		buttonVertex.SetCenter(D3DXVECTOR3(vertices.GetCenter().x, vertices.GetCenter().y+ vertices.GetSize().m_height * 0.6f, vertices.GetCenter().z));
		buttonSize.m_width = buttonSize.m_height = m_windowSize.m_width * 0.03f;
		buttonVertex.GetSize() = buttonSize;
		buttonVertex.SetColor(0xFF0000FF);
		buttonVertex.SetRotationZ(90.f);

	}
}

void EditDeck::SaveDack()
{
	if (LIMIT_CAPACITY != m_EditCards.size())
	{
		ShowCursor(true);
		m_rGameFramework.OneShotStart(L"ERROR");
		MessageBox(m_Hwnd, _T("デッキ枚数が40枚ではありません\nセーブできません"), _T("ERRROR"), MB_OK);
		ShowCursor(false);
		return;
	}

	OutputDebugString(L"Deckをセーブします\n");
	std::string filename = "DeckDate/Deck.csv";

	std::ofstream writingFile;
	writingFile.open(filename, std::ios::trunc);
	if (!writingFile) return;
	for (auto& card : m_EditCards)
	{
		const TCHAR* tch = card->pCard->Name().c_str();
		char ch[64];
		WideCharToMultiByte(CP_ACP, 0, tch, -1, ch, sizeof(ch), NULL, NULL);
		std::string str=ch;
		writingFile << str << "," <<std::endl;
	}
	return;
}


}
