#ifndef RECT_VECTORS_H
#define RECT_VECTORS_H

#include <d3dx9.h>

#include "RectSize.h"
#include "Degree.h"
#include "RectDegrees.h"
#include "GameFramework/Vertices.h"
#include "algorithm.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	namespace collision
	{
		/// <summary>
		/// 矩形のベクトルのファーストクラスコレクションの基底
		/// </summary>
		class RectVectors
		{
		public:
			virtual ~RectVectors();

			inline const D3DXVECTOR2* Get() const
			{
				return m_vectors;
			}

			/// <summary>
			/// 引数のベクトルとこのベクトルの角度を引数に入れる
			/// </summary>
			/// <param name="pRectDegrees">ベクトルとの角度を入れる</param>
			/// <param name="pRectVectors">角度を求めるベクトル</param>
			void GetDegrees(RectDegrees* pRectDegrees, const RectVectors* pRectVectors)const;

		protected:
			RectVectors();
			D3DXVECTOR2 m_vectors[4];
		};
	}
}

#endif //!RECT_VECTORS_H
