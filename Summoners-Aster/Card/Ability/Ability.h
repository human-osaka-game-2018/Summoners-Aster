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
		//! 回転時
		ROTATE,
	};
	/// <summary>
	/// 動作の種類
	/// </summary>
	enum Execute
	{
		//! ドロー
		DRAWCARD
	};
	Ability(const ActivationEvent activationEvent, const Execute execute);
	Ability();

	ActivationEvent activationEvent;
	Execute execute;
};
}
#endif
