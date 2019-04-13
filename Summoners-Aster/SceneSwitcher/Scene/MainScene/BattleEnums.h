#ifndef BATTLE_ENUMS_H
#define BATTLE_ENUMS_H

namespace summonersaster
{
	/// <summary>
	/// プレイヤーの種類
	/// </summary>
	enum class PLAYER_KIND
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
	enum class BATTLE_ORDER
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

} // namespace summonersaster

#endif // ! BATTLE_ENUMS_H
