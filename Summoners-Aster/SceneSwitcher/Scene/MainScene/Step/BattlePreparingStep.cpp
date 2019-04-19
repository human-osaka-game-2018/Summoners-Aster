#include "BattlePreparingStep.h"

namespace summonersaster
{
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
		if (m_rPlayer.Update(STEP_KIND::BATTLE_PREPARING))
		{
			std::random_device seed;
			std::minstd_rand generator(seed());
			std::uniform_int_distribution<int> dist(0, 1);

			m_rField.Initialize(static_cast<bool>(dist(generator)));

			SwitchEventMediatorBase<Step>::GetRef().SendSwitchEvent(STEP_KIND::BATTLE);
		}
	}

	void BattlePreparingStep::Render()
	{
		m_rField.Render();
		m_rPlayer.Render();
		m_rRotationOrderMediator.Render(false);
	}
} // namespace summonersaster
