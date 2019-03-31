#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "Behavior.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 点滅
	/// </summary>
	class Diffuse :public Behavior
	{
	public:
		Diffuse(float movement, const Degree& min, const Degree& width_deg);

		virtual ~Diffuse();

		virtual void Impart(Vertices* pVertices)override;

	protected:
		D3DXVECTOR2 m_baseMovementVec;
	};
}

#endif //!DIFFUSE_H
