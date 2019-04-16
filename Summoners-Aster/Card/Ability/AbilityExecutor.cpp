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
	}
}

}
