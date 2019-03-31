#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "../../../Vertices.h"
#include "../../../../Window/WindowParam.h"
#include "../../../../Algorithm.h"
#include "../../../../Color.h"
#include "../../../../Degree.h"
#include "../../../../RectSize.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// Verticesクラスの動作を決定するクラス
	/// </summary>
	class Behavior
	{
	public:
		virtual ~Behavior();

		/// <summary>
		/// 引数の矩形クラスに属性を付与する
		/// </summary>
		/// <param name="pVertices">矩形クラスのポインタ</param>
		virtual void Impart(Vertices* pVertices) = 0;

		inline bool IsEnd()const
		{
			return m_isEnd;
		}

		inline const D3DXVECTOR3& GetBaseCenter()
		{
			return m_baseCenter;
		}

	protected:
		Behavior();

		int m_lifeFrame = 0;
		D3DXVECTOR2 m_velocity = { 0.0f, 0.0f };
		D3DXVECTOR3 m_baseCenter = { 0.0f, 0.0f, 0.0f };

		bool m_isEnd = false;

		std::minstd_rand m_randEngine;
	};
}

#endif //!BEHAVIOR_H
