#include "AIPlayer.h"

#include "Ability/CardAbilityMediator.h"


namespace summonersaster
{
	using namespace gameframework;
	using CARD_TYPE = Card::TYPE;

	AIPlayer::AIPlayer(const TCHAR* pPlayerTextureKey, const tstring& deckName)
		:OpponentPlayer(pPlayerTextureKey, deckName)
	{
		m_PlayerKind = PLAYER_KIND::OPPONENT;

		m_TexturCenter = { 800.0f, 55.0f };
	}

	AIPlayer::~AIPlayer()
	{

	}

	void AIPlayer::Initialize()
	{
		m_pHand = new Hand(PLAYER_KIND::OPPONENT, D3DXVECTOR2(100.0f, 100));
		m_pDeck = new Deck(USE_DECK_NAME, D3DXVECTOR2(1529.0f, 260.0f));
		m_pDeck->Load(PLAYER_KIND::OPPONENT);
		m_pCemetery = new Cemetery(D3DXVECTOR2(1480.0f, 370.0f));

		D3DXVECTOR2 hpPos(800.0f, 110.0f);
		m_pHP = new HP(hpPos);
		m_pRotationTickets = new RotationTickets(D3DXVECTOR2(1.9f, 0.23f));
		m_pMP = new MP(D3DXVECTOR3(1435.0f, 100.0f, 0.9f));
		m_pWeaponHolder = new WeaponHolder(D3DXVECTOR3(1.15f, 0.0f, 0.9f));

		GameFrameworkFactory::Create(&m_pRect);

		m_pDeck->Shuffle();

		m_rFollowerOrderMediator.Register(PLAYER_KIND::OPPONENT, m_pRect, m_pHP, m_pWeaponHolder);
		m_rRotationOrderMediator.Register(PLAYER_KIND::OPPONENT, m_pRotationTickets);
	}


	bool AIPlayer::UpdateInDrawPhase()
	{
		DrawCard();

		DestroyWornOutCard();

		AssignHands();

		return true;
	}

	//戻り値がTrueでないとターンエンドすることができない
	bool AIPlayer::UpdateInMainPhase()
	{
		m_rField.GetFollowerZone(&m_pFollowerZone);
		DestroyWornOutCard();

		if (this->DecideBehaviour())return false;

		BattleInformation::AIPlayerEnded(true);

		return true;
	}

	//今のところはこの関数は走らない設計になっている
	bool AIPlayer::UpdateInEndPhase()
	{
		m_pHand->Update();

		DestroyWornOutCard();

		return true;
	}

	void AIPlayer::AssignHands()
	{
		//Vectorの中を一度空にする
		m_UsableFollowerCards.clear();
		m_UsableFollowerCards.shrink_to_fit();
		m_UsableSpellCards.clear();
		m_UsableSpellCards.shrink_to_fit();
		m_UsableWeaponCards.clear();
		m_UsableWeaponCards.shrink_to_fit();

		//手札にアクセスするため、手札Vectorのポインタを取得
		std::vector<MovableCard*>* pHands = m_pHand->GetCards();

		for (auto& pHand : *pHands)
		{
			//nullptrアクセスを考慮
			if (pHand == nullptr)continue;
			MovableCard* pMovableCard = pHand;
			Card* pCard = pHand->HCard();
			if (pCard == nullptr)continue;

			if (this->HaveEnoughCost(pCard) == false) continue;
			
			CARD_TYPE assigningHandType = pCard->CARD_TYPE;
			//Follower,Spell,WeaponのVectorに割り当てていく
			switch (assigningHandType)
			{
			case CARD_TYPE::FOLLOWER:
				m_UsableFollowerCards.push_back(pCard);
				break;
			case CARD_TYPE::SPELL:
				m_UsableSpellCards.push_back(pMovableCard);
				break;
			case CARD_TYPE::WEAPON:
				m_UsableWeaponCards.push_back(pMovableCard);
				break;
			}
		}
	}

	bool AIPlayer::DecideBehaviour()
	{
		//今処理中なら
		if (BattleInformation::IsWaitingAction()) return true;

		//行動を遅らせてる途中なら
		if (DelayBehaviour() == false)return true;

		//フォロワー関係の操作行ったら
		if (this->OperateFollower())return true;

		//スペル関係の操作行ったら
		if (this->OperateSpell())return true;

		//ウェポン関係の操作行ったら
		if (this->OperateWeapon())return true;

		//何の行動もできない状態にあるのでfalse
		//このfalseはAIPlayerの行動終了を意味する
		return false;
	}

