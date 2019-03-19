#ifndef DIRECT_X_9_DEVICE_H
#define DIRECT_X_9_DEVICE_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "DirectXDevice.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	/// <summary>
	/// DirectX9のデバイスクラス
	/// </summary>
	class DirectX9Device :public DirectXDevice
	{
	public:
		DirectX9Device()
		{
			Create();
		}

		~DirectX9Device() {};

	private:
		DirectX9Device(const DirectX9Device& rhs) = delete;

		DirectX9Device& operator=(const DirectX9Device& rhs) = delete;

		/// <summary>
		/// DirectX9のデバイスを作成する
		/// </summary>
		void Create();
	};

	#endif //DIRECT_X_VERSOIN_9
}

#endif //!DIRECT_X_9_DEVICE_H
