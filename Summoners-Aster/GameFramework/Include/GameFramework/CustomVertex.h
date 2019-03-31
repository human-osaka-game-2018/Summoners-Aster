#include <Windows.h>

#include <d3dx9.h>

#include "../RectSize.h"
#include "../Color.h"
#include "../TextureUVs.h"
#include "../Degree.h"

#ifndef CUSTOM_VERTEX_H
#define CUSTOM_VERTEX_H

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSION_11
	/// <summary>
	/// DirectX9での頂点構造体
	/// </summary>
	struct CustomVertex
	{
	public:
		D3DXVECTOR3 m_pos;

		/// <summary>
		/// 重みの逆数 基本1
		/// </summary>
		float m_rHW = 1.0f;

		DWORD m_aRGB = 0xFFFFFFFF;

		D3DXVECTOR2 m_texUV;

		static const int RECT_VERTICES_NUM = 4;
	};
	#elif defined DIRECT_X_VERSOIN_9
	/// <summary>
	/// DirectX9での頂点構造体
	/// </summary>
	struct CustomVertex
	{
	public:
		D3DXVECTOR3 m_pos;

		/// <summary>
		/// 重みの逆数 基本1
		/// </summary>
		float m_rHW = 1.0f;

		DWORD m_aRGB = 0xFFFFFFFF;

		D3DXVECTOR2 m_texUV;
	};

	/// <summary>
	/// CustomVertexのファーストクラスコレクション
	/// </summary>
	class CustomVertices
	{
	public:
		CustomVertices();

		CustomVertices(D3DXVECTOR3& center, RectSize& size, Color& color, TextureUVs& textureUVs);

		~CustomVertices();

		/// <summary>
		/// 頂点情報構造体を再生成する
		/// </summary>
		/// <param name="center">矩形の中心</param>
		/// <param name="size">矩形のサイズ</param>
		/// <param name="color">頂点の色</param>
		/// <param name="textureUVs">テクスチャ座標</param>
		void Reset(D3DXVECTOR3& center, RectSize& size, Color& color, TextureUVs& textureUVs);

		/// <summary>
		/// XYZ順に回転を行う
		/// </summary>
		/// <param name="x">X軸の角度</param>
		/// <param name="y">Y軸の角度</param>
		/// <param name="z">Z軸の角度</param>
		void RotateXYZ(Degree& x, Degree& y, Degree& z);

		/// <summary>
		/// X軸で回転を行う
		/// </summary>
		/// <param name="deg">回転角度</param>
		/// <param name="relativeRotateCenter">回転を行う際の中心が矩形の中心とどれほどのずれが生じているか</param>
		void RotateX(Degree deg, const D3DXVECTOR3& relativeRotateCenter);
		void RotateY(Degree deg, const D3DXVECTOR3& relativeRotateCenter);
		void RotateZ(Degree deg, const D3DXVECTOR3& relativeRotateCenter);

		inline CustomVertex* Get()
		{
			return m_vertices;
		}

		static const int RECT_VERTICES_NUM = 4;

	private:
		void Rotate(const D3DXVECTOR3& relativeRotateCenter, const D3DXMATRIX& rotate);
		
		CustomVertex m_vertices[4];
	};
	#else
	#error "DirectXのバージョンを定義してください"
	#endif
}

#endif //!CUSTOM_VERTEX_H
