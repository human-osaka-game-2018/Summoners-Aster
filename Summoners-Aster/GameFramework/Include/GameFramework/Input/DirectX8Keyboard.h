#ifndef DIRECT_X_8_KEYBOARD_H
#define DIRECT_X_8_KEYBOARD_H

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
	/// DirectX8のキーボード
	/// </summary>
	/// <seealso cref="DirectX8InputDevice" />
	class DirectX8Keyboard :public Direct8InputDevice
	{
	public:
		DirectX8Keyboard()
		{
			Create();
		}

		virtual ~DirectX8Keyboard() {};

		/// <summary>
		/// 入力状態の保存,メインループの終わりで用いる
		/// </summary>
		/// <returns></returns>
		inline void FinishInFrame()
		{
			memcpy(m_prevDiks, m_diks, sizeof(BYTE) * 256);
		}

		/// <summary>
		/// 引数に渡したキーが押された瞬間か
		/// </summary>
		/// <param name="key">キーの列挙体</param>
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
		/// 何かのキーが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool AnyKeyIsPressed() const
		{
			for (int i = 0; i < KEY_MAX; ++i)
			{
				if (IsPressed(i)) return true;
			}

			return false;
		}

		static const int KEY_MAX = 256;

	private:
		DirectX8Keyboard(const DirectX8Keyboard& rhs) = delete;

		DirectX8Keyboard& operator=(const DirectX8Keyboard& rhs) = delete;

		void Create();

		inline void AcquireInputState()
		{
			//キーボードの状態を取得する権限の取得
			m_pInputDevice->Acquire();

			//キーボードの状態を取得
			m_pInputDevice->GetDeviceState(
				sizeof(BYTE) * KEY_MAX,
				m_diks);
		}

		/// <summary>
		/// AcquireInputState()を読んだ後に用いる
		/// 入力状態の振り分けを行う
		/// </summary>
		void CheckInputStateDetatils();

		/// <summary>
		/// 現在ののフレームでキーが押されていた場合上位ビットが立つ
		/// </summary>
		BYTE m_diks[KEY_MAX];

		/// <summary>
		/// 前回のフレームでキーが押されていた場合上位ビットが立つ
		/// </summary>
		BYTE m_prevDiks[KEY_MAX];

		INPUT_DETAIL m_details[KEY_MAX];
	};
}

#endif //!DIRECT_X_8_KEYBOARD_H
