#include "BattleStep.h"

namespace summonersaster
{
	BattleStep::BattleStep()
	{

	}

	BattleStep::~BattleStep()
	{
		m_rTurn.ReleaseInstance();
	}

	void BattleStep::Initialize()
	{
		
	}

	void BattleStep::Finalize()
	{
		
	}

	void BattleStep::Update()
	{
		m_rTurn.Update();
	}

	void BattleStep::Render()
	{
		m_rTurn.Render();
	}
} // namespace summonersaster
