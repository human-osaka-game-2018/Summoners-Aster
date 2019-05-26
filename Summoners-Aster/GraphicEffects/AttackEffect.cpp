#include "AttackEffect.h"

namespace summonersaster
{
	using namespace gameframework;

	AttackEffect::AttackEffect(const D3DXVECTOR3& originPos, const D3DXVECTOR3& destPos, int requireFrameNum)
		:m_requireFrameNum(requireFrameNum), m_originPos(originPos), m_destPos(destPos)
	{
		const int EFFECT_NUM = 10;

		for (int fi = 0; fi < requireFrameNum; ++fi)
		{
			const int EFFECT_NUM_IN_FRAME = 3;
			for (int ei = 0; ei < EFFECT_NUM_IN_FRAME; ++ei)
			{
				D3DXVECTOR3 dividedDistance = (m_destPos - m_originPos) / static_cast<float>(m_requireFrameNum);
				m_partScheduler.Register(new ScalingFlashSquare(_T("キラ不透明"), 0.14f, 9.0f, 2.0f, 0.0f, fi,
					Color(0xFFFF0000), Color(0xFFFFAA00), m_originPos + dividedDistance * (fi + (ei / static_cast<float>(EFFECT_NUM_IN_FRAME))), 2.0f, 30));
			}
		}

		m_partScheduler.Register(new ScalingFlashSquare(_T("キラ十字不透明"), 0.0f, 0.0f, 0.0f, 10.0f, m_requireFrameNum, Color(0xFFFF1000), Color(0xFFFFAA10), m_destPos, 1.0f, 25));
		m_partScheduler.Register(new ScalingFlashSquare(_T("中空き円不透明"), 0.0f, 0.0f, 0.0f, 4.0f, m_requireFrameNum, Color(0xFFFF2000), Color(0xFFFFAA00), m_destPos, 0.0f, 20));
		m_partScheduler.Register(new ScalingFlashSquare(_T("中空き円不透明"), 0.0f, 0.0f, 0.0f, 2.5f, m_requireFrameNum, Color(0xFFFF0020), Color(0xFFFFAA10), m_destPos, 0.0f, 30));

		for (int i = 7; i > 0; --i)
		{
			m_partScheduler.Register(new ScalingFlashSquare(_T("キラ不透明"), 1.0f, 9.0f, 0.0f, 0.13f, m_requireFrameNum + rand() % 20, Color(0xFFFF0320), Color(0xFFFFAA20), m_destPos, 0.0f, 30));
		}

		m_isAdditionBlendMode = false;
	}

	AttackEffect::~AttackEffect()
	{

	}

	void AttackEffect::Update()
	{
		UpdateParts();

		if (!m_partScheduler.IsEnd()) return;

		m_isEnd = true;
	}
}
