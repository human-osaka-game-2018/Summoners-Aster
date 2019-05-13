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
		m_rField.Update();

		//ドローフェイズの処理が完了しているならばメインフェイズへ移行
		if (m_rPlayers.Update(PHASE_KIND::DRAW))
		{
			SwitchEventMediatorBase<Phase>::GetRef().SendSwitchEvent(PHASE_KIND::MAIN);

			m_rPlayers.InitializeInMainPhaseStart();
		}
	}

	void DrawPhase::Render()
	{
		m_rField.Render();
		m_rPlayers.Render();
		m_rField.RenderDummyButton();
		m_rRotationOrderMediator.Render(false);
	}
} // namespace summonersaster
