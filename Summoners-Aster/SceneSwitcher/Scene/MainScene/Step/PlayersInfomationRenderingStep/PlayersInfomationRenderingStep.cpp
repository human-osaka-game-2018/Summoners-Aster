#include "PlayersInfomationRenderingStep.h"

namespace summonersaster
{
	PlayersInfomationRenderingStep::PlayersInfomationRenderingStep()
	{

	}

	PlayersInfomationRenderingStep::~PlayersInfomationRenderingStep()
	{

	}

	void PlayersInfomationRenderingStep::Initialize()
	{
		m_pProponentIcon = new PlayerIcon(_T("aiueo"), false);
		m_pOpponentIcon  = new PlayerIcon(_T("aiueo"), true);
	}

	void PlayersInfomationRenderingStep::Finalize()
	{
		delete m_pProponentIcon;
		delete m_pOpponentIcon;
	}

	void PlayersInfomationRenderingStep::Update()
	{
		m_pProponentIcon->Update();
		m_pOpponentIcon->Update();

		if (m_pProponentIcon->IsFinished())
		{
			SwitchEventMediatorBase<Step>::GetRef().SendSwitchEvent(_T("BATTLE_PREPARING_STEP"));
		}
	}

	void PlayersInfomationRenderingStep::Render()
	{
		m_pProponentIcon->Render();
		m_pOpponentIcon->Render();
	}
} // namespace summonersaster
