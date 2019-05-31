#include "TurnUIRenderingStage.h"

namespace summonersaster
{
	using namespace gameframework;

	TurnUIRenderingStage::TurnUIRenderingStage()
	{
		WindowParam::GetWindowSize(&m_windowSize);

		GameFrameworkFactory::Create(&m_pStream);
		GameFrameworkFactory::Create(&m_pTurnCircule);
		GameFrameworkFactory::Create(&m_pTurnSubCircule);
		GameFrameworkFactory::Create(&m_pBlackFilter);

		RectSize circuleSize;
		circuleSize.m_width = circuleSize.m_height = m_windowSize.m_width * 0.3f;

		D3DXVECTOR3 windowCenter(m_windowSize.m_width * 0.5f, m_windowSize.m_height * 0.5f, 0.0f);

		m_pTurnCircule->SetCenterAndSize(windowCenter, circuleSize);

		m_pTurnSubCircule->SetCenterAndSize(windowCenter, circuleSize);

		m_pBlackFilter->SetCenterAndSizeAndColor(windowCenter, RectSize(2.0f * windowCenter.x, 2.0f * windowCenter.y), 0xFF000000);
	}

	TurnUIRenderingStage::~TurnUIRenderingStage()
	{
		delete m_pStream;
		delete m_pTurnCircule;
		delete m_pTurnSubCircule;
		delete m_pBlackFilter;
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

		m_rAbilityTextController.Update();
	}

	void TurnUIRenderingStage::Render()
	{
		m_rField.Render();
		m_rPlayers.Render();
		m_rField.RenderDummyButton();
		m_rRotationOrderMediator.Render(false);
		m_rAbilityTextController.Render();

		static int frame = 0;
		const int FRAME_MAX = 120;

		m_pBlackFilter->Flash(FRAME_MAX, 0, 120);

		m_pBlackFilter->Render(nullptr);

		m_pTurnCircule->Scaling(FRAME_MAX, 4.0f, 2.0f);
		m_pTurnCircule->Flash(FRAME_MAX, 0, 255);
		m_pTurnCircule->AddRotationZ(-0.5f);

		m_pTurnCircule->Render(m_rGameFramework.GetTexture(_T("TURN_CIRCULE")));

		m_pTurnSubCircule->Scaling(FRAME_MAX, 0.0f, 2.5f);
		m_pTurnSubCircule->Flash(FRAME_MAX, 0, 255);
		m_pTurnSubCircule->AddRotationZ(0.5f);

		m_pTurnSubCircule->Render(m_rGameFramework.GetTexture(_T("TURN_CIRCULE")));

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
		RectSize fontSize;
		m_rGameFramework.GetFontSize(_T("TURN_NUM"), &fontSize);

		D3DXVECTOR2 topLeft(m_windowSize.m_width * 0.5f, m_windowSize.m_height * 0.5f - 1.5f * fontSize.m_height);
		m_pStream->SetTopLeft(topLeft);

		(*m_pStream) = totstring(BattleInformation::Turn());
		(*m_pStream) += _T("ターン\n");

		m_pStream->SetColor(algorithm::Tertiary(BattleInformation::CurrentPlayer() == PLAYER_KIND::OPPONENT, 0xFFFF00FF, 0xFFFFFF00));

		tstring player =
			algorithm::Tertiary(BattleInformation::CurrentPlayer() == BattleInformation::StartPlayer(), _T("先行"), _T("後行"));

		(*m_pStream) += player;
		(*m_pStream) += _T("\n");
		(*m_pStream) += algorithm::Tertiary(BattleInformation::CurrentPlayer() == PLAYER_KIND::OPPONENT, _T("エフリ・レフル"), _T("ブレイバー・シオン"));
	}
} // namespace summonersaster
