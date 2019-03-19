#ifndef VERTICES_H
#define VERTICES_H

#include <vector>

#include <d3dx9.h>

#include "../RectSize.h"
#include "../Color.h"
#include "../TextureUVs.h"
#include "../Degree.h"
#include "../algorithm.h"
#include "Graphic/Texture.h"
#include "DirectXParam/DirectXGraphicDevice.h"
#include "DirectXParam/DirectXParam.h""

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

		static const int RECT_VERTICES_NUM = 4;
	};
	#else
	#error "DirectXのバージョンを定義してください"
	#endif

	class Vertices
	{
	public:
		Vertices() 
		{
			DirectXParam::GetDirectXGraphicDevice()->Get(&m_pDirectXGraphicDevice);
		}

		Vertices(const D3DXVECTOR3& center, const RectSize& halfScale)
		{
			SetCenterAndScale(center, halfScale);
		}

		Vertices(const D3DXVECTOR3& center, const RectSize& halfScale, const Color& color)
		{
			SetCenterAndScaleAndColor(center, halfScale, color);
		}

		Vertices(const D3DXVECTOR3& center, const RectSize& halfScale, const Color& color, const TextureUVs& textureUVs)
		{
			SetCenterAndHalfScaleAndColorAndTextureUVs(center, halfScale, color, textureUVs);
		}

		Vertices(const D3DXVECTOR3& center, const RectSize& halfScale, const Color& color, const TextureUVs& textureUVs,
			const Degree& rotationX_deg, const Degree& rotationY_deg, const Degree& rotationZ_deg)
		{
			SetCenterAndHalfScaleAndColorAndTextureUVs(center, halfScale, color, textureUVs);

			SetRotationX(rotationX_deg);
			SetRotationY(rotationY_deg);
			SetRotationZ(rotationZ_deg);
		}

		~Vertices() {};

		/************************************************************************************************************SETTER*/
		inline void SetCenter(const D3DXVECTOR3& center)
		{
			m_center = center;
		}

		inline void SetHalfScale(const RectSize& halfScale)
		{
			m_baseHalfScale = halfScale;
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

		inline void SetCenterAndScale(const D3DXVECTOR3& center, const RectSize& halfScale)
		{
			SetCenter(center);
			SetHalfScale(halfScale);
		}

		inline void SetCenterAndScaleAndColor(const D3DXVECTOR3& center, const RectSize& halfScale, const Color& color)
		{
			SetCenterAndScale(center, halfScale);
			SetColor(color);
		}

		inline void SetCenterAndHalfScaleAndColorAndTextureUVs(const D3DXVECTOR3& center, const RectSize& halfScale, const Color& color, 
			const TextureUVs& textureUVs)
		{
			SetCenterAndScaleAndColor(center, halfScale, color);
			SetTextureUVs(textureUVs);
		}

		/************************************************************************************************************GETTER*/
		inline D3DXVECTOR3& GetCenter()
		{
			return	m_center;
		}

		inline RectSize& GetHalfScale()
		{
			return m_baseHalfScale;
		}

		inline Color& GetColor()
		{
			return m_color;
		}

		inline TextureUVs& SetTextureUVs()
		{
			return m_textureUVs;
		}
		
		/// <summary>
		/// 矩形を点滅させる
		/// </summary>
		/// <param name="flashFrameMax">点滅にかかるカウント数</param>
		/// <param name="alphaMin">点滅のアルファ値の最大値</param>
		/// <param name="alphaMax">点滅のアルファ値の最小値</param>
		inline void Flash(int flashFrameMax, BYTE alphaMin, BYTE alphaMax)
		{
			algorithm::CountUp(&m_flashFrameCount, flashFrameMax);
			m_color.m_alpha = static_cast<BYTE>(algorithm::SwitchMinBetweenMax(m_flashFrameCount, flashFrameMax, alphaMin, alphaMax));
		}
		
		/// <summary>
		/// 矩形を拡縮させる
		/// </summary>
		/// <param name="flashFrameMax">拡縮にかかるカウント数</param>
		/// <param name="scaleRateMin">拡縮の最大倍率</param>
		/// <param name="scaleRateMax">拡縮の最小倍率</param>
		inline void Scaling(int flashFrameMax, float scaleRateMin, float scaleRateMax)
		{
			algorithm::CountUp(&m_flashFrameCount, flashFrameMax);
			float scaleRate = algorithm::SwitchMinBetweenMax(m_flashFrameCount, flashFrameMax, scaleRateMin, scaleRateMax);

			m_baseHalfScale = m_halfScale * scaleRate;
		}
		
		/// <summary>
		/// widthのみ拡縮
		/// </summary>
		inline void ScalingX(int flashFrameMax, float scaleRateMin, float scaleRateMax)
		{
			algorithm::CountUp(&m_flashFrameCount, flashFrameMax);
			float scaleRate = algorithm::SwitchMinBetweenMax(m_flashFrameCount, flashFrameMax, scaleRateMin, scaleRateMax);

			m_baseHalfScale.m_width = m_halfScale.m_width * scaleRate;
		}

		/// <summary>
		/// heightのみ拡縮
		/// </summary>
		inline void ScalingY(int flashFrameMax, float scaleRateMin, float scaleRateMax)
		{
			algorithm::CountUp(&m_flashFrameCount, flashFrameMax);
			float scaleRate = algorithm::SwitchMinBetweenMax(m_flashFrameCount, flashFrameMax, scaleRateMin, scaleRateMax);

			m_baseHalfScale.m_height = m_halfScale.m_height * scaleRate;
		}

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
		virtual void Render(const Texture* pTexture) = 0;

	protected:
		/// <summary>
		/// 描画を行う際の矩形を作成する
		/// </summary>
		virtual void Normalize() = 0;

		D3DXVECTOR3 m_center = { 0.0f, 0.0f, 0.0f };
		RectSize m_baseHalfScale;
		RectSize m_halfScale;
		Color m_color;
		TextureUVs m_textureUVs;
		Degree m_rotationX_deg;
		Degree m_rotationY_deg;
		Degree m_rotationZ_deg;
		int m_flashFrameCount = 0;
		int m_additionalScaleFrameCount = 0;
		
		/// <summary>
		/// 矩形の頂点分のサイズ
		/// </summary>
		CustomVertex m_vertices[4];

		LPDIRECT3DDEVICE m_pDirectXGraphicDevice = nullptr;
	};
}

#endif //!VERTICES_H
