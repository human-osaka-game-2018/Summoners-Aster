#ifndef DIRECT_8_INPUT_H
#define DIRECT_8_INPUT_H

#include "DirectInput.h"
#include "DirectX8Keyboard.h"
#include "DirectX8Mouse.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
#ifdef DIRECT_X_VERSOIN_9

	/// <summary>
	/// Direct8Inputクラスの
	/// </summary>
	class Direct8Input :public DirectInput
	{
	public:
		Direct8Input() {};

		virtual ~Direct8Input() {};

		/// <summary>
		/// マウスとキーボードの入力状態の更新を行う,メッセージループの始まりで呼ぶ
		/// </summary>
		inline void PrepareInFrame()
		{
			m_mouse.PrepareInFrame();
			m_keyboard.PrepareInFrame();
		}

		/// <summary>
		/// マウスとキーボードの入力状態の保存を行う,メッセージループの終わりで呼ぶ
		/// </summary>
		inline void FinishInFrame()
		{
			m_mouse.FinishInFrame();
			m_keyboard.FinishInFrame();
		}

		/// <summary>
		/// 引数に渡したボタンが押された瞬間か
		/// </summary>
		/// <param name="key">ボタンの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool MouseIsPressed(int key) const
		{
			return m_mouse.IsPressed(key);
		}

		inline bool MouseIsHeld(int key) const
		{
			return m_mouse.IsHeld(key);
		}

		inline bool MouseIsReleased(int key) const
		{
			return m_mouse.IsReleased(key);
		}

		inline bool MouseIsNeutral(int key) const
		{
			return m_mouse.IsNeutral(key);
		}

		/// <summary>
		/// 何かのボタンが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool MouseAnyKeyIsPressed() const
		{
			return m_mouse.AnyKeyIsPressed();
		}

		/// <summary>
		/// カーソルの位置の取得
		/// </summary>
		/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
		inline void CursorPos(POINT* pPos) const
		{
			m_mouse.CursorPos(pPos);
		}

		/// <summary>
		/// 前フレームからどのくらいスクロールされたか
		/// </summary>
		/// <returns>スクロールされた量</returns>
		inline long MouseWheelScrolling() const
		{
			return m_mouse.WheelScrolling();
		}

		/// <summary>
		/// 引数に渡したキーが押された瞬間か
		/// </summary>
		/// <param name="key">キーの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool KeyboardIsPressed(int key) const
		{
			return m_keyboard.IsPressed(key);
		}

		inline bool KeyboardIsHeld(int key) const
		{
			return m_keyboard.IsHeld(key);
		}

		inline bool KeyboardIsReleased(int key) const
		{
			return m_keyboard.IsReleased(key);
		}

		inline bool KeyboardIsNeutral(int key) const
		{
			return m_keyboard.IsNeutral(key);
		}

		/// <summary>
		/// 何かのキーが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool KeyboardAnyKeyIsPressed() const
		{
			return m_keyboard.AnyKeyIsPressed();
		}

	private:
		Direct8Input(const Direct8Input& rhs) = delete;

		Direct8Input& operator=(const Direct8Input& rhs) = delete;

		DirectX8Mouse m_mouse;
		DirectX8Keyboard m_keyboard;
	};

#endif //DIRECT_X_VERSOIN_9
}

#endif //!DIRECT_8_INPUT_H
