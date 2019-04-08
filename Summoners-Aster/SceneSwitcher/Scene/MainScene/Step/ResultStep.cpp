#include "ResultStep.h"

namespace summonersaster
{
	ResultStep::ResultStep()
	{

	}

	ResultStep::~ResultStep()
	{

	}

	void ResultStep::Initialize()
	{
		gameframework::GameFrameworkFactory::Create(&m_pStream);

		*m_pStream = _T("WIN");

		gameframework::WindowParam::GetWindowSize(&m_windowSize);

		RectSize fontSize;
		fontSize.m_width = m_windowSize.m_width * 0.01f;
		fontSize.m_height = 2.0f * fontSize.m_width;

		m_rGameFramework.CreateFont(_T("RESULT"), fontSize, nullptr);
	}

	void ResultStep::Finalize()
	{
		
	}

	void ResultStep::Update()
	{
		
	}

	void ResultStep::Render()
	{
		m_pStream->Render(m_rGameFramework.GetFont(_T("RESULT")), DT_CENTER);

		if (m_stagingTakesFrames-- >= 0)
		{
			m_stagingTakesFrames = 0;

			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(_T("HOME"));
		}
	}
} // namespace summonersaster
