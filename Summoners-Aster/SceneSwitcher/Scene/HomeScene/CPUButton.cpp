#include "CPUButton.h"

using namespace gameframework;

namespace summonersaster
{
	CPUButton::CPUButton() :Task(0.0f)
	{
		Initialize();
	}

	CPUButton::~CPUButton()
	{
		Finalize();
	}

	void CPUButton::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);

		LoadResource();
	}

	void CPUButton::LoadResource()
	{
		//m_rGameFramework.CreateTexture(_T("CPU_BUTTON"), _T("Textures/CPUButton.png"));
	}

	void CPUButton::Finalize()
	{
		Release();
	}

	void CPUButton::Release()
	{
		delete m_pRect;
		//m_rGameFramework.ReleaseTexture(_T("CPU_BUTTON"));
	}

	void CPUButton::Render()
	{
		m_isFinished = true;

		m_pRect->GetCenter() = { m_windowCenter.x * 1.625f, m_windowCenter.y * 0.86112f, 0.0f };
		m_pRect->SetSize(RectSize(m_windowSize.m_width * 0.28125f, m_windowSize.m_height * 0.19445f));

		m_pRect->Render(nullptr);
	}
} // namespace summonersaster
