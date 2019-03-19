#ifndef DIRECT_X_PARAM_FACTORY_H
#define DIRECT_X_PARAM_FACTORY_H

#include "DirectXDevice.h"
#include "DirectX9Device.h"
#include "DirectXGraphicDevice.h"
#include "DirectX9GraphicDevice.h"
#include "DirectXInputDevice.h"
#include "DirectX8InputDevice.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{	
	/// <summary>
	/// DirectXParam関連のファクトリ
	/// </summary>
	class DirectXParamFactory
	{
	public:
		template<typename T>
		static void Create(T** ppT)
		{
			*ppT = new T();
		}

		template<>
		static void Create<DirectXDevice>(DirectXDevice** ppDirectXDevice)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppDirectXDevice = nullptr;
			#elif defined DIRECT_X_VERSOIN_9
			*ppDirectXDevice = new DirectX9Device();
			#else
			#error "DirectXのバージョンを定義してください"
			#endif
		}

		static void Create(DirectXGraphicDevice** ppDirectXGraphicDevice, DirectXDevice* pDirectXDevice)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppDirectXGraphicDevice = nullptr;
			#elif defined DIRECT_X_VERSOIN_9
			*ppDirectXGraphicDevice = new DirectX9GraphicDevice(pDirectXDevice);
			#else
			#error "DirectXのバージョンを定義してください"
			#endif
		}

		template<>
		static void Create<DirectXInputDevice>(DirectXInputDevice** ppDirectXInputDevice)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppDirectXInputDevice = nullptr;
			#elif defined DIRECT_X_VERSOIN_9
			*ppDirectXInputDevice = new DirectX8InputDevice();
			#else
			#error "DirectXのバージョンを定義してください"
			#endif
		}

	private:
		DirectXParamFactory() {};
		DirectXParamFactory(const DirectXParamFactory& rhs) = delete;

		~DirectXParamFactory() {};

		DirectXParamFactory& operator=(const DirectXParamFactory& rhs) = delete;
	};
}

#endif //!DIRECT_X_PARAM_FACTORY_H
