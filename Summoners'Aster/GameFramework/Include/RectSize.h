#ifndef RECT_SIZE_H
#define RECT_SIZE_H

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 四角形の長さを保存するための構造体
	/// </summary>
	struct RectSize
	{
	public:
		RectSize() {};

		RectSize(float width, float height)
		{
			m_width = width;
			m_height = height;
		}

		/// <summary>
		/// 引数のRECT構造体から矩形のサイズを作成する
		/// </summary>
		/// <param name="rect">作成するときに扱うRECT構造体</param>
		RectSize(const RECT& rect)
		{
			*this = rect;
		}

		/// <summary>
		/// x成分の長さ
		/// </summary>
		float m_width = 0.0f;

		/// <summary>
		/// y成分の長さ
		/// </summary>
		float m_height = 0.0f;

		/// <summary>
		/// RECT構造体から矩形のサイズを作成する
		/// </summary>
		/// <param name="rhs">作成するときに扱うRECT構造体</param>
		/// <returns>自身の参照</returns>
		RectSize& operator=(const RECT& rhs)
		{
			m_width = static_cast<float>(rhs.right - rhs.left);
			m_height = static_cast<float>(rhs.bottom - rhs.top);

			return *this;
		}

		/// <summary>
		/// 引数のサイズと自身のサイズを足しその値を返す
		/// </summary>
		/// <param name="rhs">自身と足すRectSize構造体</param>
		/// <returns>足した結果のRectSize構造体</returns>
		const RectSize operator+(const RectSize& rhs) const
		{
			return RectSize(m_width + rhs.m_width, m_height + rhs.m_height);
		}

		/// <summary>
		/// 引数のサイズと自身のサイズを引きその値を返す
		/// </summary>
		/// <param name="rhs">自身と引くRectSize構造体</param>
		/// <returns>引いた結果のRectSize構造体</returns>
		const RectSize operator-(const RectSize& rhs) const
		{
			return RectSize(m_width - rhs.m_width, m_height - rhs.m_height);
		}

		/// <summary>
		/// 引数の値でメンバを割る
		/// </summary>
		/// <param name="rhs">割る際の値</param>
		/// <returns>割った後の結果のRectSize構造体</returns>
		const RectSize operator/(float rhs) const
		{
			return RectSize(m_width / rhs, m_height / rhs);
		}

		/// <summary>
		/// 引数の値でメンバを掛ける
		/// </summary>
		/// <param name="rhs">掛ける際の値</param>
		/// <returns>掛けた後の結果のRectSize構造体</returns>
		const RectSize operator*(float rhs) const
		{
			return RectSize(m_width * rhs, m_height * rhs);
		}
	};
}

#endif //!RECT_SIZE_H
