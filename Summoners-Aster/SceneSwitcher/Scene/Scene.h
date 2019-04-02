#ifndef SCENE_H
#define SCENE_H

#include "KindBase.h"

namespace summonersaster
{
	// シーンの種類
	// TITLE
	// HOME
	// BATTLE
	// RESULT

	/// <summary>
	/// シーンの基底クラス
	/// </summary>
	class Scene :public KindBase
	{
	public:
		virtual ~Scene();

	protected:
		Scene();
	};
} // namespace summonersaster

#endif //!SCENE_H
