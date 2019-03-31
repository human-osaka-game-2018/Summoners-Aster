#include "GameTitleStar.h"

using namespace gameframework;

namespace summonersaster
{
	GameTitleStar::GameTitleStar() :Task(0.1f)
	{
		Initialize();
	}

	GameTitleStar::~GameTitleStar()
	{
		Finalize();
	}

	void GameTitleStar::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);
		m_pRect->GetColor() = 0x00FFFFFF;

		LoadResource();
	}

	void GameTitleStar::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("GAME_TITLE_STAR"), _T("Textures/GameTitleStar.png"));
	}

	void GameTitleStar::Finalize()
	{
		Release();
	}

	void GameTitleStar::Release()
	{
		delete m_pRect;
		m_rGameFramework.ReleaseTexture(_T("GAME_TITLE_STAR"));
	}

	void GameTitleStar::Render()
	{
		m_rGameFramework.ToAddtionBlendMode();

		m_pRect->GetCenter() = { m_windowCenter.x * 1.316f, m_windowCenter.y * 1.12f, 0.1f };
		m_pRect->SetSize(
			RectSize(m_windowSize.m_width  * 0.52f * 0.637f,
					 m_windowSize.m_height * 1.16f * 0.64f));

		m_pRect->Render(m_rGameFramework.GetTexture(_T("GAME_TITLE_STAR")));

		m_rGameFramework.ToDefaultBlendMode();

		FadeIn();
	}

	void GameTitleStar::FadeIn()
	{
		BYTE& rAlpha = (m_pRect->GetColor())[Color::COMPONENT::ALPHA];
		rAlpha = min(rAlpha + 9, 255);

		if (rAlpha >= 255)
		{
			m_isFinished = true;
		}
	}
} // namespace summonersaster
