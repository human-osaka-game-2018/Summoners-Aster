#ifndef CLICK_EFFECT_H
#define CLICK_EFFECT_H

#include <GameFramework.h>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	class ClickEffect :public GraphicEffect
	{
	public:
		ClickEffect();

		~ClickEffect();

		/// <summary>
		/// 全てのパーツを更新する
		/// </summary>
		virtual void Update()override;
	};
}

#endif //!CLICK_EFFECT_H
