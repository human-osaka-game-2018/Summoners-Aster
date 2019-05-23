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

		static bool initialized = false;

		if (!initialized)
		{
			m_rPlayers.InitializeInMainPhaseStart();

			initialized = true;
		}

		//ドローフェイズの処理が完了しているならばメインフェイズへ移行
		if (m_rPlayers.Update(PHASE_KIND::DRAW))
		{
			initialized = false;

			SwitchEventMediatorBase<Phase>::GetRef().SendSwitchEvent(PHASE_KIND::MAIN);
		}

		m_rAbilityTextController.Update();
	}

	void DrawPhase::Render()
	{
		m_rField.Render();
		m_rPlayers.Render();
		m_rField.RenderDummyButton();
		m_rRotationOrderMediator.Render(false);
		m_rAbilityTextController.Render();
	}
} // namespace summonersaster
