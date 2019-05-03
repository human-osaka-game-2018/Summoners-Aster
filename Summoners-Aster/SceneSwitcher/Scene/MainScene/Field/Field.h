#ifndef FIELD_H
#define FIELD_H

#include <Windows.h>
#include <tchar.h>
#include <vector>

#include <d3dx9.h>

#include <GameFramework.h>

#include "BattleInformation.h"
#include "Button.h"
#include "BattleEnums.h"
#include "Card.h"
#include "Follower/Follower.h"
#include "HP/HP.h"
#include "AttackEffect.h"
#include "Shader.h"

namespace summonersaster
{
	using gameframework::Singleton;
	using gameframework::Vertices;
	using gameframework::Degree;
	using gameframework::RectSize;
	using gameframework::GameFramework;
	using gameframework::GameFrameworkFactory;

	/*////////////////////////////////////////////// FollowerData //////////////////////////////////////////////*/
	/// <summary>
	/// フォロワー情報構造体
	/// </summary>
	struct FollowerData
	{
	public:
		FollowerData();

		~FollowerData();

		Follower* m_pFollower = nullptr;

		/// <summary>
		/// 召喚枠
		/// </summary>
		Vertices* m_pVertices = nullptr;

		/// <summary>
		/// 2pゾーンにいるか
		/// </summary>
		bool m_isOpponentZone = false;

		/// <summary>
		/// 現在選択されているか
		/// </summary>
		bool m_isSelected = true;

		/// <summary>
		/// 現在のターン中に移動を行った
		/// </summary>
		bool m_isMoved = false;

		/// <summary>
		/// 現在のターン中に攻撃を行った
		/// </summary>
		bool m_isAttacked = false;

		/// <summary>
		/// 現在のターン中に召喚された
		/// </summary>
		bool m_isSummoned = false;
	};

	/// <summary>
	/// フォロワーを配置するフィールドクラス
	/// </summary>
	class Field :public Singleton<Field>
	{
	public:
		friend Singleton<Field>;

		Field();

		~Field();

		/// <summary>
		/// 初期化を行う
		/// </summary>
		void Initialize();

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		void Finalize();

		/// <summary>
		/// 移動した攻撃したなどのフラグの初期化
		/// </summary>
		void FinalizeInEndPhaseEnd();

		/// <summary>
		/// 更新を行う
		/// </summary>
		void Update();

		/// <summary>
		/// 描画を行う
		/// </summary>
		void Render();

		/// <summary>
		/// フォロワーゾーンの取得
		/// </summary>
		/// <param name="ppFollowerData">取得したゾーンの先頭アドレスを入れるポインタ</param>
		void GetFollowerZone(FollowerData** ppFollowerData);

		/// <summary>
		/// フォロワーを召喚する
		/// </summary>
		/// <param name="index">要素番号</param>
		/// <param name="pFollower">フォロワーのポインタ</param>
		void SetFollower(int index, Follower* pFollower);

		/// <summary>
		/// HPが0以下になったフォロワーを墓地へ送る
		/// </summary>
		/// <param name="pCemetary">墓地のカードベクター</param>
		void DestroyDeadFollower(std::vector<Card*>* pCemetary);

		/// <summary>
		/// 引数のフォロワーの効果発動
		/// </summary>
		/// <param name="index">要素番号</param>
		void ActivateAbirity(int index);

		/// <summary>
		/// 相手プレイヤーに攻撃を行う
		/// </summary>
		/// <param name="originIndex">主体者</param>
		/// <param name="pHP">相手プレイヤーのHP</param>
		void AttackPlayer(int originIndex, HP* pHP);

		/// <summary>
		/// 攻撃または移動を行う
		/// </summary>
		/// <param name="originIndex">主体者</param>
		/// <param name="destIndex">対象となる場所の要素番号</param>
		void AttackOrMove(int originIndex, int destIndex);

		/// <summary>
		/// 回転の起動
		/// </summary>
		/// <param name="isRightDirection">右回転</param>
		void ActivateOstensiblyCirculation(bool isRightDirection);

		/// <summary>
		/// フィールドのフォロワー数
		/// </summary>
		static const int FIELD_FOLLOWERS_NUM = 5;

		static const int FIELD_RECT_NUM = 3;

		static const TCHAR* pTEXTURE_KEYS[FIELD_RECT_NUM];

	private:
		/*////////////////////////////////////////////// Followers //////////////////////////////////////////////*/
		class Followers
		{
		public:
			Followers();

			~Followers();

			/// <summary>
			/// 移動した攻撃したなどのフラグの初期化
			/// </summary>
			void FinalizeInEndPhaseEnd();

			/// <summary>
			/// 更新を行う
			/// </summary>
			void Update();

			/// <summary>
			/// HPが0以下になったフォロワーを墓地へ送る
			/// </summary>
			/// <param name="pCemetary">墓地のカードベクター</param>
			void DestroyDeadFollower(std::vector<Card*>* pCemetary);

			/// <summary>
			/// 描画を行う
			/// </summary>
			/// <param name="rotationStagingDegree">演出用の回転角度</param>
			void Render(float rotationStagingDegree);

			/// <summary>
			/// 円運動する
			/// </summary>
			/// <param name="isRightDirection">右回転か</param>
			void Circulate(bool isRightDirection);

			/// <summary>
			/// 引数のフォロワーの効果発動
			/// </summary>
			/// <param name="index">要素番号</param>
			void ActivateAbirity(int index);

			/// <summary>
			/// 相手プレイヤーに攻撃を行う
			/// </summary>
			/// <param name="originIndex">主体者</param>
			/// <param name="pHP">相手プレイヤーのHP</param>
			void AttackPlayer(int originIndex, HP* pHP);

