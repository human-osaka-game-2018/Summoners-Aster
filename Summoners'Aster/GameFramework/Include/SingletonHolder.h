#ifndef SINGLETON_HOLDER_H
#define SINGLETON_HOLDER_H

#include <memory>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// Singletonの自動開放クラス
	/// </summary>
	template <class T>
	class SingletonHolder
	{
	public:
		~SingletonHolder()
		{
			delete m_singletonPtr;
		}

		static inline void Create(T* pSingletonPtr)
		{
			if (m_pThis) return;

			m_pThis.reset(new SingletonHolder<T>(pSingletonPtr));
		}

		static inline void Unregister()
		{
			m_singletonPtr = nullptr;

			ReleaseHolder();
		}

	private:
		SingletonHolder(T* pSingletonPtr)
		{
			Register(pSingletonPtr);
		}

		void inline Register(T* pSingletonPtr)
		{
			m_singletonPtr = pSingletonPtr;
		}

		static void ReleaseHolder()
		{
			m_pThis.release();
		}

		static T* m_singletonPtr;

		static std::unique_ptr<SingletonHolder<T>> m_pThis;
	};

	template <class T>
	T* SingletonHolder<T>::m_singletonPtr = nullptr;

	template <class T>
	std::unique_ptr<SingletonHolder<T>> SingletonHolder<T>::m_pThis;
}

#endif //!SINGLETON_HOLDER_H
