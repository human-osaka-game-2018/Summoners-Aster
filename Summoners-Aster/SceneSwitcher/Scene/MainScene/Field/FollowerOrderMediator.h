#ifndef FOLLOWER_ORDER_MEDIATOR_H
#define FOLLOWER_ORDER_MEDIATOR_H

#include <Windows.h>
#include <vector>
#include <unordered_map>

#include <GameFramework.h>

#include "Field.h"
#include "BattleEnums.h"
#include "Card.h"
#include "Follower/Follower.h"
#include "BattleInformation.h"
#include "WeaponHolder/WeaponHolder.h"

namespace summonersaster
{
	using gameframework::Singleton;
	using gameframework::Vertices;
	using gameframework::Degree;
	using gameframework::RectSize;
	using gameframework::GameFramework;
	using gameframework::GameFrameworkFactory;

	/// <summary>
	///	フィールドにある味方フォロワーに命令を送る際の仲介クラス
	/// </summary>
	class FollowerOrderMediator :public Singleton<FollowerOrderMediator>
	{
	public:
		friend Singleton<FollowerOrderMediator>;

		FollowerOrderMediator();

		~FollowerOrderMediator();

		/// <summary>
		/// プレイヤー情報の登録
		/// </summary>
		/// <param name="PlayerKind">プレイヤーの種類</param>
		/// <param name="pPlayerIconVertices">プレイヤーアイコンの矩形</param>
		/// <param name="pHP">体力</param>
		void Register(PLAYER_KIND PlayerKind, Vertices* pPlayerIconVertices, HP* pHP, WeaponHolder* pWeaponHolder);

		/// <summary>
		/// フォロワーに対する処理の実行
		/// </summary>
		void ProcessFollowerOrders();

		/// <summary>
		/// プレイヤーに攻撃する際の一連の処理
		/// </summary>
		/// <returns>終了したらtrue</returns>
		bool UpdateAttackingPlayerRoutine();

	private:
		using ActionInformation = BattleInformation::ActionInformation;

		struct PlayerAttackData
		{
		public:
			PlayerAttackData();
			PlayerAttackData(Vertices* pVertices, HP* pHP, WeaponHolder* pWeaponHolder);

			Vertices* m_pPlayerIconVertices = nullptr;
			HP* m_pHP = nullptr;
			WeaponHolder* m_pWeaponHolder = nullptr;
		};

		FollowerOrderMediator(FollowerOrderMediator& followerOrderMediator) = delete;

		FollowerOrderMediator& operator=(FollowerOrderMediator& followerOrderMediator) = delete;

		/// <summary>
		/// カーソルが乗っているフィールド上のフォロワーのインデックス取得
		/// </summary>
		/// <returns>フォロワーのインデックス</returns>
		/// <remarks>乗っていなかったら-1</remarks>
		int GetFieldFollowerIndexCursorRidden();

		/// <summary>
		/// 効果の発動
		/// </summary>
		void ActivateAbirity();

		/// <summary>
		/// フィールド上のフォロワーを選択して起こす処理の実行
		/// </summary>
		void SetIsSelectedAndAttackOrMove();

		/// <summary>
		/// 相手プレイヤーに攻撃を行う
		/// </summary>
		void ActivateAttackingPlayer();

		/// <summary>
		/// カードが選択状態にあるか
		/// </summary>
		/// <returns></returns>
		bool IsSelected();

		/// <summary>
		/// 既に選択されていたら解除、されていなかったら選択する
		/// </summary>
		/// <param name="pSelectedData">対象のデータ</param>
		void SetIsSelected(FollowerData* pSelectedData);

		/// <summary>
		/// 選択解除
		/// </summary>
		void NeutralizeSelecting();

		/// <summary>
		/// 選択されているフォロワーのインデックスの取得
		/// </summary>
		/// <returns>フォロワーのインデックス</returns>
		/// <remarks>乗っていなかったら-1</remarks>
		int GetSelectingFollowerIndex();

		FollowerData* m_pFollowerZone = nullptr;

		std::unordered_map<PLAYER_KIND, PlayerAttackData> m_playersAttackData;

		int m_attackingFollowerIndex = 0;

		const int ATTACK_EFFECT_TAKES_FRAMES = 20;
		const int ATTACK_EFFECT_SPACE_TAKES_FRAMES = 10;
		int m_attackEffectFramesLeft = 0;

		Field& m_rField = Field::CreateAndGetRef();

		GameFramework& m_rGameFramework = GameFramework::GetRef();
	};
} // namespace summonersaster

#endif // !FOLLOWER_ORDER_MEDIATOR_H
