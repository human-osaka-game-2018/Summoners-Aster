#ifndef DIRECT_X_PARAM_H
#define DIRECT_X_PARAM_H

#include <Windows.h>

#include "DirectXDevice.h" 
#include "DirectXGraphicDevice.h"
#include "DirectXInputDevice.h"
#include "../../Window/WindowParam.h"
#include "../DirectXParam/DirectXParamFactory.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// DirectXのデバイスをまとめたstaticクラス
	/// </summary>
	class DirectXParam
	{
	public:		
		/// <remarks>
		/// Windowを作成した後に呼ぶ必要がある
		/// </remarks>
		static inline void Create()
		{
			HINSTANCE hInstance = GetModuleHandle(nullptr);
			WindowParam::SetInstanceHandle(hInstance);

			DirectXParamFactory::Create(&m_pDirectXDevice);
			DirectXParamFactory::Create(&m_pDirectXGraphicDevice, m_pDirectXDevice);
			DirectXParamFactory::Create(&m_pDirectXInputDevice);
		}

		static inline void Release()
		{
			delete m_pDirectXInputDevice;
			m_pDirectXInputDevice = nullptr;

			delete m_pDirectXGraphicDevice;
			m_pDirectXGraphicDevice = nullptr;

			delete m_pDirectXDevice;
			m_pDirectXDevice = nullptr;
		}

		static inline DirectXDevice* GetDirectXDevice()
		{
			return m_pDirectXDevice;
		}

		static inline DirectXGraphicDevice* GetDirectXGraphicDevice()
		{
			return m_pDirectXGraphicDevice;
		}

		static inline DirectXInputDevice* GetDirectXInputDevice()
		{
			return m_pDirectXInputDevice;
		}

	private:
		DirectXParam() {};
		DirectXParam(const DirectXParam& rhs) = delete;

		~DirectXParam() 
		{
			Release();
		};

		DirectXParam& operator=(const DirectXParam& rhs) = delete;

		static DirectXDevice* m_pDirectXDevice;
		static DirectXGraphicDevice* m_pDirectXGraphicDevice;
		static DirectXInputDevice* m_pDirectXInputDevice;
	};
}

#endif //!DIRECT_X_PARAM_H