	bool AIPlayer::OperateFollower()
	{
		//手札のフォロワー関係の操作を行えばtrue
		if (this->OperateHandFollower()) return true;

		//フィールドフォロワー関係の操作を行えばtrue
		if (this->OperateFieldFollower())return true;

		return false;
	}

	bool AIPlayer::OperateHandFollower()
	{
		if (this->HaveFollower() == false)return false;

		if (this->CanSummonFollower() == false)return false;

		return true;
	}

	bool AIPlayer::OperateFieldFollower()
	{
		//行動可能なフォロワーが存在しなければfalse
		if (ActiveFollowerExists() == false)return false;

		//自フォロワーを移動させたらtrue
		if (this->MoveFollower())return true;

		//敵プレイヤーに攻撃を行ったらtrue
		if (this->AttackPlayer())return true;

		//敵フォロワーに攻撃を行ったらtrue
		if (this->AttackFollower())return true;

		return false;
	}

	bool AIPlayer::OperateSpell()
	{
		AssignHands();
		if (this->ShouldUseSpell())
		{
			
			UseSpell();
			AssignHands();
			return true;
		}

		return false;
	}

	bool AIPlayer::OperateWeapon()
	{
		//装備すべきなら
		if (this->ShouldEquipWeapon())
		{
			EquipWeapon();
			AssignHands();
		
			return true;
		}

		//ウェポン装備時にプレイヤーがフォロワーに攻撃できる仕様が完成したら実装する部分
		//if (PlayerShouldAttackFollower())
		//{
		//	//PlayerAttackFollower();
		//	return true;
		//}

		return false;
	}

	//現段階では、召喚できるかだけを判定する関数ではない
	//召喚できるなら召喚まで行っている
	bool AIPlayer::CanSummonFollower()
	{
		for (auto& pCard : *m_pHand->GetCards())
		{
			int handCardIndex = static_cast<int>(&pCard - &(*m_pHand->GetCards())[0]);

			for (int fzi = 0; fzi < m_rField.FIELD_FOLLOWERS_NUM; ++fzi)
			{
				if ((pCard)->HCard()->CARD_TYPE != Card::TYPE::FOLLOWER) continue;

				//フォロワーが召喚できる場所か
				if (m_pFollowerZone[fzi].m_pFollower || m_pFollowerZone[fzi].m_isOpponentZone) continue;
				//コストが足りているか
				if (!m_pMP->CanPay((pCard)->HCard())) continue;

				//召喚時の効果発動
				CardAbilityMediator::Activator(Ability::ActivationEvent::SUMMONED, &m_pFollowerZone[fzi]);

				//召喚する
				ActivateSummoning(handCardIndex, fzi);
				AssignHands();

				return true;
			}
		}

		return false;
	}

	bool AIPlayer::ActiveFollowerExists()
	{
		m_ActiveFieldFollowerIndex.clear();
		m_ActiveFieldFollowerIndex.shrink_to_fit();

		for (int fzi = 0; fzi < m_rField.FIELD_FOLLOWERS_NUM; ++fzi)
		{
			//モンスターがいなければ
			if (m_pFollowerZone[fzi].m_pFollower == nullptr) continue;

			//AIのフォロワーでなければ
			if (m_pFollowerZone[fzi].m_pFollower->Owner() == PLAYER_KIND::PROPONENT)continue;

			//行動可能で
			if (m_rField.CanTakeAction(fzi) == false)continue;

			//行動可能フォロワーのindexをAIPlayerが保存する
			m_ActiveFieldFollowerIndex.push_back(fzi);
		}

		//行動可能フォロワーがいたらTRUEを返す
		return (m_ActiveFieldFollowerIndex.size() > 0) ? true : false;
	}

	//ActiveFollowerExistsで選定したキャラを使って、攻撃する相手を判定する
	bool AIPlayer::AttackPlayer()
	{
		for (auto fieldIndex : m_ActiveFieldFollowerIndex) 
		{
			//自分のフォロワーが敵ゾーンにいなければ
			if (m_pFollowerZone[fieldIndex].m_isOpponentZone == false)continue;

			//FollowerOrderMediatorに「プレイヤーに攻撃する」と伝達してもらう
			m_rFollowerOrderMediator.ActivateAIAttackingPlayer(fieldIndex);
			return true;
		}

		return false;
	}

