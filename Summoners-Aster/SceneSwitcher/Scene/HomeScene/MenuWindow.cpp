#include "MenuWindow.h"

#include "Scene/Scene.h"
#include "SwitchEventMediatorBase.h"

using namespace gameframework;

namespace summonersaster
{
	MenuWindow::MenuWindow()
	{
		Initialize();
	}

	MenuWindow::~MenuWindow()
	{
		Finalize();
	}

	void MenuWindow::Initialize()
	{
		GameFrameworkFactory::Create(&m_pVertices);
		gameframework::WindowParam::GetWindowSize(&m_windowSize);
		m_windowCenter = { m_windowSize.m_width * 0.5f, m_windowSize.m_height * 0.35f };

		m_pVertices->GetCenter() = { m_windowCenter.x * 1.8f, m_windowCenter.y * 0.5f, 0.0f };
		m_pVertices->SetSize(RectSize(m_windowSize.m_width * 0.2f, m_windowSize.m_height * 0.35f));

		m_pExitButton = new Button(0xFF888888, false,_T("RESULT"), RectSize(10.f,20.f));
		m_pSettingButton = new Button(0xFF888888, false, _T("RESULT"), RectSize(10.f, 20.f));
		m_pEndGameButton = new Button(0xFF888888, false, _T("RESULT"), RectSize(10.f, 20.f));
		LoadResource();
		LocaleButton();
	}

	void MenuWindow::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("WINDOW"), _T("Textures/windowBox.png"));
	}

	void MenuWindow::Finalize()
	{
		Release();
	}

	void MenuWindow::Release()
	{
		delete m_pVertices;
		m_rGameFramework.ReleaseTexture(_T("WINDOW"));
	}

	void MenuWindow::Render()
	{
		if (!isActive) return;
		if (m_pExitButton->IsUnderCursor())
		{
			m_pExitButton->GetFrame().SetColor(0xFF999999);
		}
		if (m_pSettingButton->IsUnderCursor())
		{
			m_pSettingButton->GetFrame().SetColor(0xFF999999);
		}
		if (m_pEndGameButton->IsUnderCursor())
		{
			m_pEndGameButton->GetFrame().SetColor(0xFF999999);
		}

		m_pVertices->Render(m_rGameFramework.GetTexture(_T("WINDOW")));
		m_pExitButton->Render(m_rGameFramework.GetTexture(nullptr));
		m_pSettingButton->Render(m_rGameFramework.GetTexture(nullptr));
		m_pEndGameButton->Render(m_rGameFramework.GetTexture(nullptr));

		m_pExitButton->GetFrame().SetColor(0xFFFFFFFF);
		m_pSettingButton->GetFrame().SetColor(0xFFFFFFFF);
		m_pEndGameButton->GetFrame().SetColor(0xFFFFFFFF);

	}
	void MenuWindow::Update()
	{
		if (!isActive) return;
		if (m_pExitButton->IsClicked())
		{
			OutputDebugString(L"タイトル");
			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND::TITLE);
			return;
		}
		if (m_pSettingButton->IsClicked())
		{
			OutputDebugString(L"設定");
			return;
		}
		if (m_pEndGameButton->IsClicked())
		{
			OutputDebugString(L"ゲーム終了");
			PostQuitMessage(WM_QUIT);
			return;

		}
		if(!m_rGameFramework.IsCursorOnRect(*m_pVertices) && m_rGameFramework.MouseIsPressed(gameframework::DirectX8Mouse::DIM_LEFT))
		{
			ToggleActive();
		}
	}

	void MenuWindow::LocaleButton()
	{
		m_pExitButton->GetFrame().GetCenter() = m_pSettingButton->GetFrame().GetCenter() = m_pEndGameButton->GetFrame().GetCenter() =
		{ m_pVertices->GetCenter().x,m_pVertices->GetCenter().y, 0.f };

		float distanceByCenter = m_pVertices->GetSize().m_height * 0.2f;
		m_pExitButton->GetFrame().GetCenter().y -= distanceByCenter;
		m_pSettingButton->GetFrame().GetCenter().y;
		m_pEndGameButton->GetFrame().GetCenter().y += distanceByCenter;
		RectSize buttonSize;
		buttonSize.m_height = m_windowSize.m_width * 0.04f;
		buttonSize.m_width = m_pVertices->GetSize().m_width * 0.75f;
		m_pExitButton->GetStream() = _T("タイトルに戻る");
		m_pSettingButton->GetStream() = _T("設定");
		m_pEndGameButton->GetStream() = _T("ゲーム終了");

		m_pExitButton->GetStream().SetColor(0xFF000000);
		m_pSettingButton->GetStream().SetColor(0xFF000000);
		m_pEndGameButton->GetStream().SetColor(0xFF000000);

		m_pExitButton->GetFrame().GetSize() = m_pSettingButton->GetFrame().GetSize() = m_pEndGameButton->GetFrame().GetSize() = buttonSize;
	}

} // namespace summonersaster
