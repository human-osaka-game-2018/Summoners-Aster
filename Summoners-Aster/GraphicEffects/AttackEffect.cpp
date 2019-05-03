#include "AttackEffect.h"

namespace summonersaster
{
	using namespace gameframework;

	AttackEffect::AttackEffect(const D3DXVECTOR3& originPos, const D3DXVECTOR3& destPos, int requireFrameNum)
		:m_requireFrameNum(requireFrameNum), m_originPos(originPos), m_destPos(destPos)
	{
		const int EFFECT_NUM = 10;

		for (int i = 0; i < EFFECT_NUM; ++i)
		{
			m_partScheduler.Register(new SquareMoveToDest(_T("円"), 1.0f, 0.13f, rand() % 10,
				Color(0xFFFF2323), Color(0xFFFF23FF), m_originPos, m_destPos, m_requireFrameNum));
		}
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
