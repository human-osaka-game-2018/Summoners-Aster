#ifndef TURN_STAGE_H
#define TURN_STAGE_H

#include "KindBase.h"

namespace summonersaster
{
	// フェイズの種類
	// TURN_UI_RENDERING
	// PHASE_OPERATION

	/// <summary>
	/// フェイズの基底クラス
	/// </summary>
	class TurnStage :public KindBase
	{
	public:
		virtual ~TurnStage();

	protected:
		TurnStage();
	};
} // namespace summonersaster

#endif //!TURN_STAGE_H
