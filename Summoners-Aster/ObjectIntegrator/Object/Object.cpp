#include "Object.h"

namespace summonersaster
{
	Object::~Object()
	{

	}

	void Object::LoadResource()
	{

	}

	void Object::Update()
	{

	}

	Object::Object(float z) : m_z(z)
	{
		gameframework::WindowParam::GetWindowSize(&m_windowSize);
		m_windowCenter = { m_windowSize.m_width * 0.5f, m_windowSize.m_height * 0.5f };
	}
} // namespace summonersaster
