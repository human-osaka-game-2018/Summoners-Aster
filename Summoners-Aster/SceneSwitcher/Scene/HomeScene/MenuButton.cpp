#include "MenuButton.h"

using namespace gameframework;

namespace summonersaster
{
	MenuButton::MenuButton() :Task(0.0f)
	{
		Initialize();
	}

	MenuButton::~MenuButton()
	{
		Finalize();
	}

	void MenuButton::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);

		LoadResource();
	}

	void MenuButton::LoadResource()
	{
		//m_rGameFramework.CreateTexture(_T("MENU_BUTTON"), _T("Textures/MenuButton.png"));
	}

	void MenuButton::Finalize()
	{
		Release();
	}

	void MenuButton::Release()
	{
		delete m_pRect;
		//m_rGameFramework.ReleaseTexture(_T("MENU_BUTTON"));
	}

	void MenuButton::Render()
	{
		m_isFinished = true;

		m_pRect->GetCenter() = { m_windowCenter.x * 1.75f, m_windowCenter.y * 0.2223f, 0.0f };
		m_pRect->SetSize(RectSize(m_windowSize.m_width * 0.1875f, m_windowSize.m_height * 0.1112f));

		m_pRect->Render(nullptr);
	}
} // namespace summonersaster
