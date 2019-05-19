#ifndef STEP_H
#define STEP_H

#include "KindBase.h"
#include "BattlePlayer/Players.h"
#include "Ability/AbilityTextController.h"
#include "BattleEnums.h"
#include "Field.h"

namespace summonersaster
{
	/// <summary>
	/// ステップの基底クラス
	/// </summary>
	class Step :public KindBase
	{
	public:
		virtual ~Step();

	protected:
		Step();

		int m_frame = 0;

		Field& m_rField = Field::CreateAndGetRef();
		Players& m_rPlayers = Players::CreateAndGetRef();
		RotationOrderMediator& m_rRotationOrderMediator = RotationOrderMediator::CreateAndGetRef();
		AbilityTextController& m_rAbilityTextController = AbilityTextController::CreateAndGetRef();
	};
} // namespace summonersaster

#endif //!STEP_H
