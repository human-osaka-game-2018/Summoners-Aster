#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include <tchar.h>

#include <GameFramework.h>

#include "OpponentPlayer.h"
#include "Deck/Deck.h"
#include "Hand/Hand.h"
#include "Cemetery/Cemetery.h"
#include "HP/HP.h"
#include "MP/MP.h"
#include "RotationTickets/RotationTickets.h"
#include "FollowerOrderMediator.h"
#include "RotationOrderMediator.h"
#include "BattleEnums.h"

namespace summonersaster
{
	using gameframework::tstring;

	using gameframework::Singleton;

	class AIPlayer :public OpponentPlayer
	{
	public:
		AIPlayer(const TCHAR* pPlayerTextureKey, const tstring& deckName = _T("AllFollower"));
		~AIPlayer();

		void Initialize()override;

	protected:
		virtual bool UpdateInDrawPhase();
		virtual bool UpdateInMainPhase();
		virtual bool UpdateInEndPhase();

	private:
		/// <summary>
		/// 手札をフォロワー、スペル、ウェポンに割り当てる関数
		/// </summary>
		/// <remarks>手札の数が変わった場合に呼ぶ</remarks>
		void AssignHands();

		/// <summary>
		/// AIの行動を決める関数
		/// </summary>
		/// <returns>行動が決定されたらTrue</returns>
		bool DecideBehaviour();

		/// <summary>
		/// Follower関係の操作を行う関数
		/// </summary>
		/// <returns>フォロワー関係の操作を行ったらTrue</returns>
		bool OperateFollower();

		/// <summary>
		/// 手札にいるFollower関係の操作を行う関数
		/// </summary>
		/// <returns>手札のFollower関係の操作を行ったらTrue</returns>
		bool OperateHandFollower();

		/// <summary>
		/// フィールドにいるFollower関係の操作を行う関数
		/// </summary>
		/// <returns>フィールドにいるFollower関係の操作を行ったらTrue</returns>
		bool OperateFieldFollower();

		/// <summary>
		/// Spell関係の操作を行う関数
		/// </summary>
		/// <returns>スペル関係の操作を行ったらTrue</returns>
		bool OperateSpell();

		/// <summary>
		/// Weapon関係の操作を行う関数
		/// </summary>
		/// <returns>Weapon関係の操作を行ったらTrue</returns>
		bool OperateWeapon();

		/// <summary>
		/// フォロワーを召喚することができるか判定する関数
		/// </summary>
		/// <returns>フォロワーが召喚できるならTrue</returns>
		bool CanSummonFollower();

		/// <summary>
		/// フォロワーの召喚位置を決める関数
		/// </summary>
		/// <returns>召喚位置が決まればTrue</returns>
		bool DecideSummonPos();

		/// <summary>
		/// 行動可能なフォロワーが存在しているか判定する関数
		/// </summary>
		/// <remarks>存在していたらそのフォロワーのFieldZoneIndexをvectorに保存する</remarks>
		/// <returns>行動可能なフォロワーが存在したらTrue</returns>
		bool ActiveFollowerExists();

		/// <summary>
		/// フォロワーを移動させる関数
		/// </summary>
		/// <returns>フォロワーが移動を行えたらTrue</returns>
		bool MoveFollower();

		/// <summary>
		/// フォロワーが敵プレイヤーに攻撃する関数
		/// </summary>
		/// <returns>フォロワーが攻撃を行えたらTrue</returns>
		bool AttackPlayer();

		/// <summary>
		/// フォロワーが敵キャラに攻撃する関数
		/// </summary>
		/// <returns>フォロワーが攻撃を行えたらTrue</returns>
		bool AttackFollower();

		/// <summary>
		/// スペルカードを使用するべきか判定する関数
		/// </summary>
		/// <returns>スペルを使用するべきならTrue</returns>
		bool ShouldUseSpell();

		/// <summary>
		/// スペルカードを使用する関数
		/// </summary>
		void UseSpell();

		/// <summary>
		/// ウェポンカードを装備すべきか判定する関数
		/// </summary>
		/// <returns>ウェポンカードをを装備すべきならTrue</returns>
		bool ShouldEquipWeapon();

		/// <summary>
		/// 武器を装備しているか判定する関数
		/// </summary>
		/// <returns>武器を装備していたらTrue</returns>
		bool IsEquipedWeapon();

