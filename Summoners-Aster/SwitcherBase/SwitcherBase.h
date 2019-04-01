#ifndef SWITCHER_BASE_H
#define SWITCHER_BASE_H

#include <tchar.h>
#include <unordered_map>

#include <GameFramework.h>

#include "SwitchEventMediatorBase.h"

namespace summonersaster
{
	using gameframework::Singleton;
	using gameframework::tstring;

	/// <summary>
	/// シーンなどを切り替えるクラスの基底
	/// </summary>
	template<class T>
	class SwitcherBase
	{
	public:
		virtual ~SwitcherBase()
		{
			ReleaseKindInstances();
		}

		/// <summary>
		/// 現在の段階の更新処理を行う
		/// </summary>
		/// <remarks>
		/// 段階を切り替える関数を呼ぶ
		/// </remarks>
		virtual void Update()
		{
			if (m_switchEventPost.m_shouldSwitch)
			{
				SwitchKind();
			}

			m_kinds[m_currentKind]->Update();
		}

		/// <summary>
		/// 現在の段階の描画処理を行う
		/// </summary>
		virtual void Render()
		{
			m_kinds[m_currentKind]->Render();
		}

	protected:
		SwitcherBase()
		{
			SwitchEventMediatorBase<T>& rSwitchEventMediatorBase = SwitchEventMediatorBase<T>::CreateAndGetRef();
			rSwitchEventMediatorBase.RegisterReceiver(&m_switchEventPost);
		}

		/// <summary>
		/// 段階を切り替える
		/// </summary>
		virtual void SwitchKind()
		{
			FinalizeCurrentKind();

			m_currentKind = m_switchEventPost.m_nextKind;
			InitializeCurrentKind();

			m_switchEventPost.m_shouldSwitch = false;
		}

		/// <summary>
		/// 現在の段階の初期化処理を行う
		/// </summary>
		virtual void InitializeCurrentKind()
		{
			m_kinds[m_currentKind]->Initialize();
		}

		/// <summary>
		/// 現在の段階の終了処理を行う
		/// </summary>
		virtual void FinalizeCurrentKind()
		{
			m_kinds[m_currentKind]->Finalize();
		}

		/// <summary>
		/// 全ての段階のインスタンスを生成する
		/// </summary>
		virtual void CreateKindInstances() = 0;

		/// <summary>
		/// 全ての段階のインスタンスを開放する
		/// </summary>
		virtual void ReleaseKindInstances()
		{
			for (auto& kind : m_kinds)
			{
				kind.second->Finalize();

				delete kind.second;
			}
		}

		tstring m_currentKind;

		SwitchEvent m_switchEventPost;

		std::unordered_map<tstring, T*> m_kinds;
	};
} // namespace summonersaster

#endif //!SWITCHER_BASE_H
