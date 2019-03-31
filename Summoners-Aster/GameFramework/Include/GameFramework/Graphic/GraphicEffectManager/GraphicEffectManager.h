#ifndef GRAPHIC_EFFECT_MANAGER_H
#define GRAPHIC_EFFECT_MANAGER_H

#include <vector>

#include "GraphicEffect.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// グラフィックエフェクト管理クラス
	/// </summary>
	class GraphicEffectManager
	{
	public:
		GraphicEffectManager();

		~GraphicEffectManager();

		/// <summary>
		/// エフェクトの登録
		/// </summary>
		/// <param name="pGraphicEffect">登録するエフェクトのポインタ</param>
		void Register(GraphicEffect* pGraphicEffect);

		/// <summary>
		/// エフェクトの全開放
		/// </summary>
		void ReleaseAll();

		/// <summary>
		/// 全てのエフェクトを更新する
		/// </summary>
		void Update();

		/// <summary>
		/// 全てのエフェクトを描画する
		/// </summary>
		void Render();

	protected:
		GraphicEffectManager(const GraphicEffectManager& graphicEffectManager) = delete;

		GraphicEffectManager& operator=(const GraphicEffectManager& graphicEffectManager) = delete;

		void ReleaseEndEffect();

		std::vector<GraphicEffect*> m_pGraphicEffects;
	};
}

#endif //!GRAPHIC_EFFECT_MANAGER_H
