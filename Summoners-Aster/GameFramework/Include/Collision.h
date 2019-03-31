#ifndef COLLISION_H
#define COLLISION_H

#include "RectSize.h"
#include "Degree.h"
#include "RectDegrees.h"
#include "GameFramework/Vertices.h"
#include "algorithm.h"
#include "SideVectors.h"
#include "VectorsVertexToPos.h"
#include "GameFramework/CustomVertex.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	namespace collision
	{
		/// <summary>
		/// 矩形の辺のベクトルと矩形の頂点から任意の点へのベクトルを用いその点が矩形の内側にあるかを判断する
		/// </summary>
		/// <param name="sideVecs">矩形の辺のベクトル</param>
		/// <param name="vecsVToP">矩形の頂点から任意の点へのベクトル</param>
		/// <returns>中にあればtrue</returns>
		bool IsInner(SideVectors& sideVecs, VectorsVertexToPos& vecsVToP);

		/// <summary>
		/// 既定となる矩形から見てもう一つの矩形の頂点が内包されているかを判定する
		/// </summary>
		/// <param name="baseVertices">基底となる矩形クラス</param>
		/// <param name="vertices">矩形クラス</param>
		/// <returns>中にあればtrue</returns>
		bool IsInner(Vertices& baseVertices, Vertices& vertices);

		/// <summary>
		/// 矩形と矩形の当たり判定チェック
		/// </summary>
		/// <param name="rectA">矩形クラス</param>
		/// <param name="rectB">矩形クラス</param>
		/// <returns>当たっていたらtrue</returns>
		bool Collides(Vertices& rectA, Vertices& rectB);

		/// <summary>
		/// 矩形と点の当たり判定チェック
		/// </summary>
		/// <param name="rect">矩形クラス</param>
		/// <param name="pos">点</param>
		/// <returns>当たっていたらtrue</returns>
		bool IsInner(Vertices& rect, D3DXVECTOR3& pos);

		/// <summary>
		/// 円と円の当たり判定チェック
		/// </summary>
		/// <param name="circleA">矩形クラス</param>
		/// <param name="circleB">矩形クラス</param>
		/// <returns>当たっていたらtrue</returns>
		bool CollidesCircles(Vertices& circleA, Vertices& circleB);

		/// <summary>
		/// 円と点の当たり判定チェック
		/// </summary>
		/// <param name="circle">矩形クラス</param>
		/// <param name="Pos">点</param>
		/// <returns>当たっていたらtrue</returns>
		bool Collides(Vertices& circle, D3DXVECTOR3& Pos);
	}
}

#endif //!COLLISION_H
