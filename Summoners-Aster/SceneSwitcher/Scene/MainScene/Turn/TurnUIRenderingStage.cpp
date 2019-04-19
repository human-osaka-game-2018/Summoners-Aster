#include "TurnUIRenderingStage.h"

namespace summonersaster
{
	using namespace gameframework;

	TurnUIRenderingStage::TurnUIRenderingStage(const bool& isPrecedingTurn, const int& turnNum) 
		:rIS_PRECEDING_TURN(isPrecedingTurn), rTURN_NUM(turnNum)
	{
		WindowParam::GetWindowSize(&m_windowSize);

		RectSize turnFontSize;
		turnFontSize.m_width  = m_windowSize.m_width * 0.035f;
		turnFontSize.m_height = 2.0f * turnFontSize.m_width;

		m_rGameFramework.CreateFont(_T("TURN_NUM"), turnFontSize, _T("IPAex明朝"));

		GameFrameworkFactory::Create(&m_pStream);
	}

	TurnUIRenderingStage::~TurnUIRenderingStage()
	{
		m_rGameFramework.ReleaseFont(_T("TURN_NUM"));
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
		m_rPlayer.Update(TURN_STAGE_KIND::UI_RENDERING);
	}

	void TurnUIRenderingStage::Render()
	{
		m_rField.Render();
		m_rPlayer.Render();
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
		_itot_s(rTURN_NUM, turnBuff, _countof(turnBuff), 10);

		(*m_pStream) = turnBuff;
		(*m_pStream) += _T("ターン\n");

		tstring player = _T("後行");

		if (rIS_PRECEDING_TURN)
		{
			player = _T("先行");
		}

		(*m_pStream) += player;
	}
} // namespace summonersaster
