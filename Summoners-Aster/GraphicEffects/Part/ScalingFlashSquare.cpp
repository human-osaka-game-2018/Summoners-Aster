#include "ScalingFlashSquare.h"

namespace summonersaster
{
	using namespace gameframework;

	ScalingFlashSquare::ScalingFlashSquare(const TCHAR* pTexturePath, float diffuseAmount, float baseScale, float additionDifferenceScale,
		float scalingAmount, int startDelayFrame,
		Color originalColor, Color destColor, const D3DXVECTOR3& occurencePos, float rotationZ, int requireFrameNum)
		:Part(pTexturePath), m_startDelayFrame(startDelayFrame), FLASH_COUNT_MAX(requireFrameNum)
	{
		m_lifeFrame -= m_startDelayFrame;

		SizeDifferenceSquare sizeDifferenceSquare(baseScale, additionDifferenceScale);
		sizeDifferenceSquare.ShapeVertices(m_pVertices);

		m_behaviorScheduler.Register(new Locale(occurencePos), BehaviorData::DEFAULT_START, 0, 1);
		m_behaviorScheduler.Register(new Diffuse(diffuseAmount, 0.0f, 360.0f), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
		m_behaviorScheduler.Register(new Scaling(scalingAmount), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
		m_behaviorScheduler.Register(new ColorChange(FLASH_COUNT_MAX, originalColor, destColor), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
		m_behaviorScheduler.Register(new Flash(FLASH_COUNT_MAX, 0, 255), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
		m_behaviorScheduler.Register(new RotationZ(rotationZ), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
	}

	ScalingFlashSquare::~ScalingFlashSquare()
	{

	}

	void ScalingFlashSquare::Update()
	{
		if (m_isEnd) return;

		UpdateVertices();

		if ((m_startDelayFrame--) > 0) return;

		if (m_lifeFrame >= FLASH_COUNT_MAX)
		{
			m_isEnd = true;
		}
	}

	void ScalingFlashSquare::Render(bool isAdditionBlendMode)
	{
		if (m_isEnd) return;

		if (m_startDelayFrame + 1 > 0) return;

		if (isAdditionBlendMode) m_pColorBlender->ToAddtionBlendMode();

		m_pVertices->Render(m_pTextureManager->Get(TEXTURE_KEY));

		m_pColorBlender->ToDefaultBlendMode();
	}
}
