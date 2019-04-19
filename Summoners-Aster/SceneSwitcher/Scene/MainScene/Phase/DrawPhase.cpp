#include "DrawPhase.h"

namespace summonersaster
{
	DrawPhase::DrawPhase()
	{

	}

	DrawPhase::~DrawPhase()
	{

	}

	void DrawPhase::Initialize()
	{
		
	}

	void DrawPhase::Finalize()
	{
		
	}

	void DrawPhase::Update()
	{
		//ドローフェイズの処理が完了しているならばメインフェイズへ移行
		if (m_rPlayer.Update(PHASE_KIND::DRAW))
		{
			SwitchEventMediatorBase<Phase>::GetRef().SendSwitchEvent(PHASE_KIND::MAIN);

			m_rPlayer.InitializeInMainPhaseStart();
		}
	}

	void DrawPhase::Render()
	{
		m_rField.Render();
		m_rPlayer.Render();
		m_rRotationOrderMediator.Render(false);
	}
} // namespace summonersaster
