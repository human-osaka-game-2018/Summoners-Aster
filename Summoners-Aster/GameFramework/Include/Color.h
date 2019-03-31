#ifndef COLOR_H
#define COLOR_H

#include <Windows.h>
#include <vector>

#include <d3dx9.h>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 色保存するための構造体
	/// </summary>
	struct Color
	{
	public:
		/// <summary>
		/// 色の構成要素
		/// </summary>
		enum class COMPONENT
		{
			ALPHA,
			RED,
			GREEN,
			BLUE,
		};

		/// <remarks>
		/// 初期値は非透明の白0xFFFFFFFF
		/// </remarks>
		Color() {};
		Color(DWORD colorCode)
		{
			(*this) = colorCode;
		}

		Color(BYTE alpha, BYTE red, BYTE green, BYTE blue)
			:m_alpha(alpha), m_red(red), m_green(green), m_blue(blue)
		{};

		inline DWORD GetColorCode() const
		{
			return D3DCOLOR_ARGB(m_alpha, m_red, m_green, m_blue);
		}

		/// <summary>
		/// thisと引数との平均のカラーコードを取得する
		/// </summary>
		/// <param name="colorCode">平均をとるカラーコード</param>
		/// <returns>平均のカラーコード</returns>
		inline DWORD GetAverageColorCode(DWORD colorCode) const
		{
			Color inColor(colorCode);

			return GetAverage(inColor).GetColorCode();
		}

		/// <summary>
		/// thisと引数との平均のカラー構造体を返す
		/// </summary>
		/// <param name="color">平均をとるカラー構造体</param>
		/// <returns>平均のカラー</returns>
		inline Color GetAverage(const Color& color) const
		{
			Color average(
				(m_alpha + color.m_alpha) / 2,
				(m_red + color.m_red) / 2,
				(m_green + color.m_green) / 2,
				(m_blue + color.m_blue) / 2);

			return average;
		}

		BYTE m_alpha = 255;
		BYTE m_red = 255;
		BYTE m_green = 255;
		BYTE m_blue = 255;

		/// <summary>
		/// 添え字でアクセスできる色を変える
		/// </summary>
		/// <param name="colorComponent">アクセスする色のCOMPONENT</param>
		/// <returns>アクセスした色の参照</returns>>
		BYTE& operator[](COMPONENT colorComponent)
		{
			switch (colorComponent)
			{
			case COMPONENT::ALPHA:
				return m_alpha;

			case COMPONENT::RED:
				return m_red;

			case COMPONENT::GREEN:
				return m_green;

			case COMPONENT::BLUE:
				return m_blue;

			default:
			{
				//ここに来ることは基本ない
				static BYTE errorReturnVal = 0x00;
				return errorReturnVal;
			}
			}
		}

		/// <summary>
		/// カラーコードを分解し保存する
		/// </summary>
		/// <param name="colorCode">代入するカラーコード</param>
		/// <returns>thisの参照</returns>
		/// <remarks>
		/// <para>colorCodeの下位バイトからB→G→R→Aの順に1バイトずつ抜き出し、</para>
		/// <para>それぞれ対応するメンバに保存する</para>
		/// </remarks>
		Color& operator=(DWORD colorCode)
		{
			const std::vector<COMPONENT> components =
			{
				COMPONENT::BLUE,
				COMPONENT::GREEN,
				COMPONENT::RED,
				COMPONENT::ALPHA
			};

			for (auto& component : components) {
				int index = static_cast<int>(&component - &components[0]);
				int shiftNum = CHAR_BIT * index;
				(*this)[component] = (colorCode >> shiftNum) & 0xFF;
			}

			return *this;
		}

		/// <summary>
		/// 引数の色と自身の色を足しその値を返す
		/// </summary>
		/// <param name="rhs">自身と足すColor構造体</param>
		/// <returns>足した結果のColor構造体</returns>
		const Color operator+(const Color& rhs) const
		{
			return Color(
				Normalize(m_alpha + rhs.m_alpha),
				Normalize(m_red + rhs.m_red),
				Normalize(m_green + rhs.m_green),
				Normalize(m_blue + rhs.m_blue)
			);
		}

		const Color operator+(DWORD rhs) const
		{
			return Color((*this) + Color(rhs));
		}

		/// <summary>
		/// 引数の色と自身の色を引きその値を返す
		/// </summary>
		/// <param name="rhs">自身と引くColor構造体</param>
		/// <returns>引いた結果のColor構造体</returns>
		const Color operator-(const Color& rhs) const
		{
			return Color(
				Normalize(m_alpha - rhs.m_alpha),
				Normalize(m_red - rhs.m_red),
				Normalize(m_green - rhs.m_green),
				Normalize(m_blue - rhs.m_blue)
			);
		}

		const Color operator-(DWORD rhs) const
		{
			return Color((*this) - Color(rhs));
		}

		/// <summary>
		/// 引数の色と自身の色を足しその値を代入する
		/// </summary>
		/// <param name="rhs">自身と足すColor構造体</param>
		/// <returns>thisの参照</returns>
		const Color operator+=(const Color& rhs)
		{
			(*this) = (*this) + rhs;

			return *this;
		}

		const Color operator+=(DWORD rhs)
		{
			(*this) = (*this) + rhs;

			return *this;
		}

		/// <summary>
		/// 引数の色と自身の色を引きその値を代入する
		/// </summary>
		/// <param name="rhs">自身と引くColor構造体</param>
		/// <returns>thisの参照</returns>
		const Color operator-=(const Color& rhs)
		{
			(*this) = (*this) - rhs;

			return *this;
		}

		const Color operator-=(DWORD rhs)
		{
			(*this) = (*this) - rhs;

			return *this;
		}

		/// <summary>
		/// 引数の値でメンバを掛ける
		/// </summary>
		/// <param name="rhs">掛ける際の値</param>
		/// <returns>掛けた後の結果のColor構造体</returns>
		const Color operator*(float rhs) const
		{
			return Color(
				Normalize(m_alpha * rhs),
				Normalize(m_red   * rhs),
				Normalize(m_green * rhs),
				Normalize(m_blue  * rhs)
			);
		}

		/// <summary>
		/// 引数の値でメンバを掛けその値を代入する
		/// </summary>
		/// <param name="rhs">掛ける際の値</param>
		/// <returns>thisの参照</returns>
		Color& operator*=(float rhs)
		{
			(*this) = (*this) * rhs;

			return *this;
		}

		/// <summary>
		/// 引数の値でメンバを割る
		/// </summary>
		/// <param name="rhs">割る際の値</param>
		/// <returns>割った後の結果のColor構造体</returns>
		const Color operator/(int rhs) const
		{
			return Color(
				Normalize(m_alpha / rhs),
				Normalize(m_red / rhs),
				Normalize(m_green / rhs),
				Normalize(m_blue / rhs)
			);
		}

		/// <summary>
		/// 引数の値でメンバを割りその値を代入する
		/// </summary>
		/// <param name="rhs">割る際の値</param>
		/// <returns>thisの参照</returns>
		Color& operator/=(int rhs)
		{
			(*this) = (*this) / rhs;

			return *this;
		}

	private:
		/// <summary>
		/// 各色(int)の値を0x00～0xFFに正規化する
		/// </summary>
		/// <param name="componentValue">各色の値</param>
		/// <returns>
		/// <para>・cmponentValue ＜ 0x00の場合は0x00を返す</para>
		/// <para>・0x00 ≦ componentValue ≦ 0xFFの場合はcomponentValueをそのまま返す</para>
		/// <para>・0xFF ＜ componentValue 場合は0xFFを返す</para>
		/// </returns>
		inline BYTE Normalize(int componentValue) const
		{
			return static_cast<BYTE>(max(min(componentValue, 255), 0));
		}

		/// <summary>
		/// 各色(float)の値を0x00～0xFFに正規化する
		/// </summary>
		/// <param name="componentValue">各色の値</param>
		/// <returns>
		/// <para>・cmponentValue ＜ 0x00の場合は0x00を返す</para>
		/// <para>・0x00 ≦ componentValue ≦ 0xFFの場合はcomponentValueをそのまま返す</para>
		/// <para>・0xFF ＜ componentValue 場合は0xFFを返す</para>
		/// </returns>
		inline BYTE Normalize(float componentValue) const
		{
			return Normalize(static_cast<int>(componentValue));
		}
	};
}

#endif //! COLOR_H
