#ifndef ABILITY_TEXT_CONTROLLER_H
#define ABILITY_TEXT_CONTROLLER_H

#include <unordered_map>
#include <iostream>
#include <locale> 
#include <codecvt> 
#include <fstream>
#include <cstdlib>
#include <algorithm>

#include <GameFramework.h>

#include "Card.h"
#include "CardFolder.h"
#include "Follower/Follower.h"
#include "Weapon/Weapon.h"
#include "Spell/Spell.h"
#include "BattleEnums.h"
#include "Card.h"
#include "Field.h"
#include "BattlePlayer/Players.h"

namespace summonersaster
{
	using gameframework::tstring;
	using gameframework::tstringstream;
	using gameframework::RectSize;
	using gameframework::Vertices;
	using gameframework::Degree;
	using gameframework::GameFramework;
	using gameframework::Singleton;
	using gameframework::LPFONT;
	using gameframework::WindowParam;

	/// <summary>
	/// カード効果の表示
	/// </summary>
	class AbilityTextController :public Singleton<AbilityTextController>
	{
	public:
		friend Singleton<AbilityTextController>;

		~AbilityTextController();

		void Update();
		
		void Render();

		void RenderBack();

		/// <summary>
		/// カードの詳細を描画する
		/// </summary>
		/// <param name="cardName">表示したいカードの名前</param>
		void RenderRemarks(const tstring& cardName);

		/// <summary>
		/// カード効果の表示
		/// </summary>
		/// <param name="cardName">表示したいカードの名前</param>
		/// <param name="topLeft">表示の開始地点左上</param>
		///// <param name="pFont">フォントオブジェクトのポインタ</param>
		void RenderAbilityText(const tstring& cardName, const D3DXVECTOR2& topLeft, const LPFONT& pFont);

	private:
		using ActivationEvent = Ability::ActivationEvent;
		using Execute = Ability::Execute;

		class Count
		{
		public:
			Count(int countMax);

			float ProcessRatio();

			void UpdateCount();

			bool ShouldIncreased();

			void ShouldIncreased(bool shouldIncreased);

			const int COUNT_MAX;

		private:
			void IncrementCount();

			void DecrementCount();

			int m_count = 0;

			bool m_shoudIncreased = false;
		};

		AbilityTextController();

		AbilityTextController(AbilityTextController& abilityTextController) = delete;

		AbilityTextController& operator=(AbilityTextController& abilityTextController) = delete;

		void SearchSelectedCard();

		void SearchSelectedCardOnField();

		void SearchCardRiddenCursorInHand();

		void SearchCardRiddenCursorInWeaponHolder();

		const TCHAR* GetActivationText(const tstring& cardName);

		const TCHAR* GetExecuteText(const tstring& cardName);

		D3DXVECTOR2 m_windowBottomRight = { 0.0f, 0.0f };

		Count* m_pStagingCount = nullptr;

		const TCHAR* pNOT_FOUND = _T("404:Not_Found");

		Stream* m_pAbilityStream = nullptr;
		Vertices* m_pBack = nullptr;

		tstring m_selectedCardName;

		CardFolder& m_rCardFolder = CardFolder::CreateAndGetRef();

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();
	};
}  // namespace summonersaster

#endif // !ABILITY_TEXT_CONTROLLER_H
