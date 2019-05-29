#include "AbilityEffect.h"

namespace summonersaster
{
	using namespace gameframework;

	AbilityEffect::AbilityEffect(const D3DXVECTOR3& originPos, const D3DXVECTOR3& destPos, int requireFrameNum)
		:m_requireFrameNum(requireFrameNum), m_originPos(originPos), m_destPos(destPos)
	{
		const int DFFUSE_EFFECT_NUM = 35;

		m_partScheduler.Register(new ScalingFlashSquare(_T("キラ十字円"), 0.0f, 45, 0.0f, 2.0f, 0, Color(0xFFffa500), Color(0xFF87cefa), m_originPos, 2.0f, m_requireFrameNum));
		m_partScheduler.Register(new ScalingFlashSquare(_T("中空き円"), 0.0f, 30, 0.0f, 2.5f, 0, Color(0xFFFFFF20), Color(0xFF191970), m_originPos, 4.0f, m_requireFrameNum));

		const int FRAME_DELAY = 5;

		for (int i = DFFUSE_EFFECT_NUM; i > 0; --i)
		{
			m_partScheduler.Register(new ScalingFlashAbsorbedSquare(_T("キラ不透明"), 0.0f, 1.0f, 0, Color(0xFF191970), Color(0xFFffa500), 80.0f, 20.0f, m_originPos, 30));
			m_partScheduler.Register(new ScalingFlashAbsorbedSquare(_T("キラ不透明"), 0.0f, 1.0f, FRAME_DELAY, Color(0xFF191970), Color(0xFFffa500), 80.0f, 20.0f, m_originPos, 30));
			m_partScheduler.Register(new ScalingFlashAbsorbedSquare(_T("キラ不透明"), 0.0f, 1.0f, 2 * FRAME_DELAY, Color(0xFF191970), Color(0xFFffa500), 80.0f, 20.0f, m_originPos, 30));
			m_partScheduler.Register(new ScalingFlashSquare(_T("キラ不透明"), 3.3f, 10.0f, 10.0f, 0.0f, m_requireFrameNum, Color(0xFFffa500), Color(0xFF87cefa), m_destPos, 0.0f, 30));
			m_partScheduler.Register(new ScalingFlashSquare(_T("キラ不透明"), 3.3f, 10.0f, 10.0f, 0.0f, m_requireFrameNum + FRAME_DELAY, Color(0xFFffa500), Color(0xFF87cefa), m_destPos, 0.0f, 30));
			m_partScheduler.Register(new ScalingFlashSquare(_T("キラ不透明"), 3.3f, 10.0f, 10.0f, 0.0f, m_requireFrameNum + 2 * FRAME_DELAY, Color(0xFFffa500), Color(0xFF87cefa), m_destPos, 0.0f, 30));
		}

		m_isAdditionBlendMode = false;
	}

	AbilityEffect::~AbilityEffect()
	{

	}

	void AbilityEffect::Update()
	{
		UpdateParts();

		if (!m_partScheduler.IsEnd()) return;

		m_isEnd = true;
	}
}
