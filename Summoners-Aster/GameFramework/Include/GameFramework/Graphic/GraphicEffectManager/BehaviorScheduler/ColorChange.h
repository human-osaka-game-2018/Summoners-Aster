#ifndef COLOR_CHANGE_H
#define COLOR_CHANGE_H

#include <Windows.h>
#include <vector>

#include "Behavior.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 色の遷移
	/// </summary>
	class ColorChange :public Behavior
	{
	public:
		/// <param name="changeColorFrame">色の遷移にかかるフレーム数</param>
		/// <param name="originalColor">元の色</param>
		/// <param name="destColor">遷移後の色</param>
		ColorChange(int changeColorFrame, Color& originalColor, Color& destColor);

		virtual ~ColorChange();

		/// <summary>
		/// 引数の矩形クラスに属性を付与する
		/// </summary>
		/// <param name="pVertices">矩形クラスのポインタ</param>
		virtual void Impart(Vertices* pVertices)override;

	protected:
		static const std::vector<Color::COMPONENT> COLOR_COMPONENTS;
		Color m_originalColor;

		const int CHANGE_COLOR_FRAME_MAX;
		int m_changeColorFrame = 0;

		std::vector<int> m_colorComponetAmounts;
	};
}

#endif //!COLOR_CHANGE_H
