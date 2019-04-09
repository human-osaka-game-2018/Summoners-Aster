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
		delete m_pOpponentIcon;

		m_isLoadedPlayersInfo = false;
	}

	void PlayersInformationRenderingStep::Update()
	{
		LoadPlayersInformation();

		m_pProponentIcon->Update();
		m_pOpponentIcon->Update();

		if (m_pProponentIcon->IsFinished())
		{
			SwitchEventMediatorBase<Step>::GetRef().SendSwitchEvent(_T("BATTLE_PREPARING_STEP"));
		}
	}

	void PlayersInformationRenderingStep::Render()
	{
		m_pProponentIcon->Render();
		m_pOpponentIcon->Render();
	}

	void PlayersInformationRenderingStep::LoadPlayersInformation()
	{
		if (m_isLoadedPlayersInfo) return;

		m_isLoadedPlayersInfo = true;

		m_pProponentIcon = new PlayerIcon(_T("aiueo"), false);
		m_pOpponentIcon = new PlayerIcon(_T("aiueo"), true);
	}

} // namespace summonersaster
