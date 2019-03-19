#ifndef DIRECT_INPUT_H
#define DIRECT_INPUT_H

#include <Windows.h>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// DirectInputクラスの基底クラス
	/// </summary>
	class DirectInput
	{
	public:
		virtual ~DirectInput() {};

		/// <summary>
		/// 描画の準備を行う
		/// </summary>
		virtual void PrepareInFrame() = 0;

		/// <summary>
		/// 描画の終了処理を行う
		/// </summary>
		virtual void FinishInFrame() = 0;

		/// <summary>
		/// 引数に渡したボタンが押された瞬間か
		/// </summary>
		/// <param name="key">ボタンの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		virtual bool MouseIsPressed(int key) const = 0;

		virtual bool MouseIsHeld(int key) const = 0;

		virtual bool MouseIsReleased(int key) const = 0;

		virtual bool MouseIsNeutral(int key) const = 0;

		/// <summary>
		/// 何かのボタンが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		virtual bool MouseAnyKeyIsPressed() const = 0;

		/// <summary>
		/// カーソルの位置の取得
		/// </summary>
		/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
		virtual void CursorPos(POINT* pPos) const = 0;

		/// <summary>
		/// 前フレームからどのくらいスクロールされたか
		/// </summary>
		/// <returns>スクロールされた量</returns>
		virtual long MouseWheelScrolling() const = 0;

		/// <summary>
		/// 引数に渡したキーが押された瞬間か
		/// </summary>
		/// <param name="key">キーの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		virtual bool KeyboardIsPressed(int key) const = 0;

		virtual bool KeyboardIsHeld(int key) const = 0;

		virtual bool KeyboardIsReleased(int key) const = 0;

		virtual bool KeyboardIsNeutral(int key) const = 0;

		/// <summary>
		/// 何かのキーが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		virtual bool KeyboardAnyKeyIsPressed() const = 0;

	protected:
		DirectInput() {};

	private:
		DirectInput(const DirectInput& rhs) = delete;

		DirectInput& operator=(const DirectInput& rhs) = delete;
	};
}

#endif //!DIRECT_INPUT_H
