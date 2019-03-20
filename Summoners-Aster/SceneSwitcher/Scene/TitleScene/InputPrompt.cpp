#include "InputPrompt.h"

using namespace gameframework;

namespace summonersaster
{
	InputPrompt::InputPrompt() :Task(0.0f)
	{
		Initialize();
	}

	InputPrompt::~InputPrompt()
	{
		Finalize();
	}

	void InputPrompt::Initialize()
	{
		GameFrameworkFactory::Create(&m_pStream);
		(*m_pStream) = _T("Click To Screen");

		LoadResource();
	}

	void InputPrompt::LoadResource()
	{
		m_rGameFramework.CreateFont(_T("INPUT_PROMPT"), RectSize(25.0f, 50.0f), _T("IPAex明朝"));
	}

	void InputPrompt::Finalize()
	{
		Release();
	}

	void InputPrompt::Release()
	{
		delete m_pStream;
		m_rGameFramework.ReleaseFont(_T("INPUT_PROMPT"));
	}

	void InputPrompt::Render()
	{
		m_pStream->SetTopLeft(D3DXVECTOR2(m_windowCenter.x, m_windowCenter.y * 1.5f));
		m_pStream->Flash(120, 60, 255);

		m_pStream->Render(m_rGameFramework.GetFont(_T("INPUT_PROMPT")), DT_CENTER);

		m_isFinished = true;
	}
} // namespace summonersaster
