#include "MainPhase.h"

namespace summonersaster
{
	using namespace gameframework;

	MainPhase::MainPhase()
	{
		
	}

	MainPhase::~MainPhase()
	{

	}

	void MainPhase::Initialize()
	{
		m_pEndButton = new Button(0xFF888888, true);
	}

	void MainPhase::Finalize()
	{
		
	}

	void MainPhase::Update()
	{
		UpdateButton();

		static bool isButtonClicked = false;

		if (m_pEndButton->IsReleased())
		{
			isButtonClicked = true;
		}

		//if (Players.Update(_T("MAIN")))
		//{
		//	if (!isButtonClicked) return;
		//
		//	isButtonClicked = false;
		//
		//	SwitchEventMediatorBase<Phase>::GetRef().SendSwitchEvent(_T("END"));
		//}

		//Field.Update(_T("MAIN"));
	}

	void MainPhase::Render()
	{
		//Players.Render(_T("MAIN"));
		//Field.Render(_T("MAIN"));
	}

	void MainPhase::UpdateButton()
	{
		Vertices& rEndButton = m_pEndButton->GetFrame();

		RectSize windowSize;
		WindowParam::GetWindowSize(&windowSize);

		rEndButton.GetCenter() = { windowSize.m_width * 0.8f, windowSize.m_height * 0.5f, 1.0f };
		rEndButton.GetSize() = { windowSize.m_width * 0.15f, windowSize.m_width * 0.15f };
	}
} // namespace summonersaster
