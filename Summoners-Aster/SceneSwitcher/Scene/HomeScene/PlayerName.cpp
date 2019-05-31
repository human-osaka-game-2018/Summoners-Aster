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
		GameFrameworkFactory::Create(&m_pStream);
		LoadResource();
	}

	void PlayerName::LoadResource()
	{
		RectSize windowSize;
		gameframework::WindowParam::GetWindowSize(&windowSize);
		RectSize cardInfoFontSize;
		cardInfoFontSize.m_width = windowSize.m_width * 0.01f;
		cardInfoFontSize.m_height = 2.0f * cardInfoFontSize.m_width;
		m_rGameFramework.CreateFont(_T("CARD"), cardInfoFontSize, _T("IPAex明朝"));

		m_rGameFramework.CreateTexture(_T("PLAYER_NAME"), _T("Textures/PlayerName.png"));
	}

	void PlayerName::Finalize()
	{
		Release();
	}

	void PlayerName::Release()
	{
		delete m_pRect;
		delete m_pStream;
		m_rGameFramework.ReleaseTexture(_T("PLAYER_NAME"));
	}

	void PlayerName::Render()
	{
		m_isFinished = true;

		m_pRect->GetCenter() = { m_windowCenter.x * 0.25f, m_windowCenter.y * 0.2223f, 0.0f };
		m_pRect->SetSize(RectSize(m_windowSize.m_width * 0.22f, m_windowSize.m_height * 0.1112f));
		D3DXVECTOR3 center = m_pRect->GetCenter();
		RectSize size = m_pRect->GetSize();
		m_pRect->Render(m_rGameFramework.GetTexture(_T("PLAYER_NAME")));
		m_pStream->SetTopLeft(D3DXVECTOR2(center.x/* - size.m_width*/, center.y - size.m_height * 0.1f));

		(*m_pStream) = _T("プレイヤー");
		m_pStream->SetColor(0xFF000000);
		m_pStream->Render(m_rGameFramework.GetFont(_T("CARD")), DT_CENTER);

	}
} // namespace summonersaster