			/// <summary>
			/// 攻撃または移動を行う
			/// </summary>
			/// <param name="originIndex">主体者</param>
			/// <param name="destIndex">対象となる場所の要素番号</param>
			void AttackOrMove(int originIndex, int destIndex);

			/// <summary>
			/// フォロワーゾーンの取得
			/// </summary>
			/// <param name="ppFollowerData">取得したゾーンの先頭アドレスを入れるポインタ</param>
			void GetFollowerZone(FollowerData** ppFollowerData);

			/// <summary>
			/// フォロワーを召喚する
			/// </summary>
			/// <param name="index">要素番号</param>
			/// <param name="pFollower">フォロワーのポインタ</param>
			void SetFollower(int index, Follower* pFollower);

			/// <summary>
			/// 行動を起こせるか
			/// </summary>
			/// <param name="index">カードの位置</param>
			/// <returns>起こせるならtrue</returns>
			inline bool CanTakeAction(int index)
			{
				if (m_followerDatas[index].m_isSummoned ||
					m_followerDatas[index].m_isAttacked ||
					m_followerDatas[index].m_isMoved) return false;

				return true;
			}

			/// <summary>
			/// 一回の回転角度
			/// </summary>
			const float ROTATION_DEGREE = 36.0f;

			/// <summary>
			/// フィールドのフォロワー数
			/// </summary>
			static const int FIELD_FOLLOWERS_NUM = 5;

		private:
			/*////////////////////////////////////////////// Followers //////////////////////////////////////////////*/
			Followers(Followers& followers) = delete;

			Followers& operator=(Followers& followers) = delete;

			/// <summary>
			/// フォロワーを墓地へ送る
			/// </summary>
			/// <param name="index">墓地へ送るカードのインデックス</param>
			/// <returns>墓地へ送るカードのポインタ</returns>
			Card* DestroyFollower(int index);

			/// <summary>
			/// 指定したフォロワーデータのフォロワーを空にする
			/// </summary>
			/// <param name="index">要素番号</param>
			void EmptyFollower(int index);

			/// <summary>
			/// フォロワーの状態データの初期化
			/// </summary>
			/// <param name="index">要素番号</param>
			void InitializeFollowerDataState(int index);

			/// <summary>
			/// 攻撃処理の起動
			/// </summary>
			/// <param name="originIndex">主体者</param>
			/// <param name="destIndex">相手</param>
			void ActivateAttackRoutine(int originIndex, int destIndex);

			/// <summary>
			/// 移動処理の起動
			/// </summary>
			/// <param name="originIndex">移動元</param>
			/// <param name="destIndex">移動先</param>
			void ActivateMovingRoutine(int originIndex, int destIndex);

			/// <summary>
			/// 攻撃の一連の処理の更新
			/// </summary>
			void UpdateAttackRoutine();

			/// <summary>
			/// 移動の一連の処理の更新
			/// </summary>
			void UpdateMovingRoutine();

			/// <summary>
			/// 攻撃
			/// </summary>
			void Attack();

			/// <summary>
			/// 反撃
			/// </summary>
			void Counter();

			/// <summary>
			/// 移動を行う
			/// </summary>
			/// <param name="originIndex">主体者</param>
			/// <param name="destIndex">移動する場所</param>
			void Move(int originIndex, int destIndex);

			/// <summary>
			/// フォロワーを配置するフレームの描画
			/// </summary>
			void CreateBackRects(float rotationStagingDegree);

			/// <summary>
			/// 相対的に相手ゾーンにいるかを判定する
			/// </summary>
			void JudgeFollowersZone();

			RectSize m_windowSize;
			D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

			/// <summary>
			/// 回転回数を0~9の範囲で表す
			/// </summary>
			int m_fieldRotationNum = 0;

			const int ATTACK_EFFECT_TAKES_FRAMES = 20;
			const int ATTACK_EFFECT_SPACE_TAKES_FRAMES = 10;
			int m_attackEffectFramesLeft = 0;

			const int NOT_SELECTING_INDEX = -1;
			int m_actionDestIndex = NOT_SELECTING_INDEX;
			int m_actionOriginIndex = NOT_SELECTING_INDEX;

			FollowerData m_followerDatas[FIELD_FOLLOWERS_NUM];

			GameFramework& m_rGameFramework = GameFramework::GetRef();
		};

		/*////////////////////////////////////////////// Field //////////////////////////////////////////////*/
		Field(Field& field) = delete;

		Field& operator=(Field& field) = delete;

		void LocaleField(Vertices* pVertices);

		void LocaleButton();

		/// <summary>
		/// 回転演出の更新
		/// </summary>
		void UpdateOstensiblyCirculation();

		/// <summary>
		/// 回転を行う
		/// </summary>
		/// <param name="isRightDirection">右回転かどうか</param>
		void Rotate(bool isRightDirection);

		RectSize m_windowSize;
		D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

		Vertices* m_pVertices[FIELD_RECT_NUM];
		Vertices* m_pBackVertices;
		Vertices* m_pGraphicFilterVertices;
		Vertices* m_pEndButtonDummyVertices;

		/// <summary>
		/// 右回転+1左回転-1
		/// </summary>
		int m_rotationNum = 0;

		/// <summary>
		/// 回転の演出用の角度
		/// </summary>
		float m_rotationStagingDegree = 0.0f;

		Followers* m_pFollowers = nullptr;

		GameFramework& m_rGameFramework = GameFramework::GetRef();
	};
} // namespace summonersaster

#endif // !FIELD_H
