#ifndef SIDE_VECTORS_H
#define SIDE_VECTORS_H

#include <d3dx9.h>

#include "RectVectors.h"
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
		/// 矩形の辺のベクトルのファーストクラスコレクション
		/// </summary>
		class SideVectors :public RectVectors
		{
		public:
			SideVectors(Vertices& vertices);

			~SideVectors();

			/// <summary>
			/// 矩形の辺のベクトルを作成する
			/// </summary>
			/// <param name="vertices">作成するための矩形</param>
			void Create(Vertices& vertices);
		};
	}
}

#endif //!SIDE_VECTORS_H
