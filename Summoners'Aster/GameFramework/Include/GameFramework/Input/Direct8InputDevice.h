#ifndef DIRECT_8_INPUT_DEVICE_H
#define DIRECT_8_INPUT_DEVICE_H

#include <Windows.h>

#include <dinput.h>

#include "InputDevice.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// DirectX8の入力デバイスの基底クラス
	/// </summary>
	/// <seealso cref="InputDevice" />
	class Direct8InputDevice :public InputDevice
	{
	public:
		virtual ~Direct8InputDevice() {};

	protected:
		Direct8InputDevice() {};

		inline bool IsInputted(int key) const
		{
			return ((key & 0x80) != 0);
		}

		LPDIRECTINPUTDEVICE8 m_pInputDevice = nullptr;

	private:
		Direct8InputDevice(const Direct8InputDevice& rhs) = delete;

		Direct8InputDevice& operator=(const Direct8InputDevice& rhs) = delete;
	};
}

#endif //!DIRECT_8_INPUT_DEVICE_H
