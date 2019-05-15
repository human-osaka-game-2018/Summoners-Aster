#ifndef PLAYERS_H
#define PLAYERS_H

#include <tchar.h>
#include <unordered_map>

#include <GameFramework.h>

#include "BattlePlayer.h"
#include "OpponentPlayer.h"
#include "BattleEnums.h"
#include "BattleInformation.h"

namespace summonersaster
{
	using gameframework::tstring;

	using gameframework::Singleton;

	/// <summary>
	/// Playerのファーストクラスコレクション
	/// </summary>
	class Players :public Singleton<Players>
	{
	public:
		friend Singleton<Players>;

		Players();
		~Players();

		void Initialize();

		void Finalize();

		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="phaseName">現フェイズの名前</param>
		/// <returns>更新処理が終了したらtrue</returns>
		virtual bool Update(const tstring& phaseName);

		virtual void Render();

		/// <summary>
		/// メインフェイズの始まりで行う初期化
		/// </summary>
		virtual void InitializeInMainPhaseStart();

		static inline BattlePlayer* GetPlayer(PLAYER_KIND kind) 
		{
			return m_pBattlePlayers[kind];
		}
		
		virtual inline std::unordered_map<PLAYER_KIND, BattlePlayer*>* HBattlePlayers()
		{
			return &m_pBattlePlayers;
		}

	private:
		void DestroyDeadFollower();
	
		static std::unordered_map<PLAYER_KIND, BattlePlayer*> m_pBattlePlayers;
	};
} // namespace summonersaster

#endif // !PLAYERS_H
