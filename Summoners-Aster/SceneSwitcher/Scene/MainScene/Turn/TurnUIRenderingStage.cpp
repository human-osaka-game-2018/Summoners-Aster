#include "TurnUIRenderingStage.h"

namespace summonersaster
{
	using namespace gameframework;

	TurnUIRenderingStage::TurnUIRenderingStage() 
	{
		WindowParam::GetWindowSize(&m_windowSize);

		GameFrameworkFactory::Create(&m_pStream);
	}

	TurnUIRenderingStage::~TurnUIRenderingStage()
	{
		delete m_pStream;
	}

	void TurnUIRenderingStage::Initialize()
	{
		
	}

	void TurnUIRenderingStage::Finalize()
	{
		
	}

	void TurnUIRenderingStage::Update()
	{
		m_rField.Update();

		m_rPlayers.Update(TURN_STAGE_KIND::UI_RENDERING);
	}

	void TurnUIRenderingStage::Render()
	{
		m_rField.Render();
		m_rPlayers.Render();
		m_rRotationOrderMediator.Render(false);

		static int frame = 0;
		const int FRAME_MAX = 120;

		CreateTurnStream();
		m_pStream->Flash(FRAME_MAX, 0, 255);
		m_pStream->Render(m_rGameFramework.GetFont(_T("TURN_NUM")), DT_CENTER);

		if (++frame >= FRAME_MAX)
		{
			frame = 0;

			SwitchEventMediatorBase<TurnStage>::GetRef().SendSwitchEvent(TURN_STAGE_KIND::PHASE_OPERATION);
		}
	}

	void TurnUIRenderingStage::CreateTurnStream()
	{
		D3DXVECTOR2 topLeft(m_windowSize.m_width * 0.5f, m_windowSize.m_height * 0.4f);
		m_pStream->SetTopLeft(topLeft);

		TCHAR turnBuff[4];
		_itot_s(BattleInformation::Turn() , turnBuff, _countof(turnBuff), 10);

		(*m_pStream) = turnBuff;
		(*m_pStream) += _T("ターン\n");

		tstring player = 
			algorithm::Tertiary(BattleInformation::CurrentPlayer() == BattleInformation::StartPlayer(), _T("先行"), _T("後行"));

		(*m_pStream) += player;
		(*m_pStream) += _T("\n");
		(*m_pStream) += algorithm::Tertiary(BattleInformation::CurrentPlayer() == PLAYER_KIND::OPPONENT, _T("エフリ・レフル"), _T("ブレイバー・シオン"));

	}
} // namespace summonersaster
