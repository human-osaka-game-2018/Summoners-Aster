#include "Turn.h"

namespace summonersaster
{
	Turn::~Turn()
	{

	}

	Turn::Turn()
	{
		m_switchEventPost.m_nextKind = m_currentKind = _T("TURN_UI_RENDERING");
		CreateKindInstances();
		SwitchKind();
	}

	void Turn::Update()
	{
		if (m_switchEventPost.m_shouldSwitch)
		{
			if (m_switchEventPost.m_nextKind == _T("TURN_UI_RENDERING"))
			{
				IncrementTurn();
			}

			SwitchKind();
		}

		m_kinds[m_currentKind]->Update();
	}

	void Turn::CreateKindInstances()
	{
		m_kinds[_T("TURN_UI_RENDERING")] = new TurnUIRenderingStage(m_isPreceding, m_turnNum);
		m_kinds[_T("PHASE_OPERATION")]   = new PhaseOperationStage();
	}

	void Turn::IncrementTurn()
	{
		if ((m_isPreceding = !m_isPreceding))
		{
			++m_turnNum;
		}
	}
} // namespace summonersaster
