#include "PlayerIcon.h"

using namespace gameframework;
using namespace gameframework::algorithm;

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
		RectSize size;
		size.m_width = size.m_height = m_windowSize.m_width * 0.19f;
		m_pVertices->GetSize() = size;
		float sign = Tertiary(m_isOpponent, +1.0f, -1.0f);
		m_pVertices->GetCenter().y = m_windowCenter.y + m_windowSize.m_height * 0.25f * sign;
		m_pVertices->GetCenter().z = 0.0f;

		GameFrameworkFactory::Create(&m_pStream);

		m_streamTopLeft.y = m_windowSize.m_height * 0.1f + Tertiary(m_isOpponent, 0.0f, m_windowSize.m_height * 0.5f);

		(*m_pStream = _T("RANK ")) += _T("999");
		*m_pStream += _T("\n");
		*m_pStream += Tertiary(m_isOpponent, _T("エフリ・レフル"), _T("ブレイバー・シオン"));

		LoadResource();
	}

	void PlayerIcon::LoadResource()
	{

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

		float sign = Tertiary(m_isOpponent, +1.0f, -1.0f);
		rCenter.x = m_windowCenter.x + m_windowSize.m_width * 0.3f * -sign;

		float shiftAmountX = m_windowSize.m_width * 1.0f * (m_preStagingTakesFrames / 30.0f) * sign;
		rCenter.x += shiftAmountX;

		m_streamTopLeft.x = m_windowSize.m_width  * 0.1f + Tertiary(m_isOpponent, 0.0f, m_windowSize.m_width  * 0.5f);
		m_streamTopLeft.x += shiftAmountX;

		if ((m_preStagingTakesFrames--) > 0) return;
		
		m_preStagingTakesFrames = 0;
	}

	void PlayerIcon::DisplayInformation()
	{
		if (m_preStagingTakesFrames != 0) return;

		if ((m_displayInfoTakesFrames--) > 0) return;

		m_displayInfoTakesFrames = 0;
	}

	void PlayerIcon::PerformPostStaging()
	{
		if (m_displayInfoTakesFrames != 0) return;

		D3DXVECTOR3& rCenter = m_pVertices->GetCenter();

		float sign = Tertiary(m_isOpponent, -1.0f, +1.0f);
		float shiftAmountY = m_windowSize.m_height * 0.033f * sign;

		rCenter.y -= shiftAmountY;

		m_streamTopLeft.y += shiftAmountY;

		if ((m_postStagingTakesFrames--) > 0) return;

		m_postStagingTakesFrames = 0;

		m_isFinished = true;
	}

} // namespace summonersaster
