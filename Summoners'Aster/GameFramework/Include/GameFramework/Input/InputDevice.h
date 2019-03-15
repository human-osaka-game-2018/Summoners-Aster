#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include <Windows.h>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/**
	* @brief 入力デバイスの基底クラス
	*/
	class InputDevice
	{
	public:
		virtual ~InputDevice() {};

		/// <summary>
		/// 入力状態の保存,メインループの終わりで用いる
		/// </summary>
		/// <returns></returns>
		virtual void PrepareInFrame()
		{
			AcquireInputState();
			CheckInputStateDetatils();
		}

		/// <summary>
		/// 引数に渡したボタンが押された瞬間か
		/// </summary>
		/// <param name="key">ボタンの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		virtual void FinishInFrame() = 0;

		/// <summary>
		/// 引数に渡したボタンが押された瞬間か
		/// </summary>
		/// <param name="key">ボタンの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		virtual bool IsPressed(int key) const = 0;
		virtual bool IsHeld(int key) const = 0;
		virtual bool IsReleased(int key) const = 0;
		virtual bool IsNeutral(int key) const = 0;

		/// <summary>
		/// 何かのキーが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		virtual bool AnyKeyIsPressed() const = 0;

	protected:
		enum INPUT_DETAIL
		{
			//押された瞬間のフレームだけtrue
			IND_PRESS,

			//押され続けられている間true
			IND_HOLD,

			//離された瞬間のフレームだけtrue
			IND_RELEASE,

			//前回と現在のフレームで押されていない間true
			IND_NEUTRAL,
			IND_MAX
		};

		InputDevice() {};

		virtual void AcquireInputState() {};
		virtual void CheckInputStateDetatils() {};
		virtual void Create() = 0;

	private:
		InputDevice(const InputDevice& rhs) = delete;

		InputDevice& operator=(const InputDevice& rhs) = delete;
	};
}

#endif //!INPUT_DEVICE_H
