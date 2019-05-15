#include "BattleInformation.h"

namespace summonersaster
{
	int BattleInformation::m_turn = 1;
	PLAYER_KIND BattleInformation::m_winner = PLAYER_KIND::NON_SELECTING;
	PLAYER_KIND BattleInformation::m_startPlayer   = PLAYER_KIND::OPPONENT;
	PLAYER_KIND BattleInformation::m_currentPlayer = PLAYER_KIND::OPPONENT;
	std::deque<BattleInformation::ActionInformation> BattleInformation::m_actionQue;
} // namespace summonersaster
