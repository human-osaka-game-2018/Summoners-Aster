#include "ConnectButton.h"

using namespace gameframework;

namespace summonersaster
{
	ConnectButton::ConnectButton(Color pressColor, bool isCircle, const TCHAR* pFontKey, const RectSize& fontSize, const TCHAR* pFontName) 
		:Button(pressColor, isCircle, pFontKey, fontSize, pFontName)
	{
		Initialize();
	}

	ConnectButton::~ConnectButton()
	{
		Finalize();
	}

	void ConnectButton::Initialize()
	{

		LoadResource();
	}

	void ConnectButton::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("CONNECT_BUTTON"), _T("Textures/ConnectButton.png"));
	}

	void ConnectButton::Finalize()
	{
		Release();
	}

	void ConnectButton::Release()
	{
		m_rGameFramework.ReleaseTexture(_T("CONNECT_BUTTON"));
	}

	void ConnectButton::Render()
	{
		RenderFrame();
		RenderStream();
	}

	void ConnectButton::RenderFrame()
	{
		m_isFinished = true;
		if (IsUnderCursor())
		{
			m_pVertices->SetColor(0xFF888888);
		}

		m_pVertices->GetCenter() = { m_windowSize.m_width/4.f,  m_windowSize.m_height * 0.85f, 0.0f };
		m_pVertices->SetSize(RectSize(m_windowSize.m_height * 0.3f, m_windowSize.m_height * 0.3f));

		m_pVertices->Render(m_rGameFramework.GetTexture(_T("CONNECT_BUTTON")));
		m_pVertices->SetColor(0xFFFFFFFF);

	}
} // namespace summonersaster
