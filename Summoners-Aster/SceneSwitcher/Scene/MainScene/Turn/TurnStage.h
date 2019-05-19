#ifndef TURN_STAGE_H
#define TURN_STAGE_H

#include "KindBase.h"
#include "BattleEnums.h"
#include "BattlePlayer//Players.h"
#include "Field.h"
#include "Ability/AbilityTextController.h"

namespace summonersaster
{
	/// <summary>
	/// フェイズの基底クラス
	/// </summary>
	class TurnStage :public KindBase
	{
	public:
		virtual ~TurnStage();

	protected:
		TurnStage();

		Field& m_rField = Field::CreateAndGetRef();
		Players& m_rPlayers = Players::CreateAndGetRef();
		RotationOrderMediator& m_rRotationOrderMediator = RotationOrderMediator::CreateAndGetRef();
		AbilityTextController& m_rAbilityTextController = AbilityTextController::CreateAndGetRef();
	};
} // namespace summonersaster

#endif //!TURN_STAGE_H
