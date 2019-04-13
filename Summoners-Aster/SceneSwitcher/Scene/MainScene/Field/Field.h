#ifndef FIELD_H
#define FIELD_H

#include <Windows.h>
#include <tchar.h>
#include <vector>

#include <d3dx9.h>

#include <GameFramework.h>

#include "Button.h"
#include "BattleEnums.h"

namespace summonersaster
{
	using gameframework::Singleton;
	using gameframework::Vertices;
	using gameframework::Degree;
	using gameframework::RectSize;
	using gameframework::GameFramework;
	using gameframework::GameFrameworkFactory;

	class Follower;
	class Card;
	class HP;

	/*////////////////////////////////////////////// FollowerData //////////////////////////////////////////////*/
	/// <summary>
	/// フォロワー情報構造体
	/// </summary>
	struct FollowerData
	{
	public:
		FollowerData();

		~FollowerData();

		Card* m_pFollower = nullptr;

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
		/// テクスチャなどの読み込み
		/// </summary>
		void LoadResource();

		/// <summary>
		/// 初期化を行う
		/// </summary>
		/// <param name="isPropnentPrecedence">1pが先行か</param>
		void Initialize(bool isPropnentPrecedence);
		
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
		void Update(PLAYER_KIND currentPlayerKind);

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
		void SetFollower(int index, Card* pFollower);

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
		/// 回転を行う
		/// </summary>
		/// <param name="isRightDirection">右回転かどうか</param>
		void Rotate(bool isRightDirection);

		/// <summary>
		/// フィールドのフォロワー数
		/// </summary>
		static const int FIELD_FOLLOWERS_NUM = 5;

	private:
		/*////////////////////////////////////////////// Followers //////////////////////////////////////////////*/
		class Followers
		{
		public:
			/// <param name="isPropnentPrecedence">1pが先行か</param>
			Followers(bool isPropnentPrecedence);

			~Followers();
			
			/// <summary>
			/// 移動した攻撃したなどのフラグの初期化
			/// </summary>
			void FinalizeInEndPhaseEnd();

			/// <summary>
			/// 更新を行う
			/// </summary>
			/// <param name="currentPlayerKind">現在のターンプレイヤー</param>
			void Update(PLAYER_KIND currentPlayerKind);

			/// <summary>
			/// HPが0以下になったフォロワーを墓地へ送る
			/// </summary>
			/// <param name="pCemetary">墓地のカードベクター</param>
			void DestroyDeadFollower(std::vector<Card*>* pCemetary);

			/// <summary>
			/// 描画を行う
			/// </summary>
			void Render();

			/// <summary>
			/// 円運動する
			/// </summary>
			/// <param name="isRightDirection">右回転か</param>
			void Circulation(bool isRightDirection);

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
			void SetFollower(int index, Card* pFollower);

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
			/// 攻撃を行う
			/// </summary>
			/// <param name="originIndex">主体者</param>
			/// <param name="destIndex">相手</param>
			void Attack(int originIndex, int destIndex);

			/// <summary>
			/// 移動を行う
			/// </summary>
			/// <param name="originIndex">主体者</param>
			/// <param name="destIndex">移動する場所</param>
			void Move(int originIndex, int destIndex);

			/// <summary>
			/// フォロワーを配置するフレームの描画
			/// </summary>
			void CreateBackRects();

			/// <summary>
			/// フォロワーの位置の設定
			/// </summary>
			void SetFollowerPos();

			/// <summary>
			/// 相対的に相手ゾーンにいるかを判定する
			/// </summary>
			/// <param name="currentPlayerKind">現在のプレイヤー</param>
			void JudgeFollowersZone(PLAYER_KIND currentPlayerKind);

			RectSize m_windowSize;
			D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

			/// <summary>
			/// 回転回数を0~9の範囲で表す
			/// </summary>
			int m_fieldRotationNum = 0;

			FollowerData m_followerDatas[FIELD_FOLLOWERS_NUM];

			GameFramework& m_rGameFramework = GameFramework::GetRef();
		};

		/*////////////////////////////////////////////// Field //////////////////////////////////////////////*/
		Field(Field& field) = delete;

		Field& operator=(Field& field) = delete;

		/// <summary>
		/// フィールドの配置
		/// </summary>
		void LocaleField();

		RectSize m_windowSize;
		D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

		Vertices* m_pVertices;

		/// <summary>
		/// 右回転+1左回転-1
		/// </summary>
		int m_rotationNum = 0;

		Followers* m_pFollowers = nullptr;

		GameFramework& m_rGameFramework = GameFramework::GetRef();
	};
} // namespace summonersaster

#endif // !FIELD_H
