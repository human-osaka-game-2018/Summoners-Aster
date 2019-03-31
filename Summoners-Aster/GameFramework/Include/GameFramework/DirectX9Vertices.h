#ifndef DIRECT_X_9_VERTICES_H
#define DIRECT_X_9_VERTICES_H

#include <vector>

#include <d3dx9.h>

#include "../RectSize.h"
#include "../Color.h"
#include "../TextureUVs.h"
#include "../Degree.h"
#include "../algorithm.h"
#include "Graphic/Texture.h"
#include "Vertices.h"
#include "DirectXParam/DirectXGraphicDevice.h"
#include "DirectXParam/DirectXParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
#ifdef DIRECT_X_VERSOIN_9

	class DirectX9Vertices :public Vertices
	{
	public:
		DirectX9Vertices();

		DirectX9Vertices(const D3DXVECTOR3& center, const RectSize& size);

		DirectX9Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color);

		DirectX9Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs);

		DirectX9Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs,
			const Degree& rotationX_deg, const Degree& rotationY_deg, const Degree& rotationZ_deg);

		~DirectX9Vertices();

		/// <summary>
		/// 描画を行う
		/// </summary>
		/// <param name="pTexture">描画する際に扱うテクスチャ</param>
		void Render(const LPTEXTURE pTexture);

	private:
		/// <summary>
		/// CustomVertexの形に正規化する
		/// </summary>
		void CreateCustomVertices();
	};

#endif //DIRECT_X_VERSOIN_9
}

#endif //!DIRECT_X_9_VERTICES_H
