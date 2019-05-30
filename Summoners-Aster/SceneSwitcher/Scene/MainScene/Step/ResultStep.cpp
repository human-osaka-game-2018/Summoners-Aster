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
		GameFrameworkFactory::Create(&m_pVertices);
	}

	void ResultStep::Finalize()
	{
		m_stagingTakesFrames = 240;

		m_loadedResult = false;

		delete m_pStream;
		m_pStream = nullptr;

		delete m_pVertices;
		m_pVertices = nullptr;
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

		float alphaRatio = 1.0f - (m_stagingTakesFrames / static_cast<float>(m_STAGING_TAKES_FRAME_MAX));
		alphaRatio = min(max(alphaRatio, 0.0f), 1.0f);

		m_stagingColor[Color::COMPONENT::ALPHA] = static_cast<BYTE>(255 * alphaRatio);
		m_pStream->SetColor(m_stagingColor);

		m_pVertices->GetColor()[Color::COMPONENT::ALPHA] = static_cast<BYTE>(160 * alphaRatio);

		if (*m_pStream == _T("WIN")) m_rGameFramework.ToAddtionBlendMode();
		m_pVertices->Render(m_rGameFramework.GetTexture(_T("RESULT_BACK")));
		m_rGameFramework.ToDefaultBlendMode();

		m_pStream->Render(m_rGameFramework.GetFont(_T("TURN_NUM")), DT_CENTER);

		if (m_stagingTakesFrames-- <= 0)
		{
			m_stagingTakesFrames = 0;

			--m_periodOfFramesStagingEndToEnd;
		}

		if (m_periodOfFramesStagingEndToEnd < 0)
		{
			SwitchEventMediatorBase<Step>::GetRef().SendSwitchEvent(STEP_KIND::PLAYERS_INFOMATION_RENDERING);
			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(_T("HOME"));
		}
	}

	void ResultStep::LoadResult()
	{
		if (m_loadedResult) return;

		m_loadedResult = true;
		*m_pStream = algorithm::Tertiary(BattleInformation::Winner() == PLAYER_KIND::PROPONENT, _T("WIN"), _T("LOSE"));

		m_stagingColor = algorithm::Tertiary(*m_pStream == _T("WIN"), 0x00FF2323, 0x002323FF);

		if (*m_pStream == _T("WIN")) {
			m_rGameFramework.OneShotStart(L"WIN");
		}
		else m_rGameFramework.OneShotStart(L"LOSE");

		RectSize fontSize(0.0f, 0.0f);
		m_rGameFramework.GetFontSize(_T("TURN_NUM"), &fontSize);

		D3DXVECTOR2 topLeft(0.5f * m_windowSize.m_width, 0.5f * (m_windowSize.m_height - fontSize.m_height));
		m_pStream->SetTopLeft(topLeft);

		m_pVertices->SetCenterAndSize(D3DXVECTOR3(m_windowSize.m_width * 0.5f, m_windowSize.m_height * 0.5f, 0.0f), m_windowSize);
		m_pVertices->SetColor(algorithm::Tertiary(*m_pStream == _T("WIN"), 0x00FFFFFF, 0x00000000));
	}

} // namespace summonersaster
