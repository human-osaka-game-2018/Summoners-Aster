#ifndef FIELD_H
#define FIELD_H

#include <Windows.h>
#include <tchar.h>
#include <vector>

#include <d3dx9.h>

#include <GameFramework.h>

#include "Button.h"

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
		/// <param name="ppFollowerZones"></param>
		void GetFollowerZones(Vertices** ppFollowerZones);

		/// <summary>
		/// フォロワーを召喚する
		/// </summary>
		/// <param name="index">要素番号</param>
		/// <param name="pFollower">フォロワーのポインタ</param>
		void SetFollower(int index, Card* pFollower);

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
			/// 円運動する
			/// </summary>
			/// <param name="isRightDirection">右回転か</param>
			void Circulation(bool isRightDirection);

			/// <summary>
			/// フォロワーの処理更新
			/// </summary>
			void UpdateFollowerAction();

			/// <summary>
			/// 描画を行う
			/// </summary>
			void Render();

			/// <summary>
			/// フォロワーゾーンの取得
			/// </summary>
			/// <param name="ppFollowerZones"></param>
			void GetFollowerZones(Vertices** ppFollowerZones);

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

		private:
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

				Vertices* m_pVertices = nullptr;

				/// <summary>
				/// 2pゾーンにいるか
				/// </summary>
				bool m_isOpponentZone = false;

				bool m_isSelected = true;

				/// <summary>
				/// 現在のターン中に移動を行った
				/// </summary>
				bool m_isMoved = false;
				bool m_isAttacked = false;
				bool m_isSummoned = false;
			};

			/*////////////////////////////////////////////// Followers //////////////////////////////////////////////*/
			Followers(Followers& followers) = delete;

			Followers& operator=(Followers& followers) = delete;

			/// <summary>
			/// HPが0以下になったフォロワーを墓地へ送る
			/// </summary>
			void DestoroyDeadFollower();

			/// <summary>
			/// フォロワーを墓地へ送る
			/// </summary>
			/// <param name="index"></param>
			/// <returns></returns>
			Card* DestoroyFollower(int index);

			/// <summary>
			/// 選択されたフォロワーの効果の発動
			/// </summary>
			void ActivateAbirity();

			/// <summary>
			/// 引数のフォロワーの効果発動
			/// </summary>
			/// <param name="index">要素番号</param>
			void ActivateAbirity(int index);

			/// <summary>
			/// 動作主フォロワーの選択または攻撃移動
			/// </summary>
			void SetIsSelectedAndAttackOrMove();

			/// <summary>
			/// 動作主フォロワーが選択されているか
			/// </summary>
			/// <returns>選択されていればtrue</returns>
			bool IsSelected();

			/// <summary>
			/// 動作主フォロワーの設定
			/// </summary>
			/// <param name="pSelectedData">選択されたフォロワーのポインタ</param>
			void SetIsSelected(FollowerData* pSelectedData);

			/// <summary>
			/// 選択状態をすべてニュートラルにする
			/// </summary>
			void NeutralizeSelecting();

			/// <summary>
			/// 現在動作主に選択されているフォロワーの取得
			/// </summary>
			/// <returns>選択されているフォロワーのインデックス</returns>
			/// <remarks>選択されていなかった場合-1</remarks>
			int GetSelectedFollowerIndex();

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
			/// 攻撃または移動を行う
			/// </summary>
			/// <param name="originIndex">主体者</param>
			/// <param name="destIndex">相手</param>
			void AttackOrMove(int originIndex, int destIndex);

			/// <summary>
			/// 攻撃を行う
			/// </summary>
			/// <param name="originIndex">主体者</param>
			/// <param name="destIndex">相手</param>
			void Attack(int originIndex, int destIndex);

			/// <summary>
			/// 相手プレイヤーに攻撃を行う
			/// </summary>
			void AttackOpponent();

			/// <summary>
			/// 相手プレイヤーに攻撃を行う
			/// </summary>
			/// <param name="originIndex">主体者</param>
			void Attack(int originIndex);

			/// <summary>
			/// 移動を行う
			/// </summary>
			/// <param name="originIndex">主体者</param>
			/// <param name="destIndex">相手</param>
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
			/// 2pゾーンにいるかを判定する
			/// </summary>
			void JudgeFollowersZone();

			RectSize m_windowSize;
			D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

			/// <summary>
			/// 回転回数を0~9の範囲で表す
			/// </summary>
			int m_fieldRotationNum = 0;

			FollowerData m_followerDatas[5];

			GameFramework& m_rGameFramework = GameFramework::GetRef();
		};

		/*////////////////////////////////////////////// Field //////////////////////////////////////////////*/
		Field(Field& field) = delete;

		Field& operator=(Field& field) = delete;

		/// <summary>
		/// ボタンが押されたか確認し、それに応じて回転する
		/// </summary>
		void RotateByClickedButton();

		/// <summary>
		/// 回転ボタンの配置
		/// </summary>
		void LocaleButton();

		/// <summary>
		/// フィールドの配置
		/// </summary>
		void LocaleField();

		RectSize m_windowSize;
		D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

		Vertices* m_pVertices;

		/// <summary>
		/// 回転ボタン右左
		/// </summary>
		Button* m_pRRotationButton;
		Button* m_pLRotationButton;

		/// <summary>
		/// 右回転+1左回転-1
		/// </summary>
		int m_rotationNum = 0;

		Followers* m_pFollowers = nullptr;

		GameFramework& m_rGameFramework = GameFramework::GetRef();
	};
} // namespace summonersaster

#endif // !FIELD_H
