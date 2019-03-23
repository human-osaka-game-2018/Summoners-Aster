#include "PlayerName.h"

using namespace gameframework;

namespace summonersaster
{
	PlayerName::PlayerName() :Task(0.0f)
	{
		Initialize();
	}

	PlayerName::~PlayerName()
	{
		Finalize();
	}

	void PlayerName::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);

		LoadResource();
	}

	void PlayerName::LoadResource()
	{
		//m_rGameFramework.CreateTexture(_T("PLAYER_NAME"), _T("Textures/PlayerName.png"));
	}

	void PlayerName::Finalize()
	{
		Release();
	}

	void PlayerName::Release()
	{
		delete m_pRect;
		//m_rGameFramework.ReleaseTexture(_T("PLAYER_NAME"));
	}

	void PlayerName::Render()
	{
		m_isFinished = true;

		m_pRect->GetCenter() = { m_windowCenter.x * 0.375f, m_windowCenter.y * 0.2223f, 0.0f };
		m_pRect->SetSize(RectSize(m_windowSize.m_width * 0.3125f, m_windowSize.m_height * 0.1112f));

		m_pRect->Render(nullptr);
	}
} // namespace summonersaster
