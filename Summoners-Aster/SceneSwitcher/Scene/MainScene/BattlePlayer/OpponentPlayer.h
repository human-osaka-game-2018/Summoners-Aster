#ifndef OPPONENT_PLAYER_H
#define OPPONENT_PLAYER_H

#include <tchar.h>

#include <GameFramework.h>

#include "BattlePlayer.h"
#include "Deck/Deck.h"
#include "Hand/Hand.h"
#include "Cemetery/Cemetery.h"
#include "HP/HP.h"
#include "MP/MP.h"
#include "RotationTickets/RotationTickets.h"
#include "FollowerOrderMediator.h"
#include "RotationOrderMediator.h"
#include "BattleEnums.h"

namespace summonersaster
{
	using gameframework::tstring;

	using gameframework::Singleton;

	class OpponentPlayer :public BattlePlayer
	{
	public:
		OpponentPlayer(const TCHAR* pPlayerTextureKey, const tstring& deckName = _T("AllFollower"));

		~OpponentPlayer();

		void Initialize()override;
	};
} // namespace summonersaster

#endif // !OPPONENT_PLAYER_H
