#include "HomeBack.h"

using namespace gameframework;

namespace summonersaster
{
	HomeBack::HomeBack() :Task(1.0f)
	{
		Initialize();
	}

	HomeBack::~HomeBack()
	{
		Finalize();
	}

	void HomeBack::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);

		LoadResource();
	}

	void HomeBack::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("HOME_BACK"), _T("Textures/HomeBack.png"));
	}

	void HomeBack::Finalize()
	{
		Release();
	}

	void HomeBack::Release()
	{
		delete m_pRect;
		m_rGameFramework.ReleaseTexture(_T("HOME_BACK"));
	}

	void HomeBack::Render()
	{
		m_isFinished = true;

		m_pRect->GetCenter() = { m_windowCenter.x, m_windowCenter.y, 1.0f };
		m_pRect->SetSize(RectSize(m_windowSize.m_width, m_windowSize.m_height));

		m_pRect->Render(m_rGameFramework.GetTexture(_T("HOME_BACK")));
	}
} // namespace summonersaster