	bool AIPlayer::AttackFollower()
	{
		for (auto originIndex : m_ActiveFieldFollowerIndex)
		{
			//星型頂点ルールの攻撃方法の場所に攻撃できるか
			m_destIndexInfo[0].destIndex = NormalizeFieldIndex(originIndex + 2);
			m_destIndexInfo[0].canAttackOrMove =
				algorithm::Tertiary(ThisIndexCanAttack(m_destIndexInfo[0].destIndex), true, false);

			m_destIndexInfo[1].destIndex = NormalizeFieldIndex(originIndex + 3);
			m_destIndexInfo[1].canAttackOrMove =
				algorithm::Tertiary(ThisIndexCanAttack(m_destIndexInfo[1].destIndex), true, false);

			//対象となる目標のIndexが決まらなければContinue
			//行動可能ならここで宣言したdestIndexに値を詰めて返してくれる
			int destIndex = 0;
			if (this->DecideFieldZoneIndex(&destIndex) == false)continue;

			m_rFollowerOrderMediator.ActivateAIAttackingFollower(originIndex, destIndex);
			return true;
		}
		
		return false;
	}

	bool AIPlayer::MoveFollower()
	{
		for (auto originIndex : m_ActiveFieldFollowerIndex)
		{
			//星型頂点ルールの移動方法の場所に移動できるか
			m_destIndexInfo[0].destIndex = NormalizeFieldIndex(originIndex + 2);
			m_destIndexInfo[0].canAttackOrMove = 
				algorithm::Tertiary(ThisIndexCanMove(originIndex, m_destIndexInfo[0].destIndex), true, false);

			m_destIndexInfo[1].destIndex = NormalizeFieldIndex(originIndex + 3);
			m_destIndexInfo[1].canAttackOrMove = 
				algorithm::Tertiary(ThisIndexCanMove(originIndex, m_destIndexInfo[1].destIndex), true, false);

			//対象となる目標のIndexが決まらなければContinue
			//行動可能ならここで宣言したdestIndexに値を詰めて返してくれる
			int destIndex = 0;
			if (this->DecideFieldZoneIndex(&destIndex) == false) continue;

			m_rFollowerOrderMediator.ActivateAIMovingFollower(originIndex, destIndex);
			return true;
		}

		return false;
	}

	bool AIPlayer::ShouldUseSpell()
	{
		if (this->HaveSpell() == false)return false;

		return true;
	}

	void AIPlayer::UseSpell()
	{
		DecideSpellCard();

		BattleInformation::ActionInformation actionInformation = { BattleInformation::ACTION_KIND::SPELLING, m_PlayerKind };
		BattleInformation::PushQueBack(actionInformation);
	}

	bool AIPlayer::ShouldEquipWeapon()
	{
		//既にウェポンを装備済みなら
		if (this->IsEquipedWeapon())return false;

		//手札にウェポンを所持していないなら
		if (this->HaveWeapon() == false)return false;

		return true;
	}

	bool AIPlayer::IsEquipedWeapon()
	{
		if (m_pWeaponHolder->HWeapon() == nullptr)return false;

		return true;
	}

	void AIPlayer::EquipWeapon()
	{
		//ウェポン上書きの時のための処理
		if (m_pWeaponHolder->HWeapon())
		{
			ActivateWeaponDestroying();
		}

		DecideWeaponCard();

		BattleInformation::ActionInformation actionInformation = { BattleInformation::ACTION_KIND::ARMING, m_PlayerKind };
		BattleInformation::PushQueBack(actionInformation);
	}

	bool AIPlayer::HaveFollower()
	{
		if (m_UsableFollowerCards.size() > 0) return true;

		return false;
	}

	bool AIPlayer::HaveSpell()
	{
		if (m_UsableSpellCards.size() > 0)return true;

		return false;
	}

	bool AIPlayer::HaveWeapon()
	{
		if (m_UsableWeaponCards.size() > 0)return true;

		return false;
	}

