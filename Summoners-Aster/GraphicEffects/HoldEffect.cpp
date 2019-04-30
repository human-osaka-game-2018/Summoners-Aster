#include "HoldEffect.h"

namespace gameframework
{
	HoldEffect::HoldEffect()
	{
		m_partScheduler.Register(new DiffuseDifferenceSquare(_T("キラ"), 0.3f, 0.16f, 0, Color(0xFF23FFFF), Color(0xFFFF23FF)));
	}

	HoldEffect::~HoldEffect()
	{

	}

	void HoldEffect::Update()
	{
		UpdateParts();

		if (!m_partScheduler.IsEnd()) return;
		
		m_isEnd = true;
	}
}
