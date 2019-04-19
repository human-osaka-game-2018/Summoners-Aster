#ifndef BATTLE_ENUMS_H
#define BATTLE_ENUMS_H

#include <GameFramework.h>

namespace summonersaster
{
	using gameframework::tstring;

	/// <summary>
	/// プレイヤーの種類
	/// </summary>
	enum class PLAYER_KIND :char
	{
		/// <summary>
		/// 主体者
		/// </summary>
		PROPONENT,

		/// <summary>
		/// 相手
		/// </summary>
		OPPONENT,
	};

	/// <summary>
	/// 戦う順序
	/// </summary>
	enum class BATTLE_ORDER :char
	{
		/// <summary>
		/// 先攻
		/// </summary>
		FIRST,

		/// <summary>
		/// 後攻
		/// </summary>
		SECOND,
	};

	struct SCENE_KIND
	{
	public:
		static const tstring TITLE;
		static const tstring HOME;
		static const tstring MAIN;
		static const tstring RESULT;
	};

	struct STEP_KIND
	{
	public:
		static const tstring PLAYERS_INFOMATION_RENDERING;
		static const tstring BATTLE_PREPARING;
		static const tstring BATTLE;
		static const tstring RESULT;
	};

	struct TURN_STAGE_KIND
	{
	public:
		static const tstring UI_RENDERING;
		static const tstring PHASE_OPERATION;
	};

	struct PHASE_KIND
	{
	public:
		static const tstring DRAW;
		static const tstring MAIN;
		static const tstring END;
	};
} // namespace summonersaster

#endif // ! BATTLE_ENUMS_H
