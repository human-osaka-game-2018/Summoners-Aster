#ifndef DIRECT_X_8_INPUT_DEVICE_H
#define DIRECT_X_8_INPUT_DEVICE_H

#include <Windows.h>
#include <tchar.h>

#include <dinput.h>

#include "../../Window/WindowParam.h"
#include "DirectXInputDevice.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	/// <summary>
	/// DirectX8のインプットデバイスクラス
	/// </summary>
	class DirectX8InputDevice :public DirectXInputDevice
	{
	public:
		DirectX8InputDevice() 
		{
			Create();
		}

		~DirectX8InputDevice()
		{
			m_pDirectXInputDevice->Release();
			delete m_pDirectXInputDevice;
		}

	private:
		DirectX8InputDevice(const DirectX8InputDevice& rhs) = delete;

		DirectX8InputDevice& operator=(const DirectX8InputDevice& rhs) = delete;

		/// <summary>
		/// DirectX8のインプットデバイスを作成する
		/// </summary>
		void Create();
	};

	#endif //DIRECT_X_VERSOIN_9
}

#endif //!DIRECT_X_8_INPUT_DEVICE_H
