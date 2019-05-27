#include "LocaleOnCircumference.h"	

namespace summonersaster
{
	using namespace gameframework;

	LocaleOnCircumference::LocaleOnCircumference(const D3DXVECTOR3& basePos, float radius, float radiusDifference, float startDegreeOnRightVec, float degreeWidth)
	{
		m_baseCenter = basePos;

		std::uniform_real_distribution<float> radiusDistribution(radius, radius + radiusDifference);
		D3DXVECTOR3 distance(radiusDistribution(m_randEngine), 0.0f, 0.0f);

		std::uniform_real_distribution<float> degreeDistribution(startDegreeOnRightVec, startDegreeOnRightVec + degreeWidth);
		gameframework::algorithm::D3DXVec3RotationZ(&distance, degreeDistribution(m_randEngine));
	
		m_pos = m_baseCenter + distance;
	}

	LocaleOnCircumference::~LocaleOnCircumference()
	{

	}

	void LocaleOnCircumference::Impart(Vertices* pVertices)
	{
		D3DXVECTOR3& rVerticesCenter = pVertices->GetCenter();

		rVerticesCenter = m_pos;

		m_isEnd = true;
	}
}
