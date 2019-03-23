#include "ConnectButton.h"

using namespace gameframework;

namespace summonersaster
{
	ConnectButton::ConnectButton() :Task(0.0f)
	{
		Initialize();
	}

	ConnectButton::~ConnectButton()
	{
		Finalize();
	}

	void ConnectButton::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);

		LoadResource();
	}

	void ConnectButton::LoadResource()
	{
		//m_rGameFramework.CreateTexture(_T("DECK_BUTTON"), _T("Textures/DeckButton.png"));
	}

	void ConnectButton::Finalize()
	{
		Release();
	}

	void ConnectButton::Release()
	{
		delete m_pRect;
		//m_rGameFramework.ReleaseTexture(_T("DECK_BUTTON"));
	}

	void ConnectButton::Render()
	{
		m_isFinished = true;

		m_pRect->GetCenter() = { m_windowCenter.x, m_windowCenter.y * 1.112f, 0.0f };
		m_pRect->SetSize(RectSize(m_windowSize.m_width * 0.28125f, m_windowSize.m_height * 0.445f));

		m_pRect->Render(nullptr);
	}
} // namespace summonersaster
