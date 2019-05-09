#include "DeckButton.h"

using namespace gameframework;

namespace summonersaster
{
	DeckButton::DeckButton(Color pressColor, bool isCircle, const TCHAR* pFontKey, const RectSize& fontSize, const TCHAR* pFontName)
		:Button(pressColor, isCircle, pFontKey, fontSize, pFontName)
	{
		Initialize();
	}

	DeckButton::~DeckButton()
	{
		Finalize();
	}

	void DeckButton::Initialize()
	{

		LoadResource();
	}

	void DeckButton::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("DECK_BUTTON"), _T("Textures/DeckButton.png"));
	}

	void DeckButton::Finalize()
	{
		Release();
	}

	void DeckButton::Release()
	{
		m_rGameFramework.ReleaseTexture(_T("DECK_BUTTON"));
	}

	void DeckButton::Render()
	{
		RenderFrame();
		RenderStream();
	}


	void DeckButton::RenderFrame()
	{
		m_isFinished = true;
		if (IsUnderCursor())
		{
			m_pVertices->SetColor(0xFF888888);
		}
		m_pVertices->GetCenter() = { m_windowSize.m_width *0.75f, m_windowSize.m_height * 0.85f, 0.0f };
		m_pVertices->SetSize(RectSize(m_windowSize.m_height * 0.3f, m_windowSize.m_height * 0.3f));

		m_pVertices->Render(m_rGameFramework.GetTexture(_T("DECK_BUTTON")));
		m_pVertices->SetColor(0xFFFFFFFF);

	}
} // namespace summonersaster
