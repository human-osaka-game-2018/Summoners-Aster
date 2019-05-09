#include "MenuButton.h"

using namespace gameframework;

namespace summonersaster
{
	MenuButton::MenuButton() :Button()
	{
		Initialize();
	}

	MenuButton::~MenuButton()
	{
		Finalize();
	}

	void MenuButton::Initialize()
	{

		LoadResource();
	}

	void MenuButton::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("MENU_BUTTON"), _T("Textures/MenuButton.png"));
	}

	void MenuButton::Finalize()
	{
		Release();
	}

	void MenuButton::Release()
	{
		m_rGameFramework.ReleaseTexture(_T("MENU_BUTTON"));
	}

	void MenuButton::Render()
	{
		RenderFrame();
		RenderStream();
	}


	void MenuButton::RenderFrame()
	{
		m_isFinished = true;

		m_pVertices->GetCenter() = { m_windowSize.m_width * 0.955f, m_windowCenter.y * 0.16f, 0.0f };
		m_pVertices->SetSize(RectSize(m_windowSize.m_height * 0.16f, m_windowSize.m_height * 0.16f));
		
		m_pVertices->Render(m_rGameFramework.GetTexture(_T("MENU_BUTTON")));
	}
} // namespace summonersaster
