#include "ScalingFlashAbsorbedSquare.h"

namespace summonersaster
{
	using namespace gameframework;

	ScalingFlashAbsorbedSquare::ScalingFlashAbsorbedSquare(const TCHAR* pTexturePath,
		float diffuseAmount, float scalingAmount, int startDelayFrame,
		Color originalColor, Color destColor,
		float radius, float radiusDifference, const D3DXVECTOR3& destPos, int requireFrameNum)
		:Part(pTexturePath), m_startDelayFrame(startDelayFrame), LIFE_LIMIT(requireFrameNum)
	{
		m_lifeFrame -= m_startDelayFrame;

		SizeDifferenceSquare sizeDifferenceSquare(5.0f, 10.0f);
		sizeDifferenceSquare.ShapeVertices(m_pVertices);

		m_behaviorScheduler.Register(new LocaleOnCircumference(destPos,radius, radiusDifference, 0.0f, 360.0f), BehaviorData::DEFAULT_START, 0, 1);
		m_behaviorScheduler.Register(new Move(D3DXVECTOR2(destPos.x, destPos.y), requireFrameNum), BehaviorData::DEFAULT_START, 0, requireFrameNum);
		m_behaviorScheduler.Register(new Diffuse(diffuseAmount, 0.0f, 360.0f), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
		m_behaviorScheduler.Register(new Scaling(scalingAmount), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
		m_behaviorScheduler.Register(new ColorChange(LIFE_LIMIT, originalColor, destColor), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
		m_behaviorScheduler.Register(new Flash(LIFE_LIMIT, 0, 255), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
	}

	ScalingFlashAbsorbedSquare::~ScalingFlashAbsorbedSquare()
	{

	}

	void ScalingFlashAbsorbedSquare::Update()
	{
		if (m_isEnd) return;

		UpdateVertices();

		if ((m_startDelayFrame--) > 0) return;

		if (m_lifeFrame >= LIFE_LIMIT)
		{
			m_isEnd = true;
		}
	}

	void ScalingFlashAbsorbedSquare::Render(bool isAdditionBlendMode)
	{
		if (m_isEnd) return;

		if (m_startDelayFrame + 1 > 0) return;

		if (isAdditionBlendMode) m_pColorBlender->ToAddtionBlendMode();

		m_pVertices->Render(m_pTextureManager->Get(TEXTURE_KEY));

		m_pColorBlender->ToDefaultBlendMode();
	}
}
