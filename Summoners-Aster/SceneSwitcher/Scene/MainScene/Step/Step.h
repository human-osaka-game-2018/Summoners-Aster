#ifndef STEP_H
#define STEP_H

#include "KindBase.h"

namespace summonersaster
{
	// ステップの種類
	// PLAYERS_INFOMATION_RENDERING_STEP
	// BATTLE_PREPARING_STEP
	// BATTLE_STEP
	// RESULT_STEP

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
	};
} // namespace summonersaster

#endif //!STEP_H
