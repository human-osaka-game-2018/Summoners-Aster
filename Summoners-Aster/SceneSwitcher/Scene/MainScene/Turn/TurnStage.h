#ifndef TURN_STAGE_H
#define TURN_STAGE_H

#include "KindBase.h"
#include "BattleEnums.h"
#include "BattlePlayer/BattlePlayer.h"
#include "Field.h"

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
		BattlePlayer& m_rPlayer = BattlePlayer::CreateAndGetRef();
		RotationOrderMediator& m_rRotationOrderMediator = RotationOrderMediator::CreateAndGetRef();
	};
} // namespace summonersaster

#endif //!TURN_STAGE_H
