#include "SummonEffect.h"

namespace summonersaster
{
	using namespace gameframework;

	SummonEffect::SummonEffect(const D3DXVECTOR3& occurencePos)
	{
		for (int i = 0; i < 3; ++i)
		{
			int delayFrame = 15 * i;

			m_partScheduler.Register(new ScalingFlashSquare(_T("円"), 0.0f, 0.0f, 0.0f, 3.0f, delayFrame,
				Color(0xFF23FFFF), Color(0xFF23FF88), occurencePos, 3.0f, 60));

			m_partScheduler.Register(new ScalingFlashSquare(_T("中空き円"), 0.0f, 0.0f, 0.0f, 2.5f, delayFrame,
				Color(0xFFFF2323), Color(0xFFFF2323), occurencePos, 2.0f, 60));

			m_partScheduler.Register(new ScalingFlashSquare(_T("中空き円"), 0.0f, 0.0f, 0.0f, 4.5f, delayFrame,
				Color(0xFF2323FF), Color(0xFF23FF88), occurencePos, 2.0f, 60));
		}
	}

	SummonEffect::~SummonEffect()
	{

	}

	void SummonEffect::Update()
	{
		UpdateParts();

		if (!m_partScheduler.IsEnd()) return;

		m_isEnd = true;
	}
}
