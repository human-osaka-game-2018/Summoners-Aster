#include "PlayerIcon.h"

using namespace gameframework;

namespace summonersaster
{
	PlayerIcon::PlayerIcon(const TCHAR* pPlayerTextureKey, bool isOpponent)
		:Task(0.0f), pPLAYER_TEXTURE_KEY(pPlayerTextureKey), m_isOpponent(isOpponent)
	{
		Initialize();
	}

	PlayerIcon::~PlayerIcon()
	{
		Finalize();
	}

	void PlayerIcon::Initialize()
	{
		GameFrameworkFactory::Create(&m_pVertices);
		m_pVertices->GetSize() = { m_windowSize.m_width * 0.4f, m_windowSize.m_height * 0.48f };
		float sign = (m_isOpponent) ? +1.0f : -1.0f;
		m_pVertices->GetCenter().y = m_windowCenter.y + m_windowSize.m_width * 0.25f * sign;

		GameFrameworkFactory::Create(&m_pStream);

		m_streamTopLeft.y = m_windowSize.m_height * 0.3f + (m_isOpponent) ? 0.0f : m_windowSize.m_height * 0.5f;

		(*m_pStream = _T("RANK ")) += _T("999");
		*m_pStream += _T("\n");
		*m_pStream = (m_isOpponent) ? _T("エフリ") : _T("卍7位さん卍");

		LoadResource();
	}

	void PlayerIcon::LoadResource()
	{
		m_rGameFramework.CreateFont(_T("PLAYER_INFO"), RectSize(30.0f, 60.0f), nullptr);
	}

	void PlayerIcon::Finalize()
	{
		Release();
	}

	void PlayerIcon::Release()
	{
		delete m_pVertices;
		delete m_pStream;
	}

	void PlayerIcon::Render()
	{
		PerformPreStaging();
		DisplayInformation();
		PerformPostStaging();

		m_pVertices->Render(m_rGameFramework.GetTexture(pPLAYER_TEXTURE_KEY));
		m_pStream->SetTopLeft(m_streamTopLeft);
		m_pStream->Render(m_rGameFramework.GetFont(_T("PLAYER_INFO")), DT_LEFT);
	}

	void PlayerIcon::PerformPreStaging()
	{
		D3DXVECTOR3& rCenter = m_pVertices->GetCenter();

		float sign = (m_isOpponent) ? +1.0f : -1.0f;
		rCenter.x = m_windowCenter.x + m_windowSize.m_width * 0.3f * sign;

		float shiftAmountX = m_windowSize.m_width * 0.3f * (m_preStagingTakesFrames / 30.0f) * sign;
		rCenter.x += shiftAmountX;

		m_streamTopLeft.x = m_windowSize.m_width  * 0.1f + (m_isOpponent) ? 0.0f : m_windowSize.m_width  * 0.5f;
		m_streamTopLeft.x += shiftAmountX;

		if ((m_preStagingTakesFrames--) >= 0)
		{
			m_preStagingTakesFrames = 0;
		}
	}

	void PlayerIcon::DisplayInformation()
	{
		if (m_preStagingTakesFrames != 0) return;

		if ((m_displayInfoTakesFrames--) >= 0)
		{
			m_displayInfoTakesFrames = 0;
		}
	}

	void PlayerIcon::PerformPostStaging()
	{
		if (m_displayInfoTakesFrames != 0) return;

		D3DXVECTOR3& rCenter = m_pVertices->GetCenter();

		float sign = (m_isOpponent) ? +1.0f : -1.0f;
		float shiftAmountY = m_windowSize.m_height * 0.033f * sign;

		rCenter.y += shiftAmountY;

		m_streamTopLeft.y += shiftAmountY;

		if ((m_postStagingTakesFrames--) >= 0)
		{
			m_postStagingTakesFrames = 0;

			m_isFinished = true;
		}
	}

} // namespace summonersaster
