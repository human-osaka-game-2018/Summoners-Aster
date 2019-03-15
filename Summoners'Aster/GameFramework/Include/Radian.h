#ifndef RADIAN_H
#define RADIAN_H

#include <d3dx9.h>

#include "RotationValue.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{	
	/// <summary>
	/// 弧度法での角度クラス
	/// </summary>
	/// <seealso cref="RotationValue{Radian}" />
	class Radian :public RotationValue<Radian>
	{
	public:
		Radian(float amount, float min = -D3DX_PI) :RotationValue(amount, min, ONE_CYCLE_AMOUNT) {};
		~Radian() {};

		/// <summary>
		/// 値を代入する
		/// </summary>
		/// <param name="rhs">代入したい値</param>
		/// <returns>thisの参照</returns>
		Radian& operator=(const Radian& rhs)
		{
			Normalize(rhs.Raw());

			return *this;
		}

		Radian& operator=(float rhs)
		{
			Normalize(rhs);

			return *this;
		}

		static const float ONE_CYCLE_AMOUNT;
	};
}

#endif //!RADIAN_H
