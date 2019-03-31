#ifndef VECTORS_VERTEX_TO_POS_H
#define VECTORS_VERTEX_TO_POS_H

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
		/// 頂点から任意への点へのベクトルのファーストクラスコレクション
		/// </summary>
		class VectorsVertexToPos :public RectVectors
		{
		public:
			VectorsVertexToPos(Vertices& vertices, D3DXVECTOR3& pos);
			~VectorsVertexToPos();

			void Create(Vertices& vertices, D3DXVECTOR3& pos);
		};
	}
}

#endif //!VECTORS_VERTEX_TO_POS_H
