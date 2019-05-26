#include "MovingEffect.h"

namespace summonersaster
{
	using namespace gameframework;

	MovingEffect::MovingEffect(const D3DXVECTOR3& originPos, const D3DXVECTOR3& destPos, int requireFrameNum)
		:m_requireFrameNum(requireFrameNum), m_originPos(originPos), m_destPos(destPos)
	{
		const int DFFUSE_EFFECT_NUM = 20;

		for (int i = DFFUSE_EFFECT_NUM; i > 0; --i)
		{
			m_partScheduler.Register(new ScalingFlashAbsorbedSquare(_T("キラ不透明"), 0.0f, 0.0f, 0, Color(0xFF0FF320), Color(0xFFFFFF20), 80.0f, 20.0f, m_originPos, 30));
		}

		for (int fi = 0; fi < requireFrameNum; ++fi)
		{
			const int EFFECT_NUM_IN_FRAME = 3;
			for (int ei = 0; ei < EFFECT_NUM_IN_FRAME; ++ei)
			{
				D3DXVECTOR3 dividedDistance = (m_destPos - m_originPos) / static_cast<float>(m_requireFrameNum);
				m_partScheduler.Register(new ScalingFlashSquare(_T("キラ不透明"), 0.24f, 18.0f, 2.0f, 0.0f, fi,
					Color(0xFF00FF00), Color(0xFFFFFF00), m_originPos + dividedDistance * (fi + (ei / static_cast<float>(EFFECT_NUM_IN_FRAME))), 2.0f, 30));
			}
		}

		for (int i = DFFUSE_EFFECT_NUM; i > 0; --i)
		{
			m_partScheduler.Register(new ScalingFlashSquare(_T("キラ不透明"), 3.3f, 10.0f, 10.0f, 0.0f, m_requireFrameNum, Color(0xFF03FF20), Color(0xFFFFFF20), m_destPos, 0.0f, 30));
		}

		m_isAdditionBlendMode = false;
	}

	MovingEffect::~MovingEffect()
	{

	}

	void MovingEffect::Update()
	{
		UpdateParts();

		if (!m_partScheduler.IsEnd()) return;

		m_isEnd = true;
	}
}