		/// <summary>
		/// 武器を装備する関数
		/// </summary>
		void EquipWeapon();

		/// <summary>
		/// 手札にフォロワーカードをもっているかどうか確認する関数
		/// </summary>
		/// <returns>手札にフォロワーカードがあればTrue</returns>
		bool HaveFollower();

		/// <summary>
		/// 手札にスペルカードをもっているかどうか判定する関数
		/// </summary>
		/// <returns>手札にスペルカードがあればTrue</returns>
		bool HaveSpell();

		/// <summary>
		/// 手札にウェポンカードをもっているかどうか判定する関数
		/// </summary>
		/// <returns>手札にウェポンカードがあればTrue</returns>
		bool HaveWeapon();

		/// <summary>
		/// コストが足りているかどうか判定する関数
		/// </summary>
		/// <param name="pCard">カードのポインタ</param>
		/// <returns>コストが足りているならTrue</returns>
		bool HaveEnoughCost(Card* pCard);

		/// <summary>
		///　渡したFieldZoneIndexに移動できるかを判定する関数
		/// </summary>
		/// <param name="originFieldZoneIndex">原点となるフィールドの場所のIndex</param>
		/// <param name="destFieldZoneIndex">目的となるフィールドの場所のIndex</param>
		/// <returns>渡したIndexに移動できるならTrue</returns>
		int ThisIndexCanMove(int originFieldZoneIndex, int destFieldZoneIndex);

		/// <summary>
		///　渡したFieldZoneIndexのフォロワーに攻撃できるかを判定する関数
		/// </summary>
		/// <param name="fieldZoneIndex">フィールドの場所のIndex</param>
		/// <returns>渡したIndexのフォロワー攻撃できるならTrue</returns>
		int ThisIndexCanAttack(int fieldZoneIndex);

		/// <summary>
		/// フィールドのインデックスを正規化する関数
		/// </summary>
		/// <remarks>フィールドのインデックスは0～4までなのでそれ以上や以下にならないように</remarks>
		/// <returns>フィールドの0～4のインデックスを返す</returns>
		int NormalizeFieldIndex(int index);

		/// <summary>
		/// 攻撃するフォロワーがいるfieldZoneIndex、または移動できるfieldZoneIndexを決定する関数
		/// </summary>
		/// <remarks>fieldZoneIndexが決まれば引数のdestIndexに値をつめる</remarks>
		/// <param name="destIndex">決まったfieldZoneIndexを保存する先のポインタ</param>
		/// <returns>Indexを決定出来たらTrue</returns>
		bool DecideFieldZoneIndex(int* destIndex);

		/// <summary>
		/// 使用する手札のスペルを決定する関数
		/// </summary>
		/// <returns>使用するスペルが決定したらTrue</returns>
		bool DecideSpellCard();

		/// <summary>
		/// 装備する手札のウェポンを決定する関数
		/// </summary>
		/// <returns>装備するウェポンが決定したらTrue</returns>
		bool DecideWeaponCard();

		/// <summary>
		/// AIの行動が早いので、少し遅らせる処理
		/// </summary>
		/// <returns>行動できる時間が経てばTrue</returns>
		bool DelayBehaviour();

		std::vector<Card*> m_UsableFollowerCards;         //!<使える手札のフォロワーカードを保存する
		std::vector<MovableCard*> m_UsableSpellCards;     //!<使える手札のスペルカードを保存する
		std::vector<MovableCard*> m_UsableWeaponCards;    //!<使える手札のウェポンカードを保存する
		std::vector<int> m_ActiveFieldFollowerIndex;      //!<行動可能な自フォロワーのFieldZoneIndexを保存する

		/// <summary>
		/// 攻撃や移動を行えるかどうかの情報を持つ構造体
		/// </summary>
		struct DestIndexInfo
		{
			int destIndex;           //!<攻撃や移動の目的となるFieldZoneIndex
			bool canAttackOrMove;    //!<その目的のFieldZoneIndexに行動可能か
		};

		static const int ELIGIBLE_INDEX_NUM = 2;    //!<星型のフィールドの規則である、攻撃や移動の対象となる最大Index数
		DestIndexInfo m_destIndexInfo[ELIGIBLE_INDEX_NUM];

		static const int DELAY_COUNT_MAX = 60;
		int m_delayCount = 0;
	};
} // namespace summonersaster

#endif // !AI_PLAYER_H
