#include "ResultStep.h"

namespace summonersaster
{
	using namespace gameframework;

	ResultStep::ResultStep()
	{
		WindowParam::GetWindowSize(&m_windowSize);
	}

	ResultStep::~ResultStep()
	{
		
	}

	void ResultStep::Initialize()
	{
		GameFrameworkFactory::Create(&m_pStream);
	}

	void ResultStep::Finalize()
	{
		m_stagingTakesFrames = 240;

		m_loadedResult = false;

		delete m_pStream;

		m_pStream = nullptr;
	}

	void ResultStep::Update()
	{
		LoadResult();
	}

	void ResultStep::Render()
	{
		m_rField.Render();
		m_rPlayers.Render();
		m_rField.RenderDummyButton();
		m_rRotationOrderMediator.Render(false);
		m_pStream->Render(m_rGameFramework.GetFont(_T("TURN_NUM")), DT_CENTER);

		if (m_stagingTakesFrames-- < 0)
		{
			m_stagingTakesFrames = 0;

			SwitchEventMediatorBase<Step>::GetRef().SendSwitchEvent(STEP_KIND::PLAYERS_INFOMATION_RENDERING);
			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(_T("HOME"));
		}
	}

	void ResultStep::LoadResult()
	{
		if (m_loadedResult) return;

		m_loadedResult = true;

		*m_pStream = algorithm::Tertiary(BattleInformation::Winner() == PLAYER_KIND::PROPONENT, _T("WIN"), _T("LOSE"));

		m_pStream->SetColor(0xFF2323FF);

		if (*m_pStream == _T("WIN")) m_pStream->SetColor(0xFFFF2323);

		RectSize fontSize(0.0f, 0.0f);
		m_rGameFramework.GetFontSize(_T("TURN_NUM"), &fontSize);

		D3DXVECTOR2 topLeft(0.5f * m_windowSize.m_width, 0.5f * (m_windowSize.m_height - fontSize.m_height));
		m_pStream->SetTopLeft(topLeft);
	}

} // namespace summonersaster
