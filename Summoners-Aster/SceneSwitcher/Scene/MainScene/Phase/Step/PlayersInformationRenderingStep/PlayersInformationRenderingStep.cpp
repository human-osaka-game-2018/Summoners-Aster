#include "PlayersInformationRenderingStep.h"

namespace summonersaster
{
	PlayersInformationRenderingStep::PlayersInformationRenderingStep()
	{

	}

	PlayersInformationRenderingStep::~PlayersInformationRenderingStep()
	{

	}

	void PlayersInformationRenderingStep::Initialize()
	{
		
	}

	void PlayersInformationRenderingStep::Finalize()
	{
		delete m_pProponentIcon;
		m_pProponentIcon = nullptr;

		delete m_pOpponentIcon;
		m_pOpponentIcon = nullptr;

		m_isLoadedPlayersInfo = false;
	}

	void PlayersInformationRenderingStep::Update()
	{
		LoadPlayersInformation();

		m_pProponentIcon->Update();
		m_pOpponentIcon->Update();

		if (m_pProponentIcon->IsFinished())
		{
			SwitchEventMediatorBase<Step>::GetRef().SendSwitchEvent(STEP_KIND::BATTLE_PREPARING);
		}
	}

	void PlayersInformationRenderingStep::Render()
	{
		m_rField.Render();
		m_rRotationOrderMediator.Render(false);
		m_pProponentIcon->Render();
		m_pOpponentIcon->Render();
	}

	void PlayersInformationRenderingStep::LoadPlayersInformation()
	{
		if (m_isLoadedPlayersInfo) return;

		m_isLoadedPlayersInfo = true;

		m_pProponentIcon = new PlayerIcon(_T("FUJIZONO"), false);
		m_pOpponentIcon = new PlayerIcon(_T("SHION"), true);
	}

} // namespace summonersaster
