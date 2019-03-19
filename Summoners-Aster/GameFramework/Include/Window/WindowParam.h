#ifndef WINDOW_PARAM_H
#define WINDOW_PARAM_H

#include <Windows.h>

#include "../RectSize.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// ウィンドウ作成時に必要な情報をまとめたstaticクラス
	/// </summary>
	class WindowParam
	{
	public:
		static inline void GetWindowSize(RectSize* pWindowSize)
		{
			*pWindowSize = m_windowSize;
		}

		static inline void SetWindowSize(const RectSize& windowSize)
		{
			m_windowSize = windowSize;
		}

		static inline void GetInstanceHandle(HINSTANCE* pHInstance)
		{
			*pHInstance = m_hInstance;
		}

		static inline void SetInstanceHandle(const HINSTANCE& hInstance)
		{
			m_hInstance = hInstance;
		}

		static inline void GetWindowHandle(HWND* pHWnd)
		{
			*pHWnd = m_hWnd;
		}

		static inline void SetWindowHandle(const HWND& hWnd)
		{
			m_hWnd = hWnd;
		}

	private:
		WindowParam() {};
		WindowParam(const WindowParam& rhs) = delete;

		~WindowParam() {};

		WindowParam& operator=(const WindowParam& rhs) = delete;

		/// <summary>
		/// ウィンドウのサイズ
		/// </summary>
		static RectSize m_windowSize;

		static HINSTANCE m_hInstance;

		static HWND m_hWnd;
	};
}

#endif //!WINDOW_PARAM_H
