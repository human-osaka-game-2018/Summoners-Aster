#include "MainPhase.h"

namespace summonersaster
{
	using namespace gameframework;

	MainPhase::MainPhase()
	{
		WindowParam::GetWindowSize(&m_windowSize);
		m_windowCenter = { m_windowSize.m_width * 0.5f,m_windowSize.m_height * 0.5f };

		m_rGameFramework.CreateTexture(_T("END_MAIN_BUTTON"), _T("Textures/Battle_endMainButton.png"));

		m_pEndButton = new Button(0xFF888888, true);
		LocaleButton();
	}

	MainPhase::~MainPhase()
	{

	}

	void MainPhase::Initialize()
	{
		
	}

	void MainPhase::Finalize()
	{
		
	}

	void MainPhase::Update()
	{
		static bool isButtonClicked = false;

		if (m_pEndButton->IsReleased())
		{
			isButtonClicked = true;
		}

		m_pEndButton->GetFrame().SetColor(0xFFFFFFFF);

		if (m_rPlayer.Update(PHASE_KIND::MAIN))
		{
			if (!isButtonClicked) return;
		
			isButtonClicked = false;
		
			m_pEndButton->GetFrame().SetColor(0xFF888888);

			SwitchEventMediatorBase<Phase>::GetRef().SendSwitchEvent(PHASE_KIND::END);
		}
	}

	void MainPhase::Render()
	{
		m_rField.Render();
		m_rPlayer.Render();
		m_pEndButton->Render(m_rGameFramework.GetTexture(_T("END_MAIN_BUTTON")));
		m_rRotationOrderMediator.Render();
	}

	void MainPhase::LocaleButton()
	{
		Vertices& rEndButton = m_pEndButton->GetFrame();

		RectSize windowSize;
		WindowParam::GetWindowSize(&windowSize);

		rEndButton.GetCenter() = { windowSize.m_width, windowSize.m_height * 0.5f, 0.0f };

		RectSize size;
		size.m_width = size.m_height = windowSize.m_width * 0.17f;
		rEndButton.GetSize() = size;
	}
} // namespace summonersaster
