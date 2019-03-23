#include "DeckButton.h"

using namespace gameframework;

namespace summonersaster
{
	DeckButton::DeckButton() :Task(0.0f)
	{
		Initialize();
	}

	DeckButton::~DeckButton()
	{
		Finalize();
	}

	void DeckButton::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);

		LoadResource();
	}

	void DeckButton::LoadResource()
	{
		//m_rGameFramework.CreateTexture(_T("DECK_BUTTON"), _T("Textures/DeckButton.png"));
	}

	void DeckButton::Finalize()
	{
		Release();
	}

	void DeckButton::Release()
	{
		delete m_pRect;
		//m_rGameFramework.ReleaseTexture(_T("DECK_BUTTON"));
	}

	void DeckButton::Render()
	{
		m_isFinished = true;

		m_pRect->GetCenter() = { m_windowCenter.x * 1.625f, m_windowCenter.y * 1.3612f, 0.0f };
		m_pRect->SetSize(RectSize(m_windowSize.m_width * 0.28125f, m_windowSize.m_height * 0.19445f));

		m_pRect->Render(nullptr);
	}
} // namespace summonersaster
