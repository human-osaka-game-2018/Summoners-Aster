#ifndef DIRECT_X_GRAPHIC_DEVICE_H
#define DIRECT_X_GRAPHIC_DEVICE_H

#include <Windows.h>

#include <d3dx9.h>

#include "DirectXDevice.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
#ifdef DIRECT_X_VERSION_11
	using LPDIRECT3DDEVICE = LPDIRECT3DDEVICE9;
#elif defined DIRECT_X_VERSOIN_9
	using LPDIRECT3DDEVICE = LPDIRECT3DDEVICE9;
#else
#error "DirectXのバージョンを定義してください"
#endif

	/// <summary>
	/// DirectXのグラフィックデバイスクラス
	/// </summary>
	class DirectXGraphicDevice
	{
	public:
		virtual ~DirectXGraphicDevice()
		{
			m_pDirectXGraphicDevice->Release();
			delete m_pDirectXGraphicDevice;
		}

		inline void Get(LPDIRECT3DDEVICE* ppDirectXDevice) const
		{
			*ppDirectXDevice = m_pDirectXGraphicDevice;
		}

	protected:
		DirectXGraphicDevice() {};

		/// <summary>
		/// DirectXのグラフィックデバイスを作成する
		/// </summary>
		/// <param name="pDirectXDevice">DirectXのデバイスクラスのポインタ</param>
		virtual void Create(DirectXDevice* pDirectXDevice) = 0;

		/// <summary>
		/// ビューポートを初期化する
		/// </summary>
		virtual void InitializeViewPort() = 0;

		LPDIRECT3DDEVICE m_pDirectXGraphicDevice = nullptr;

	private:
		DirectXGraphicDevice(const DirectXGraphicDevice& rhs) = delete;

		DirectXGraphicDevice& operator=(const DirectXGraphicDevice& rhs) = delete;
	};
}

#endif //!DIRECT_X_GRAPHIC_DEVICE_H
