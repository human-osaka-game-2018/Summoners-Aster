#ifndef DIRECT_X_8_MOUSE_H
#define DIRECT_X_8_MOUSE_H

#include <Windows.h>

#include <dinput.h>

#include "Direct8InputDevice.h"
#include "../DirectXParam/DirectXParam.h"
#include "../../Window/WindowParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// DirectX8のマウス
	/// </summary>
	/// <seealso cref="DirectX8InputDevice" />
	class DirectX8Mouse :public Direct8InputDevice
	{
	public:
		enum DIM
		{
			DIM_LEFT,
			DIM_RIGHT,
			DIM_SUB_1,
			DIM_SUB_2,
			DIM_MAX
		};

		DirectX8Mouse()
		{
			Create();
		}

		virtual ~DirectX8Mouse() {};

		/// <summary>
		/// 入力状態の保存,メインループの終わりで用いる
		/// </summary>
		/// <returns></returns>
		inline void FinishInFrame()
		{
			memcpy(&m_prevState, &m_state, sizeof(DIMOUSESTATE));
		}

		/// <summary>
		/// 引数に渡したボタンが押された瞬間か
		/// </summary>
		/// <param name="key">ボタンの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool IsPressed(int key) const
		{
			return (m_details[key] == IND_PRESS);
		}

		inline bool IsHeld(int key) const
		{
			return (m_details[key] == IND_HOLD);
		}

		inline bool IsReleased(int key) const
		{
			return (m_details[key] == IND_RELEASE);
		}

		inline bool IsNeutral(int key) const
		{
			return (m_details[key] == IND_NEUTRAL);
		}

		/// <summary>
		/// 何かのボタンが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool AnyKeyIsPressed() const
		{
			for (int i = 0; i < DIM_MAX; ++i)
			{
				if (IsPressed(i)) return true;
			}

			return false;
		}

		/// <summary>
		/// カーソルの位置の取得
		/// </summary>
		/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
		inline void CursorPos(POINT* pPos) const
		{
			*pPos = m_cursorRelativePos;
		}

		/// <summary>
		/// 前フレームからどのくらいスクロールされたか
		/// </summary>
		/// <returns>スクロールされた量</returns>
		inline long WheelScrolling() const
		{
			return m_state.lZ;
		}

	private:
		DirectX8Mouse(const DirectX8Mouse& rhs) = delete;

		DirectX8Mouse& operator=(const DirectX8Mouse& rhs) = delete;

		void Create();

		void AcquireInputState();

		/// <summary>
		/// AcquireInputState()を読んだ後に用いる
		/// 入力状態の振り分けを行う
		/// </summary>
		void CheckInputStateDetatils();

		DIMOUSESTATE m_state;
		DIMOUSESTATE m_prevState;
		
		/// <summary>
		/// カーソルのウィンドウ基準の相対座標
		/// </summary>
		POINT m_cursorRelativePos;

		INPUT_DETAIL m_details[DIM_MAX];
	};
}

#endif //!DIRECT_X_8_MOUSE_H
