#include "BattlePreparingStep.h"

namespace summonersaster
{
	using namespace gameframework;

	BattlePreparingStep::BattlePreparingStep()
	{

	}

	BattlePreparingStep::~BattlePreparingStep()
	{

	}

	void BattlePreparingStep::Initialize()
	{
		
	}

	void BattlePreparingStep::Finalize()
	{
		
	}

	void BattlePreparingStep::Update()
	{
		m_rField.Update();

		if (m_rPlayers.Update(STEP_KIND::BATTLE_PREPARING))
		{
			std::random_device seed;
			std::minstd_rand generator(seed());
			std::uniform_int_distribution<> dist(0, 1);

			BattleInformation::StartPlayer(algorithm::Tertiary(dist(generator) == 0, PLAYER_KIND::PROPONENT, PLAYER_KIND::OPPONENT));

			m_rField.Initialize();

			SwitchEventMediatorBase<Step>::GetRef().SendSwitchEvent(STEP_KIND::BATTLE);
		}
	}

	void BattlePreparingStep::Render()
	{
		m_rField.Render();
		m_rPlayers.Render();
		m_rField.RenderDummyButton();
		m_rRotationOrderMediator.Render(false);
	}
} // namespace summonersaster
