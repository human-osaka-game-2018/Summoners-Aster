#ifndef ROTATION_ORDER_MEDIATOR_H
#define ROTATION_ORDER_MEDIATOR_H

#include <Windows.h>
#include <vector>
#include <unordered_map>

#include <GameFramework.h>

#include "Field.h"
#include "BattleEnums.h"

namespace summonersaster
{
	using gameframework::Singleton;
	using gameframework::Vertices;
	using gameframework::Degree;
	using gameframework::RectSize;
	using gameframework::LPTEXTURE;
	using gameframework::TextureUVs;
	using gameframework::GameFramework;
	using gameframework::GameFrameworkFactory;

	class Card;
	class RotationPoint;

	/// <summary>
	///	フィールド自体に命令を送る際の仲介クラス
	/// </summary>
	class RotationOrderMediator :public Singleton<RotationOrderMediator>
	{
	public:
		friend Singleton<RotationOrderMediator>;

		RotationOrderMediator();
		~RotationOrderMediator();

		/// <summary>
		/// テクスチャなどの読み込み
		/// </summary>
		void LoadResource();

		/// <summary>
		/// プレイヤー情報の登録
		/// </summary>
		/// <param name="PlayerKind">プレイヤーの種類</param>
		/// <param name="pRotationPoint">回転権</param>
		void Register(PLAYER_KIND PlayerKind, RotationPoint* pRotationPoint);

		/// <summary>
		/// 回転命令の処理
		/// </summary>
		void ProcessRotationOrders();

		/// <summary>
		/// 回転UIの描画
		/// </summary>
		void Render();

	private:
		RotationOrderMediator(RotationOrderMediator& rotationOrderMediator) = delete;

		RotationOrderMediator& operator=(RotationOrderMediator& rotationOrderMediator) = delete;

		/// <summary>
		/// ボタンの設置
		/// </summary>
		void LocaleButton();

		/// <summary>
		/// 回転ボタン右左
		/// </summary>
		Button* m_pRRotationButton = nullptr;
		Button* m_pLRotationButton = nullptr;

		std::unordered_map<PLAYER_KIND, RotationPoint*> m_pPlayerRotationPoints;

		Field& m_rField = Field::CreateAndGetRef();

		RectSize m_windowSize;
		D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

		GameFramework& m_rGameFramework = GameFramework::GetRef();
	};
} // namespace summonersaster

#endif // !ROTATION_ORDER_MEDIATOR_H
