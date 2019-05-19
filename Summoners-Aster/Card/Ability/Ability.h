#ifndef ABILITY_H
#define ABILITY_H

namespace summonersaster
{
/// <summary>
/// カード効果を保存しておく入れ物
/// </summary>
struct Ability
{
public:
	/// <summary>
	/// 効果の発動イベント
	/// </summary>
	enum ActivationEvent
	{
		//! 発動イベントなし
		NONE,
		//! 回転時
		ROTATE,
		//! 召喚をしたとき
		SUMMON,
		//! 召喚された時
		SUMMONED,
		//! 破壊されたとき
		KILLED,
		//! 命令されたとき
		ODRERED,
		//! 自分が移動した
		MOVED,
		//! 誰かが移動した
		FOLLOWER_MOVED,
		//! 相手フォロワーが移動した
		RIVAL_FOLLOWER_MOVED,
		//! 自分フォロワーが移動した
		ALLY_FOLLOWER_MOVED,
		//! 攻撃した
		ATTACK,
		//! 相手プレイヤーに攻撃した
		ATTACK_RIVAL_PLAYER,
		//! 相手フォロワーに攻撃した
		ATTACK_RIVAL_FOLLOWER,
		//! 相手が攻撃した
		RIVAL_ATTACKED,
		//! 自分が攻撃された
		ATTACKED,
		//! 味方フォロワーが攻撃された
		ATTACKED_ALLY_FOLLOWER,
		//! オーナープレイヤーが攻撃された
		ATTACKED_OWNER_PLAYER,
		//! 相手フォロワーを破壊した
		KILL_RIVAL_FOLLOWER,
	};
	/// <summary>
	/// 動作の種類
	/// </summary>
	enum Execute
	{
		//! ドロー
		DRAWCARD,
		//! スピードアタッカー
		SPEED_ATTACK,
		DIRECT_ATTACK,
	};
	Ability(const ActivationEvent activationEvent, const Execute execute);
	Ability();

	ActivationEvent activationEvent;
	Execute execute;
};
}
#endif
