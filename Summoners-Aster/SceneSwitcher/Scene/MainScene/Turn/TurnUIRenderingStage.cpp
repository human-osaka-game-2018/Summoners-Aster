#include "TurnUIRenderingStage.h"

namespace summonersaster
{
	using namespace gameframework;

	TurnUIRenderingStage::TurnUIRenderingStage(const bool& isPrecedingTurn, const int& turnNum) 
		:rIS_PRECEDING_TURN(isPrecedingTurn), rTURN_NUM(turnNum)
	{
		WindowParam::GetWindowSize(&m_windowSize);

		RectSize turnFontSize;
		turnFontSize.m_width  = m_windowSize.m_width * 0.01f;
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

	}

	void TurnUIRenderingStage::Render()
	{
		static int frame = 0;

		CreateTurnStream();
		m_pStream->Render(m_rGameFramework.GetFont(_T("TURN_NUM")), DT_CENTER);

		if ((frame++) >= 120)
		{
			frame = 0;

			SwitchEventMediatorBase<TurnStage>::GetRef().SendSwitchEvent(_T("PHASE_OPERATION"));
		}
	}

	void TurnUIRenderingStage::CreateTurnStream()
	{
		TCHAR turnBuff[4];
		_itot_s(rTURN_NUM, turnBuff, sizeof(turnBuff), 10);

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