	bool AIPlayer::HaveEnoughCost(Card* pCard)
	{
		unsigned int usableMP = m_pMP->GetUsablePoint();
		if (usableMP >= (unsigned int)pCard->Cost())return true;

		return false;
	}

	int AIPlayer::ThisIndexCanMove(int originFieldZoneIndex, int destFieldZoneIndex)
	{
		//敵がいたら移動しない
		if (m_pFollowerZone[destFieldZoneIndex].m_pFollower) return false;

		//自フォロワーがすでに敵のフィールドにいるなら移動しない
		if (m_pFollowerZone[originFieldZoneIndex].m_isOpponentZone)return false;

		//移動先が敵Playerのフィールドでないなら移動しない
		if (m_pFollowerZone[destFieldZoneIndex].m_isOpponentZone == false)return false;

		return true;
	}

	int AIPlayer::ThisIndexCanAttack(int fieldZoneIndex)
	{
		//指定したZoneにフォロワー自体がいなければ何もしない
		if (m_pFollowerZone[fieldZoneIndex].m_pFollower == nullptr) return false;

		//そのフォロワーが自分のフォロワーであれば何もしない
		if (m_pFollowerZone[fieldZoneIndex].m_pFollower->Owner() == PLAYER_KIND::OPPONENT)return false;

		return true;
	}
	
	int AIPlayer::NormalizeFieldIndex(int index)
	{
		return (index % m_rField.FIELD_FOLLOWERS_NUM);
	}

	bool AIPlayer::DecideFieldZoneIndex(int* destIndex)
	{
		//どちらの頂点も攻撃不可能なら
		if (m_destIndexInfo[0].canAttackOrMove == false &&
			m_destIndexInfo[1].canAttackOrMove == false) return false;

		//どちらの頂点も攻撃可能なら
		if (m_destIndexInfo[0].canAttackOrMove == true &&
			m_destIndexInfo[1].canAttackOrMove == true)
		{
			std::srand((unsigned int)time(NULL));
			*destIndex = m_destIndexInfo[rand() % ELIGIBLE_INDEX_NUM].destIndex;

			return true;
		}

		//攻撃可能な方のIndexを保存する
		for (int i = 0; i < ELIGIBLE_INDEX_NUM; ++i)
		{
			if (m_destIndexInfo[i].canAttackOrMove == false)continue;

			*destIndex = m_destIndexInfo[i].destIndex;
			return true;
		}

		return false;
	}
	
	bool AIPlayer::DecideSpellCard()
	{
		std::srand(static_cast<unsigned int>(time(NULL)));
		int weaponIndex = rand() % static_cast<int>(m_UsableSpellCards.size());
		//m_pSpellTmpに詰めないと、Activate関数系でエラーとなる
		m_pSpellTmp = m_UsableSpellCards[weaponIndex];

		//m_UsableWeaponCardsのポインタが、手札の何番目のIndexと同じかを探す
		auto itr = find(m_pHand->GetCards()->begin(), m_pHand->GetCards()->end(), m_pSpellTmp);
		//手札の何番目のIndexかを計算で求める
		auto index = itr - m_pHand->GetCards()->begin();

		//要素を削除している
		m_pSpellTmp = m_pHand->SendMovableCard(static_cast<unsigned int>(index));
		m_pSpellTmp->CanOperated(false);

		return true;
	}

	bool AIPlayer::DecideWeaponCard()
	{
		std::srand(static_cast<unsigned int>(time(NULL)));
		int weaponCardIndex = rand() % m_UsableWeaponCards.size();
		//m_pWeaponTmpに詰めないと、Activate関数系でエラーとなる
		m_pWeaponTmp = m_UsableWeaponCards[weaponCardIndex]->HCard();

		//m_UsableWeaponCardsのポインタが、手札の何番目のIndexと同じかを探す
		auto itr = find(m_pHand->GetCards()->begin(), m_pHand->GetCards()->end(), m_UsableWeaponCards[weaponCardIndex]);
		//手札の何番目のIndexかを計算で求める
		auto index = itr - m_pHand->GetCards()->begin();

		//要素を削除している
		m_pHand->SendCard(static_cast<unsigned int>(index));

		return true;
	}

	bool AIPlayer::DelayBehaviour()
	{
		++m_delayCount;

		if (m_delayCount >= DELAY_COUNT_MAX)
		{
			m_delayCount = 0;
			return true;
		}

		return false;
	}
}
