#ifndef INPUT_H
#define INPUT_H

#include "DirectInput.h"
#include "../GameFrameworkFactory.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 入力関係の統括クラス
	/// </summary>
	class Input
	{
	public:
		Input()
		{
			GameFrameworkFactory::Create(&m_pDirectInput);
		}

		~Input()
		{
			delete m_pDirectInput;
		}

		/// <summary>
		/// マウスとキーボードの入力状態の更新を行う,メッセージループの始まりで呼ぶ
		/// </summary>
		inline void PrepareInFrame()
		{
			m_pDirectInput->PrepareInFrame();
		}

		/// <summary>
		/// マウスとキーボードの入力状態の保存を行う,メッセージループの終わりで呼ぶ
		/// </summary>
		inline void FinishInFrame()
		{
			m_pDirectInput->PrepareInFrame();
		}

		/// <summary>
		/// 引数に渡したボタンが押された瞬間か
		/// </summary>
		/// <param name="key">ボタンの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool MouseIsPressed(int key) const
		{
			return m_pDirectInput->MouseIsPressed(key);
		}

		inline bool MouseIsHeld(int key) const
		{
			return m_pDirectInput->MouseIsHeld(key);
		}

		inline bool MouseIsReleased(int key) const
		{
			return m_pDirectInput->MouseIsReleased(key);
		}

		inline bool MouseIsNeutral(int key) const
		{
			return m_pDirectInput->MouseIsNeutral(key);
		}

		/// <summary>
		/// 何かのボタンが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool MouseAnyKeyIsPressed() const
		{
			return m_pDirectInput->MouseAnyKeyIsPressed();
		}

		/// <summary>
		/// カーソルの位置の取得
		/// </summary>
		/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
		inline void CursorPos(POINT* pPos) const
		{
			m_pDirectInput->CursorPos(pPos);
		}

		/// <summary>
		/// 前フレームからどのくらいスクロールされたか
		/// </summary>
		/// <returns>スクロールされた量</returns>
		inline long MouseWheelScrolling() const
		{
			return m_pDirectInput->MouseWheelScrolling();
		}

		/// <summary>
		/// 引数に渡したキーが押された瞬間か
		/// </summary>
		/// <param name="key">キーの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool KeyboardIsPressed(int key) const
		{
			return m_pDirectInput->KeyboardIsPressed(key);
		}

		inline bool KeyboardIsHeld(int key) const
		{
			return m_pDirectInput->KeyboardIsHeld(key);
		}

		inline bool KeyboardIsReleased(int key) const
		{
			return m_pDirectInput->KeyboardIsReleased(key);
		}

		inline bool KeyboardIsNeutral(int key) const
		{
			return m_pDirectInput->KeyboardIsNeutral(key);
		}

		/// <summary>
		/// 何かのキーが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool KeyboardAnyKeyIsPressed() const
		{
			return m_pDirectInput->KeyboardAnyKeyIsPressed();
		}

	private:
		Input(const Input& rhs) = delete;

		Input& operator=(const Input& rhs) = delete;

		DirectInput* m_pDirectInput = nullptr;
	};
}

#endif //!INPUT_H
