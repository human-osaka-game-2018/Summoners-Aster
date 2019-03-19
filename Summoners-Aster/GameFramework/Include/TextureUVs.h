#ifndef TEXTURE_UVS_H
#define TEXTURE_UVS_H

#include <Windows.h>
#include <vector>

#include <d3dx9.h>

#include "RectSize.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// Texture座標クラス
	/// </summary>
	class TextureUVs
	{
	public:
		/// <remarks>
		/// アニメーションを使わない場合やデフォルトのTuTvを扱う場合はこちらを使う
		/// </remarks>
		TextureUVs();

		/// <param name="topLeft">テクスチャの左上のピクセル位置</param>
		/// <param name="textureSize">テクスチャ一枚の大きさ</param>
		/// <param name="oneDivideSize">統合ファイルの一区切りの大きさ</param>
		/// <param name="dividesNumMax">アニメーション枚数</param>
		TextureUVs(const D3DXVECTOR2& topLeft, const RectSize& textureSize, const RectSize& oneDivideSize, int dividesNumMax);

		~TextureUVs();

		inline void SetTextureUVsParams(const D3DXVECTOR2& topLeft, const RectSize& textureSize, const RectSize& oneDivideSize, int dividesNumMax)
		{
			m_topLeft = topLeft;
			m_textureSize = textureSize;
			m_oneDivideSize = oneDivideSize;
			m_dividesNumMax = dividesNumMax;
		}

		/// <summary>
		/// テクスチャ座標vectorのアドレスを返す
		/// </summary>
		/// <returns>テクスチャ座標vectorのアドレス</returns>
		inline const std::vector<D3DXVECTOR2>* Get()
		{
			Normalize();

			return &m_textureUVs;
		}

		/// <summary>
		/// テクスチャ座標を次にずらす
		/// </summary>
		/// <remarks>
		/// アニメーションの最大枚数を超えると初めに戻りループする
		/// </remarks>
		void Next();	//関数名は審議中

		/// <summary>
		/// 配列番号から頂点が右辺にあるかを判断する
		/// </summary>
		/// <param name="index">頂点の配列番号</param>
		/// <returns>
		///  右辺だったらtrue
		/// </returns>
		static inline bool IsRightSide(int index)
		{
			return (index == 1 || index == 2);
		}

		/// <summary>
		/// 配列番号から頂点が底辺にあるかを判断する
		/// </summary>
		/// <param name="index">頂点の配列番号</param>
		/// <returns>
		///  底辺だったらtrue
		/// </returns>
		static inline bool IsUnderSide(int index)
		{
			return (index == 2 || index == 3);
		}

	private:
		/// <summary>
		/// テクスチャ座標を必要数分確保する
		/// </summary>
		void ResizeTextureUVsForRect();

		/// <summary>
		/// テクスチャ座標の正規化を行う
		/// </summary>
		void Normalize();

		std::vector<D3DXVECTOR2> m_textureUVs;
		D3DXVECTOR2 m_topLeft = { 0.0f, 0.0f };
		RectSize m_textureSize = { 1.0f, 1.0f };
		RectSize m_oneDivideSize = { 1.0f, 1.0f };

		/// <summary>
		/// 現在のアニメーションの番号 1始まり
		/// </summary>
		int m_currentDivideNum = 1;
		int m_dividesNumMax = 1;
	};
}

#endif //!TEXTURE_UVS_H
