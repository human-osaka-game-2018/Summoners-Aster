#ifndef PHASE_H
#define PHASE_H

#include "KindBase.h"

namespace summonersaster
{
	// フェイズの種類
	// DRAW
	// MAIN
	// END

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
	};
} // namespace summonersaster

#endif //!PHASE_H
