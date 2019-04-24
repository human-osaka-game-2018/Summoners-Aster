#include "BattleInformation.h"

namespace summonersaster
{
	int BattleInformation::m_turn = 1;
	PLAYER_KIND BattleInformation::m_winner = PLAYER_KIND::OPPONENT;
	PLAYER_KIND BattleInformation::m_startPlayer   = PLAYER_KIND::OPPONENT;
	PLAYER_KIND BattleInformation::m_currentPlayer = PLAYER_KIND::OPPONENT;

	bool BattleInformation::m_isExcecuting = false;
	bool BattleInformation::m_isRotating = false;
} // namespace summonersaster
