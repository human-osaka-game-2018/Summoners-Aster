#include "Move.h"	

namespace summonersaster
{
	Move::Move(const D3DXVECTOR2& destPos, int requireFrameNum) :m_requireFrameNum(requireFrameNum)
	{
		m_baseCenter = { destPos.x, destPos.y, 0.0f };
	}

	Move::~Move()
	{

	}

	void Move::Impart(Vertices* pVertices)
	{
		D3DXVECTOR3& rVerticesCenter = pVertices->GetCenter();

		if (D3DXVec3Length(&m_oneFrameMovement) == 0.0f)
		{
			m_baseCenter.z = rVerticesCenter.z;
			m_oneFrameMovement = m_baseCenter - rVerticesCenter;

			m_oneFrameMovement /= static_cast<float>(m_requireFrameNum);
		}

		rVerticesCenter += m_oneFrameMovement;

		if (--m_requireFrameNum < 0)
		{
			m_isEnd = true;
		}
	}
}
