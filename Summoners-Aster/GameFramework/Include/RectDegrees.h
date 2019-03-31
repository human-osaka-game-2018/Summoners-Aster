#ifndef RECT_DEGREES_H
#define RECT_DEGREES_H

#include "Degree.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	namespace collision
	{
		/// <summary>
		/// 当たり判定で扱う矩形に関する角度範囲は-180～180固定
		/// </summary>
		struct RectDegrees
		{
		public:
			Degree m_degrees[4];

			/// <summary>
			/// 引数が全部の角度に対して真なら真を返す
			/// </summary>
			bool operator==(const Degree& rhs)
			{
				for (auto& deg : m_degrees)
				{
					if (deg.Normalized() != rhs.Normalized()) return false;
				}

				return true;
			}

			bool operator>(const Degree& rhs)
			{
				for (auto& deg : m_degrees)
				{
					if (deg.Normalized() <= rhs.Normalized()) return false;
				}

				return true;
			}

			bool operator>=(const Degree& rhs)
			{
				for (auto& deg : m_degrees)
				{
					if (deg.Normalized() < rhs.Normalized()) return false;
				}

				return true;
			}

			bool operator<(const Degree& rhs)
			{
				for (auto& deg : m_degrees)
				{
					if (deg.Normalized() >= rhs.Normalized()) return false;
				}

				return true;
			}

			bool operator<=(const Degree& rhs)
			{
				for (auto& deg : m_degrees)
				{
					if (deg.Normalized() > rhs.Normalized()) return false;
				}

				return true;
			}
		};
	}
}

#endif //!RECT_DEGREES_H
