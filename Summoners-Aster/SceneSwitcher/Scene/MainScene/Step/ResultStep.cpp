#include "ResultStep.h"

namespace summonersaster
{
	ResultStep::ResultStep()
	{
		gameframework::WindowParam::GetWindowSize(&m_windowSize);

		gameframework::GameFrameworkFactory::Create(&m_pStream);
	}

	ResultStep::~ResultStep()
	{
		
	}

	void ResultStep::Initialize()
	{
	
	}

	void ResultStep::Finalize()
	{
		m_stagingTakesFrames = 120;

		m_isLoadedResult = false;
	}

	void ResultStep::Update()
	{
		LoadResult();
	}

	void ResultStep::Render()
	{
		m_pStream->Render(m_rGameFramework.GetFont(_T("RESULT")), DT_CENTER);

		if (m_stagingTakesFrames-- >= 0)
		{
			m_stagingTakesFrames = 0;

			SwitchEventMediatorBase<Step>::GetRef().SendSwitchEvent(STEP_KIND::PLAYERS_INFOMATION_RENDERING);
			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(_T("HOME"));
		}
	}

	void ResultStep::LoadResult()
	{
		if (m_isLoadedResult) return;

		m_isLoadedResult = true;

		*m_pStream = _T("WIN");
	}

} // namespace summonersaster
