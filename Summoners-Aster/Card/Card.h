#ifndef CARD_H
#define CARD_H

#include <Windows.h>
#include <tchar.h>

#include <GameFramework.h>
#include "BattleEnums.h"

namespace summonersaster
{
	using gameframework::tstring;
	using gameframework::RectSize;
	using gameframework::Vertices;
	using gameframework::Degree;
	using gameframework::GameFramework;

	/// <summary>
	/// カード基底クラス
	/// </summary>
	class Card
	{
	public:
		/// <summary>
		/// カードの種類
		/// </summary>
		enum class TYPE : UCHAR
		{
			FOLLOWER,
			SPELL,
			WEAPON
		};

		virtual ~Card();

		/// <summary>
		/// 初期化する
		/// </summary>
		virtual void Initialize();

		/// <summary>
		/// リソースの読み込み	
		/// </summary>
		virtual void LoadResource();

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		virtual void Finalize();

		/// <summary>
		/// リソースなどの開放を行う
		/// </summary>
		virtual void Release();

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="center">描画する際の中心座標</param>
		/// <param name="size">描画する際のカードの幅と高さ</param>
		void Render(const D3DXVECTOR3& center, const RectSize& size, const Degree& rotationZ = 0.0f);

		/// <summary>
		/// 自身のコピーを動的確保する
		/// </summary>
		/// <param name="ppCard">コピーされるカードのポインタのポインタ</param>
		virtual void CreateCopy(Card** ppCard) const = 0;

		const tstring& Name() const
		{
			return m_name;
		}

		inline int Cost() const
		{
			return m_cost;
		}

		inline void Cost(int cost)
		{
			m_cost = cost;
		}

		inline Vertices& Rect()
		{
			return *m_pRect;
		}

		inline PLAYER_KIND Owner()
		{
			return m_owner;
		}

		inline PLAYER_KIND Owner(PLAYER_KIND owner)
		{
			m_owner = owner;
		}

		const TYPE CARD_TYPE;

	protected:
		Card(TYPE type, const tstring& name, const tstring& texturePath, int cost);

		Card(Card& card) = delete;

		Card& operator=(Card& card) = delete;

		tstring m_name;
		tstring m_texturePath;
		const TCHAR* pTEXTURE_KEY = nullptr;

		int m_cost = 0;
		PLAYER_KIND m_owner = PLAYER_KIND::PROPONENT;

		gameframework::Vertices* m_pRect = nullptr;

		gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();
	};
} // namespace summonersaster

#endif // !CARD_H
