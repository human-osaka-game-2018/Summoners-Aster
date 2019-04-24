#ifndef BATTLE_INFORMATION_H
#define BATTLE_INFORMATION_H

#include "BattleEnums.h"

namespace summonersaster
{
	class BattleInformation
	{
	public:
		static inline int Turn()
		{
			return m_turn;
		}

		static inline void Turn(int turn)
		{
			m_turn = turn;
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

		static inline bool IsRotating()
		{
			return m_isRotating;
		}

		static inline void IsRotating(bool isRotating)
		{
			m_isRotating = isRotating;
		}

		static inline bool IsExcecuting()
		{
			if (IsRotating()) return true;

			return false;
		}

	private:
		BattleInformation()  = delete;
		~BattleInformation() = delete;

		static int m_turn;
		static PLAYER_KIND m_winner;
		static PLAYER_KIND m_startPlayer;
		static PLAYER_KIND m_currentPlayer;

		static bool m_isExcecuting;
		static bool m_isRotating;
	};
} // namespace summonersaster

#endif // !BATTLE_INFORMATION_H
