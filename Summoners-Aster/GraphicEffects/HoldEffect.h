#ifndef HOLD_EFFECT_H
#define HOLD_EFFECT_H

#include <GameFramework.h>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// マウスの左ボタンを押している間出す際のエフェクト
	/// </summary>
	class HoldEffect :public GraphicEffect
	{
	public:
		HoldEffect();

		~HoldEffect();

		/// <summary>
		/// 全てのパーツを更新する
		/// </summary>
		virtual void Update()override;
	};
}

#endif //!HOLD_EFFECT_H
