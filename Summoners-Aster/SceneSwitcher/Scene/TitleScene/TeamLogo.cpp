#include "TeamLogo.h"

using namespace gameframework;

namespace summonersaster
{
	TeamLogo::TeamLogo() :Task(0.0f)
	{
		Initialize();
	}

	TeamLogo::~TeamLogo()
	{
		Finalize();
	}

	void TeamLogo::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);
		m_pRect->GetColor() = 0x00FFFFFF;

		GameFrameworkFactory::Create(&m_pWhiteBack);

		LoadResource();
	}

	void TeamLogo::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("TEAM_LOGO"), _T("Textures/SINGULARITY.png"));
	}

	void TeamLogo::Finalize()
	{
		Release();
	}

	void TeamLogo::Release()
	{
		delete m_pRect;
		delete m_pWhiteBack;
		m_rGameFramework.ReleaseTexture(_T("TEAM_LOGO"));
	}

	void TeamLogo::Render()
	{
		RenderWhiteBack();

		m_pRect->GetCenter() = { m_windowCenter.x, m_windowCenter.y, 0.0f };
		m_pRect->SetSize(m_windowSize);

		m_pRect->Render(m_rGameFramework.GetTexture(_T("TEAM_LOGO")));

		FadeIn();
	}

	void TeamLogo::RenderWhiteBack()
	{
		m_pWhiteBack->GetCenter() = { m_windowCenter.x, m_windowCenter.y, 1.0f };
		m_pWhiteBack->SetSize(m_windowSize);

		m_pWhiteBack->Render(nullptr);
	}

	void TeamLogo::FadeIn()
	{
		BYTE& rAlpha = m_pRect->GetColor()[Color::COMPONENT::ALPHA];
		rAlpha = min(rAlpha + 4, 255);
		if (rAlpha < 255) return;

		if (m_frameLeftFinishTaskAfterEndStaging-- > 0) return;
		m_frameLeftFinishTaskAfterEndStaging = 0;
		m_isFinished = true;
		m_rGameFramework.OneShotStart(L"HOLY");
		m_rGameFramework.LoopStart(L"TITLE");

	}

} // namespace summonersaster
