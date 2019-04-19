#ifndef STEP_H
#define STEP_H

#include "KindBase.h"
#include "BattlePlayer/BattlePlayer.h"
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
		BattlePlayer& m_rPlayer = BattlePlayer::CreateAndGetRef();
		RotationOrderMediator& m_rRotationOrderMediator = RotationOrderMediator::CreateAndGetRef();
	};
} // namespace summonersaster

#endif //!STEP_H
