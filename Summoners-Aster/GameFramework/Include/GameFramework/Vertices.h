#ifndef VERTICES_H
#define VERTICES_H

#include <vector>

#include <d3dx9.h>

#include "../RectSize.h"
#include "../Color.h"
#include "../TextureUVs.h"
#include "../Degree.h"
#include "../algorithm.h"
#include "CustomVertex.h"
#include "Graphic/Texture.h"
#include "DirectXParam/DirectXGraphicDevice.h"
#include "DirectXParam/DirectXParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	class Vertices
	{
	public:
		Vertices();

		Vertices(const D3DXVECTOR3& center, const RectSize& size);

		Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color);

		Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs);

		Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs,
			const Degree& rotationX_deg, const Degree& rotationY_deg, const Degree& rotationZ_deg);

		~Vertices();

		/************************************************************************************************************SETTER*/

		inline void SetCenter(const D3DXVECTOR3& center)
		{
			m_center = center;
		}

		void SetCenterAndSize(const D3DXVECTOR3& center, const RectSize& size);

		void SetPosByTopLeft(const D3DXVECTOR3& topLeft, const RectSize& size);

		void SetPosBybottomLeft(const D3DXVECTOR3& bottomLeft, const RectSize& size);

		void SetPosByTopRight(const D3DXVECTOR3& topRight, const RectSize& size);

		void SetPosBybottomRight(const D3DXVECTOR3& bottomRight, const RectSize& size);

		inline void SetSize(const RectSize& size)
		{
			m_baseSize = size;
		}

		inline void SetColor(const Color& color)
		{
			m_color = color;
		}

		inline void SetTextureUVs(const TextureUVs& textureUVs)
		{
			m_textureUVs = textureUVs;
		}

		inline void SetRotationX(const Degree& rotationX_deg)
		{
			m_rotationX_deg = rotationX_deg;
		}

		inline void SetRotationY(const Degree& rotationY_deg)
		{
			m_rotationY_deg = rotationY_deg;
		}

		inline void SetRotationZ(const Degree& rotationZ_deg)
		{
			m_rotationZ_deg = rotationZ_deg;
		}

		void SetCenterAndSizeAndColor(const D3DXVECTOR3& center, const RectSize& size, const Color& color);

		void SetCenterAndSizeAndColorAndTextureUVs(const D3DXVECTOR3& center, const RectSize& size, const Color& color,
			const TextureUVs& textureUVs);

		/************************************************************************************************************GETTER*/

		inline D3DXVECTOR3& GetCenter()
		{
			return	m_center;
		}

		inline RectSize& GetSize()
		{
			return m_baseSize;
		}

		inline const RectSize& GetSizeForRender() const
		{
			if (!m_hasUpdatedSize) return m_baseSize;

			return m_sizeForRender;
		}

		inline Color& GetColor()
		{
			return m_color;
		}

		inline TextureUVs& GetTextureUVs()
		{
			return m_textureUVs;
		}

		inline CustomVertices& GetCustomVertex()
		{
			CreateCustomVertices();

			return m_vertices;
		}

		/// <summary>
		/// 矩形を点滅させる
		/// </summary>
		/// <param name="flashFrameMax">点滅にかかるカウント数</param>
		/// <param name="alphaMin">点滅のアルファ値の最大値</param>
		/// <param name="alphaMax">点滅のアルファ値の最小値</param>
		void Flash(int flashFrameMax, BYTE alphaMin, BYTE alphaMax);

		/// <summary>
		/// 矩形をフェードインさせる
		/// </summary>
		/// <param name="fadeInFrameMax">フェードインにかかる時間</param>
		/// <param name="orginAlpha">初めのアルファ値</param>
		/// <param name="destAlpha">終わりのアルファ値</param>
		void FadeIn(int fadeInFrameMax, BYTE orginAlpha, BYTE destAlpha);
		void FadeOut(int fadeOutFrameMax, BYTE orginAlpha, BYTE destAlpha);

		/// <summary>
		/// 矩形を拡縮させる
		/// </summary>
		/// <param name="scalingFrameMax">拡縮にかかるカウント数</param>
		/// <param name="scaleRateMin">拡縮の最大倍率</param>
		/// <param name="scaleRateMax">拡縮の最小倍率</param>
		void Scaling(int scalingFrameMax, float scaleRateMin, float scaleRateMax);

		/// <summary>
		/// widthのみ拡縮
		/// </summary>
		void ScalingX(int scalingFrameMax, float scaleRateMin, float scaleRateMax);

		/// <summary>
		/// heightのみ拡縮
		/// </summary>
		void ScalingY(int scalingFrameMax, float scaleRateMin, float scaleRateMax);

		inline void AddRotationX(const Degree& rotationX_deg)
		{
			m_rotationX_deg += rotationX_deg;
		}

		inline void AddRotationY(const Degree& rotationY_deg)
		{
			m_rotationY_deg += rotationY_deg;
		}

		inline void AddRotationZ(const Degree& rotationZ_deg)
		{
			m_rotationZ_deg += rotationZ_deg;
		}

		/// <summary>
		/// 描画を行う
		/// </summary>
		/// <param name="pTexture">描画する際に扱うテクスチャ</param>
		virtual void Render(const LPTEXTURE pTexture) = 0;

	protected:
		D3DXVECTOR3 m_center = { 0.0f, 0.0f, 0.0f };
		RectSize m_baseSize;
		RectSize m_sizeForRender;
		Color m_color;
		TextureUVs m_textureUVs;
		Degree m_rotationX_deg;
		Degree m_rotationY_deg;
		Degree m_rotationZ_deg;
		int m_flashFrameCount = 0;
		int m_fadeInFrameCount = 0;
		int m_fadeOutFrameCount = 0;
		int m_additionalScaleFrameCount = 0;
		bool m_hasUpdatedSize = false;

		/// <summary>
		/// 描画を行う際の矩形を作成する
		/// </summary>
		virtual void CreateCustomVertices() = 0;

		/// <summary>
		/// 矩形の頂点分のサイズ
		/// </summary>
		CustomVertices m_vertices;

		LPDIRECT3DDEVICE m_pDirectXGraphicDevice = nullptr;
	};
}

#endif //!VERTICES_H
