#include "CPUButton.h"

using namespace gameframework;

namespace summonersaster
{
	CPUButton::CPUButton(Color pressColor, bool isCircle, const TCHAR* pFontKey, const RectSize& fontSize, const TCHAR* pFontName)
		:Button(pressColor, isCircle, pFontKey, fontSize, pFontName)
	{
		Initialize();
	}

	CPUButton::~CPUButton()
	{
		Finalize();
	}

	void CPUButton::Initialize()
	{
		LoadResource();
	}

	void CPUButton::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("CPU_BUTTON"), _T("Textures/CPUButton.png"));
	}

	void CPUButton::Finalize()
	{
		Release();
	}

	void CPUButton::Release()
	{
		m_rGameFramework.ReleaseTexture(_T("CPU_BUTTON"));
	}

	void CPUButton::Render()
	{
		RenderFrame();
		RenderStream();
	}

	void CPUButton::RenderFrame()
	{
		m_isFinished = true;
		if (IsUnderCursor())
		{
			m_pVertices->SetColor(0xFF888888);
		}

		m_pVertices->GetCenter() = { m_windowCenter.x, m_windowSize.m_height * 0.85f, 0.0f };
		m_pVertices->SetSize(RectSize(m_windowSize.m_height * 0.3f, m_windowSize.m_height * 0.3f));

		m_pVertices->Render(m_rGameFramework.GetTexture(_T("CPU_BUTTON")));
		m_pVertices->SetColor(0xFFFFFFFF);

	}
} // namespace summonersaster
