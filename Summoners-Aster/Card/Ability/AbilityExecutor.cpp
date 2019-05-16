#include "AbilityExecutor.h"
#include <windows.h>
#include "BattlePlayer/Players.h"

namespace summonersaster
{


AbilityExecutor::AbilityExecutor()
{
}


AbilityExecutor::~AbilityExecutor()
{
}

void AbilityExecutor::Execute(Card* card)
{
	switch (card->GetExcute())
	{
	case Ability::Execute::DRAWCARD:
		Players::GetPlayer(card->Owner())->DrawCard();
		OutputDebugString(L"カードをドローします\n");
		break;
	case Ability::Execute::DIRECT_ATTACK:
	{
		PLAYER_KIND kind = (card->Owner() == PLAYER_KIND::OPPONENT) ? PLAYER_KIND::PROPONENT : PLAYER_KIND::OPPONENT;
		Players::GetPlayer(kind)->Damaged(dynamic_cast<Follower*>(card)->Attack());
		OutputDebugString(L"相手プレイヤーに直接攻撃します\n");
		break; 
	}
	default:
		OutputDebugString(L"発動できませんでした\n");
	}
}

void AbilityExecutor::Execute(FollowerData* followerData)
{
	switch (followerData->m_pFollower->GetExcute())
	{
	case Ability::Execute::DRAWCARD:
		Players::GetPlayer(followerData->m_pFollower->Owner())->DrawCard();
		OutputDebugString(L"カードをドローします\n");
		break;
	case Ability::Execute::SPEED_ATTACK:
		followerData->m_isSummoned = false;
		OutputDebugString(L"召喚酔いを無くします\n");
		break;
	case Ability::Execute::DIRECT_ATTACK:
		// 自陣にいる場合に発動できる
	{
		if ((followerData->m_isOpponentZone && followerData->m_pFollower->Owner() != PLAYER_KIND::OPPONENT) ||
			(!followerData->m_isOpponentZone && followerData->m_pFollower->Owner() == PLAYER_KIND::OPPONENT)) break;
		PLAYER_KIND kind = (followerData->m_pFollower->Owner() == PLAYER_KIND::OPPONENT) ? PLAYER_KIND::PROPONENT : PLAYER_KIND::OPPONENT;
		Players::GetPlayer(kind)->Damaged(followerData->m_pFollower->Attack());
		OutputDebugString(L"相手プレイヤーに直接攻撃します\n");
		break;
	}
	default:
		OutputDebugString(L"発動できませんでした\n");
	}
}

}
