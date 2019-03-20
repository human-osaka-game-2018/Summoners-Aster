#include "TitleBack.h"

using namespace gameframework;

namespace summonersaster
{
	TitleBack::TitleBack() :Task(1.0f)
	{
		Initialize();
	}

	TitleBack::~TitleBack()
	{
		Finalize();
	}

	void TitleBack::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);

		LoadResource();
	}

	void TitleBack::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("TITLE_BACK"), _T("Textures/TitleBack.png"));
	}

	void TitleBack::Finalize()
	{
		Release();
	}

	void TitleBack::Release()
	{
		delete m_pRect;
		m_rGameFramework.ReleaseTexture(_T("TITLE_BACK"));
	}

	void TitleBack::Render()
	{
		m_isFinished = true;

		m_pRect->GetCenter() = { m_windowCenter.x, m_windowCenter.y, 1.0f };
		m_pRect->SetSize(RectSize(m_windowSize.m_width, m_windowSize.m_height));

		m_pRect->Render(m_rGameFramework.GetTexture(_T("TITLE_BACK")));
	}
} // namespace summonersaster
