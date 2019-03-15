#ifndef DEGREE_H
#define DEGREE_H

#include "RotationValue.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{	
	/// <summary>
	/// 度数法での角度クラス
	/// </summary>
	/// <seealso cref="RotationValue{Degree}" />
	class Degree :public RotationValue<Degree>
	{
	public:
		Degree(float amount = 0.0f, float min = -180.0f) :RotationValue(amount, min, ONE_CYCLE_AMOUNT) {};
		~Degree() {};

		/// <summary>
		/// 値を代入する
		/// </summary>
		/// <param name="rhs">代入したい値</param>
		/// <returns>thisの参照</returns>
		Degree& operator=(const Degree& rhs)
		{
			Normalize(rhs.Raw());

			return *this;
		}

		Degree& operator=(float rhs)
		{
			Normalize(rhs);

			return *this;
		}

		static const float ONE_CYCLE_AMOUNT;
	};
}

#endif //!DEGREE_H
