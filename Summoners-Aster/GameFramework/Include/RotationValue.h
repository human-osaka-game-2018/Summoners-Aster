#ifndef ROTATION_VALUE_H
#define ROTATION_VALUE_H

#include <d3dx9.h>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{	
	/// <summary>
	/// 角度の基底クラス
	/// </summary>
	/// <remarks>
	/// Tは継承するクラスそれ自身
	/// </remarks>
	template<class T>
	class RotationValue
	{
	public:
		inline float Raw() const
		{
			return m_rawAmount;
		}

		inline float Normalized() const
		{
			return m_normalizedAmount;
		}

		/// <summary>
		/// 足した値を返す
		/// </summary>
		/// <param name="rhs">足す値</param>
		/// <returns>足した結果</returns>
		const T operator+(const T& rhs) const
		{
			return T(m_rawAmount + rhs.Raw(), m_min);
		}

		const T operator+(float rhs) const
		{
			return T(m_rawAmount + rhs, m_min);
		}

		/// <summary>
		/// 引いた値を返す
		/// </summary>
		/// <param name="rhs">引く値</param>
		/// <returns>引いた結果</returns>
		const T operator-(const T& rhs) const
		{
			return T(m_rawAmount - rhs.Raw(), m_min);
		}

		const T operator-(float rhs) const
		{
			return T(m_rawAmount - rhs, m_min);
		}

		/// <summary>
		/// 足した値を代入する
		/// </summary>
		/// <param name="rhs">足す値</param>
		/// <returns>thisの参照</returns>
		T& operator+=(const T& rhs)
		{
			Normalize(m_rawAmount += rhs.Raw());

			return *m_pInstatnce;
		}

		T& operator+=(float rhs)
		{
			Normalize(m_rawAmount += rhs);

			return *m_pInstatnce;
		}

		/// <summary>
		/// 引いた値を代入する
		/// </summary>
		/// <param name="rhs">引く値</param>
		/// <returns>thisの参照</returns>
		T& operator-=(const T& rhs)
		{
			Normalize(m_rawAmount -= rhs.Raw());

			return *this;
		}

		T& operator-=(float rhs)
		{
			Normalize(m_rawAmount -= rhs);

			return *m_pInstatnce;
		}

		/// <summary>
		/// 掛けた値を返す
		/// </summary>
		/// <param name="rhs">掛ける値</param>
		/// <returns>掛けた結果</returns>
		const T operator*(const T& rhs) const
		{
			return T(m_rawAmount * rhs.Raw(), m_min);
		}

		const T operator*(float rhs) const
		{
			return T(m_rawAmount * rhs, m_min);
		}

		/// <summary>
		/// 割った値を返す
		/// </summary>
		/// <param name="rhs">割る値</param>
		/// <returns>割った結果</returns>
		const T operator/(const T& rhs) const
		{
			return T(m_rawAmount / rhs.Raw(), m_min);
		}

		const T operator/(float rhs) const
		{
			return T(m_rawAmount / rhs, m_min);
		}

		/// <summary>
		/// 掛けた値を代入する
		/// </summary>
		/// <param name="rhs">掛ける値</param>
		/// <returns>thisの参照</returns>
		T& operator*=(const T& rhs)
		{
			Normalize(m_rawAmount *= rhs.Raw());

			return *m_pInstatnce;
		}

		T& operator*=(float rhs)
		{
			Normalize(m_rawAmount *= rhs);

			return *m_pInstatnce;
		}

		/// <summary>
		/// 割った値を代入する
		/// </summary>
		/// <param name="rhs">割る値</param>
		/// <returns>thisの参照</returns>
		T& operator/=(const T& rhs)
		{
			Normalize(m_rawAmount /= rhs.Raw());

			return *m_pInstatnce;
		}

		T& operator/=(float rhs)
		{
			Normalize(m_rawAmount /= rhs);

			return *m_pInstatnce;
		}

	protected:
		RotationValue(float amount, float min, float oneCycleAmount)
			:m_oneCycleAmount(oneCycleAmount), m_min(min), m_max(min + oneCycleAmount), m_rawAmount(amount)
		{
			m_pInstatnce = dynamic_cast<T*>(this);

			Normalize(amount);
		}

		virtual ~RotationValue() {};

		/// <summary>
		/// 最小値と最大値の間に角度を正規化する
		/// </summary>
		/// <param name="amount">整えたい角度</param>
		/// <param name="min">最小値</param>
		void Normalize(float amount)
		{
			//正規化する必要がなければreturn
			if (m_min <= amount && amount <= m_max)
			{
				m_normalizedAmount = amount;

				return;
			}

			/*
			円ではなく距離で考える
			|-1080|----------|-720|----------|-360|----------|0|----------|360|----------|720|----------|1080|
					  |A|              min~~~~~~~~~~~~~~~max(min + 360)

				 Aと近い範囲の端(min)との差を求め
				 その距離がn区分(360n)よりも離れているならばn+1区分(360(n + 1))ずらす
				 それによりminとmaxの間にAが移動する
			*/

			//範囲の端と値との距離の絶対値
			float distanceMinMaxRangeBetweenRotationAmount = static_cast<float>((amount > m_max) ? fabs(m_max - amount) : fabs(m_min - amount));
			//値が最大値のほうに近かったら? 最大値との距離の絶対値 : 最小値との距離の絶対値 / 円上で元の位置に戻ってくるために最低限必要な角度//

			//何周期分離れていたか
			int cycleNumMaxRangeBetweenRotationAmount = static_cast<int>(distanceMinMaxRangeBetweenRotationAmount / m_oneCycleAmount);

			//ずらすべき量
			float cycleAmountMaxRangeBetweenRotationAmount = m_oneCycleAmount * (cycleNumMaxRangeBetweenRotationAmount + 1);

			amount = amount + ((amount > m_max) ? -1.0f : +1.0f) * cycleAmountMaxRangeBetweenRotationAmount;

			m_normalizedAmount = amount;
		}

		float m_min = 0.0f;
		float m_max = 0.0f;

		float m_rawAmount = 0.0f;
		float m_normalizedAmount = 0.0f;

		float m_oneCycleAmount = 0.0f;

		T* m_pInstatnce = nullptr;
	};
}

#endif //!ROTATION_VALUE_H
