#ifndef BATTLE_ACTION_EXECUTOR_H
#define BATTLE_ACTION_EXECUTOR_H

#include <deque>
#include <functional>
#include <vector>
#include <queue>
#include <unordered_map>

#include "BattleEnums.h"
#include "BattleInformation.h"
#include "BattlePlayer/Players.h"
#include "Field.h"
#include "FollowerOrderMediator.h"
#include "RotationOrderMediator.h"

namespace summonersaster
{
	/// <summary>
	/// 戦闘アクションの実行クラス
	/// </summary>
	class BattleActionExecutor
	{
	public:
		static void Update();

		static inline void Rotate()
		{
			if (!Field::GetRef().UpdateOstensiblyCirculation()) return;

			BattleInformation::PopQueFront();
		}

		static inline void Attack()
		{
			if (!Field::GetRef().UpdateAttackRoutine()) return;

			BattleInformation::PopQueFront();
		}

		static inline void Move()
		{
			if (!Field::GetRef().UpdateMovingRoutine()) return;

			BattleInformation::PopQueFront();
		}

		static inline void Summon()
		{
			if (!ActionProponentPlayer().UpdateSummoningRoutine()) return;

			BattleInformation::PopQueFront();
		}

		static inline void DstroyWeapon()
		{
			if (!ActionProponentPlayer().UpdateWeaponDestroyingRoutine()) return;

			BattleInformation::PopQueFront();
		}

		static inline void DestroyFollower()
		{
			if (!Field::GetRef().UpdateDestroyingRoutine()) return;

			BattleInformation::PopQueFront();
		}

		static inline void Arm()
		{
			if (!ActionProponentPlayer().UpdateArmingRoutine()) return;

			BattleInformation::PopQueFront();
		}

	private:
		using ACTION_KIND = BattleInformation::ACTION_KIND;

		BattleActionExecutor()  = delete;
		~BattleActionExecutor() = delete;

		static inline BattlePlayer& ActionProponentPlayer()
		{
			PLAYER_KIND playerKind = BattleInformation::QueFront().m_playerKind;

			auto pPlayers = Players::GetRef().HBattlePlayers();

			return *((*pPlayers)[playerKind]);
		}
	};
} // namespace summonersaster

#endif // !BATTLE_ACTION_EXECUTOR_H
