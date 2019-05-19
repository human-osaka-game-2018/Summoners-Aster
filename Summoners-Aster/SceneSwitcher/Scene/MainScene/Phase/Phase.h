#ifndef PHASE_H
#define PHASE_H

#include "KindBase.h"
#include "BattlePlayer/Players.h"
#include "BattleEnums.h"
#include "Field.h"
#include "Ability/AbilityTextController.h"

namespace summonersaster
{
	/// <summary>
	/// フェイズの基底クラス
	/// </summary>
	class Phase :public KindBase
	{
	public:
		virtual ~Phase();

	protected:
		Phase();

		int m_frame = 0;

		Field& m_rField = Field::CreateAndGetRef();
		Players& m_rPlayers = Players::CreateAndGetRef();
		RotationOrderMediator& m_rRotationOrderMediator = RotationOrderMediator::CreateAndGetRef();
		AbilityTextController& m_rAbilityTextController = AbilityTextController::CreateAndGetRef();
	};
} // namespace summonersaster

#endif //!PHASE_H
