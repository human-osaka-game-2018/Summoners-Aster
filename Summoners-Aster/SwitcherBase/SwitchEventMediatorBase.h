#ifndef SWITCH_EVENT_MEDIATOR_BASE_H
#define SWITCH_EVENT_MEDIATOR_BASE_H

#include <tchar.h>
#include <vector>

#include <GameFramework.h>

namespace summonersaster
{
	using gameframework::Singleton;
	using gameframework::tstring;

	/// <summary>
	/// 段階切り替え情報
	/// </summary>
	struct SwitchEvent
	{
	public:
		tstring m_nextKind;

		/// <summary>
		/// 段階の初期化を行うべきかを判断する
		/// </summary>
		/// <remarks>
		/// 現在の段階を初期化する必要が出てきた時に対応するため
		/// </remarks>
		bool m_shouldSwitch = false;
	};

	/// <summary>
	/// 段階に関するイベント伝達の仲介クラス
	/// </summary>
	template<class T>
	class SwitchEventMediatorBase :public Singleton<SwitchEventMediatorBase<T>>
	{
	public:
		friend Singleton<SwitchEventMediatorBase<T>>;

		~SwitchEventMediatorBase()
		{

		}

		/// <summary>
		/// イベントの受取先の登録
		/// </summary>
		/// <param name="pSwitchEventPost">イベントを受け取るポインタ</param>
		void RegisterReceiver(SwitchEvent* pSwitchEventPost)
		{
			m_pSwitchEventPosts.push_back(pSwitchEventPost);
		}

		/// <summary>
		/// イベント受け取りの解除
		/// </summary>
		/// <param name="pSwitchEventPost">イベントを受け取っているポインタ</param>
		void UnregisterReceiver(SwitchEvent* pSwitchEventPost)
		{
			for (auto& pPost : m_pSwitchEventPosts)
			{
				int index = static_cast<int>(&pPost - &m_pSwitchEventPosts[0]);

				//ポインタが同じじゃなかったら
				if (pPost != pSwitchEventPost) continue;

				//要素を削除する
				m_pSwitchEventPosts.erase(m_pSwitchEventPosts.begin() + index);

				return;
			}
		}

		/// <summary>
		/// 登録されている受取先全てに段階切り替えイベントを送る
		/// </summary>
		/// <param name="nextKind">次からの段階</param>
		void SendSwitchEvent(const tstring& nextKind)
		{
			for (auto pPost : m_pSwitchEventPosts)
			{
				pPost->m_nextKind = nextKind;
				pPost->m_shouldSwitch = true;
			}
		}

	private:
		SwitchEventMediatorBase()
		{

		}

		std::vector<SwitchEvent*> m_pSwitchEventPosts;
	};
} // namespace summonersaster

#endif //!SWITCH_EVENT_MEDIATOR_BASE_H
