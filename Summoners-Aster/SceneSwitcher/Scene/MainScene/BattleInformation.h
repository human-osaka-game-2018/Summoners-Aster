#ifndef BATTLE_INFORMATION_H
#define BATTLE_INFORMATION_H

#include <deque>
#include <functional>
#include <vector>
#include <queue>
#include <unordered_map>

#include "BattleEnums.h"

namespace summonersaster
{
	/// <summary>
	/// 戦闘情報統括クラス
	/// </summary>
	class BattleInformation
	{
	public:
		enum class ACTION_KIND
		{
			NOTHING,
			ROTATION,
			ATTACK,
			ATTACKING_PLAYER,
			MOVING,
			SUMMONING,
			ARMING,
			SPELLING,
			HAND_CARD_DESTROYING,
			FOLLOWER_DESTROYING,
			WEAPON_DESTROYING,
		};

		struct ActionInformation
		{
		public:
			ActionInformation(ACTION_KIND actionKind, PLAYER_KIND playerKind)
				:m_actionKind(actionKind), m_playerKind(playerKind)
			{

			}

			ACTION_KIND m_actionKind;
			PLAYER_KIND m_playerKind;
		};

		static inline int Turn()
		{
			return m_turn;
		}

		static inline void Turn(int turn)
		{
			m_turn = turn;
		}

		static inline bool AIPlayerEnded()
		{
			return m_aIPlayerEnded;
		}

		static inline void AIPlayerEnded(bool AIPlayerEnded)
		{
			m_aIPlayerEnded = AIPlayerEnded;
		}

		static inline PLAYER_KIND Winner()
		{
			return m_winner;
		}

		static inline void Winner(PLAYER_KIND winner)
		{
			m_winner = winner;
		}

		static inline PLAYER_KIND CurrentPlayer()
		{
			return m_currentPlayer;
		}

		static inline void CurrentPlayer(PLAYER_KIND currentPlayer)
		{
			m_currentPlayer = currentPlayer;
		}

		static inline PLAYER_KIND StartPlayer()
		{
			return m_startPlayer;
		}

		static inline void StartPlayer(PLAYER_KIND startPlayer)
		{
			CurrentPlayer(m_startPlayer = startPlayer);
		}

		static inline void PushQueBack(const ActionInformation& actionInformation)
		{
			m_actionQue.push_back(actionInformation);
		}

		static inline void PopQueFront()
		{
			m_actionQue.pop_front();
		}

		static inline void ClearQue()
		{
			m_actionQue.clear();
		}

		static inline ActionInformation QueFront()
		{
			if (!IsWaitingAction()) return ActionInformation(ACTION_KIND::NOTHING, CurrentPlayer());

			return m_actionQue.front();
		}

		static inline bool IsWaitingAction()
		{
			if (m_actionQue.empty()) return false;

			return true;
		}

		static inline void Initialize()
		{
			m_winner = PLAYER_KIND::NON_SELECTING;
			m_turn = 1;
		}

	private:
		BattleInformation()  = delete;
		~BattleInformation() = delete;

		static int m_turn;
		static bool m_aIPlayerEnded;
		static PLAYER_KIND m_winner;
		static PLAYER_KIND m_startPlayer;
		static PLAYER_KIND m_currentPlayer;
		static std::deque<ActionInformation> m_actionQue;
	};
} // namespace summonersaster

#endif // !BATTLE_INFORMATION_H
