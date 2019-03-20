#include "GameTitle.h"

using namespace gameframework;

namespace summonersaster
{
	GameTitle::GameTitle() :Task(0.0f)
	{
		Initialize();
	}

	GameTitle::~GameTitle()
	{
		Finalize();
	}

	void GameTitle::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);

		LoadResource();
	}

	void GameTitle::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("GAME_TITLE"), _T("Textures/GameTitle.png"));
	}

	void GameTitle::Finalize()
	{
		Release();
	}

	void GameTitle::Release()
	{
		delete m_pRect;
		m_rGameFramework.ReleaseTexture(_T("GAME_TITLE"));
	}

	void GameTitle::Render()
	{
		Stage();
		m_pRect->Render(m_rGameFramework.GetTexture(_T("GAME_TITLE")));
	}

	void GameTitle::Stage()
	{
		// UVスクロール
		m_textureUVsSize.m_width = min(m_textureUVsSize.m_width + 0.032f, 1.0f);
		m_pRect->GetTextureUVs().SetTextureUVsParams(
			D3DXVECTOR2(0.0f, 0.0f),
			RectSize(1.0f, 1.0f),
			m_textureUVsSize,
			1);

		// 矩形を長くしていく
		m_pRect->SetPosByTopLeft(
			D3DXVECTOR3(m_windowCenter.x * 0.35f,
						m_windowCenter.y * 0.475f,
						0.0f),
			RectSize(m_windowSize.m_width  * 0.65f * m_textureUVsSize.m_width,
					 m_windowSize.m_height * 0.5f  * 0.65f));

		if (m_textureUVsSize.m_width >= 1.0f)
		{
			m_isFinished = true;
		}
	}

} // namespace summonersaster
