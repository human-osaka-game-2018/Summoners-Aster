#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

#include "SingletonHolder.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// Singleton基底クラス
	/// </summary>
	template <class T>
	class Singleton
	{
	public:
		enum CREATE_RESULT
		{
			CR_COULD_NOT_CREATE,
			CR_OK,
			CR_ALREADY_CREATED,
		};

		virtual ~Singleton() {};

		inline static CREATE_RESULT CreateInstance()
		{
			if (m_ptr) return CR_ALREADY_CREATED;

			m_ptr = new T();

			SingletonHolder<T>::Create(m_ptr);

			if (m_ptr) return CR_OK;

			return CR_COULD_NOT_CREATE;
		}

		inline static void ReleaseInstance()
		{
			delete m_ptr;
			m_ptr = nullptr;

			SingletonHolder<T>::Unregister();
		}

		inline static T& GetRef()
		{
			return *m_ptr;
		}

		inline static T* GetPtr()
		{
			return m_ptr;
		}

		inline static T& CreateAndGetRef()
		{
			CreateInstance();

			return GetRef();
		}

		inline static T* CreateAndGetPtr()
		{
			CreateInstance();

			return GetPtr();
		}

	protected:
		Singleton() {};

		static T* m_ptr;
	};

	template <class T>
	T* Singleton<T>::m_ptr = nullptr;
}

#endif //!SINGLETON_H
