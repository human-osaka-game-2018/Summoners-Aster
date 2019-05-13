#include "Field.h"

#include "Ability\CardAbilityMediator.h"

using namespace gameframework;

namespace summonersaster
{
	FollowerData::FollowerData()
	{
		GameFrameworkFactory::Create(&m_pVertices);
		m_pVertices->SetColor(0xAA000000);
	}

	FollowerData::~FollowerData()
	{
		delete m_pVertices;
		delete m_pFollower;
	}

	const TCHAR* Field::pTEXTURE_KEYS[Field::FIELD_RECT_NUM] =
	{
		_T("FIELD0"),
		_T("FIELD1"),
		_T("FIELD2")
	};

	Field::Field()
	{
		gameframework::WindowParam::GetWindowSize(&m_windowSize);

		m_windowCenter.x = m_windowSize.m_width  * 0.5f;
		m_windowCenter.y = m_windowSize.m_height * 0.5f;

		for (auto& pVertices : m_pVertices)
		{
			GameFrameworkFactory::Create(&pVertices);
			LocaleField(pVertices);
		}

		GameFrameworkFactory::Create(&m_pBackVertices);
		LocaleField(m_pBackVertices);

		GameFrameworkFactory::Create(&m_pGraphicFilterVertices);
		LocaleField(m_pGraphicFilterVertices);

		GameFrameworkFactory::Create(&m_pEndButtonDummyVertices);
		LocaleButton();

		m_pFollowers = new Followers();
	}

	Field::~Field()
	{
		
	}

	void Field::Initialize()
	{
		bool isOpponentTurn = algorithm::Tertiary(BattleInformation::StartPlayer() == PLAYER_KIND::OPPONENT, true, false);

		//先攻が自分のターンなら回らない
		if (!isOpponentTurn) return;

		ActivateOstensiblyCirculation(isOpponentTurn);
	}

	void Field::Finalize()
	{
		for (auto& pVertices : m_pVertices)
		{
			delete pVertices;
			pVertices = nullptr;
		}

		delete m_pBackVertices;
		m_pBackVertices = nullptr;

		delete m_pGraphicFilterVertices;
		m_pGraphicFilterVertices = nullptr;
		
		delete m_pEndButtonDummyVertices;
		m_pEndButtonDummyVertices = nullptr;

		delete m_pFollowers;
	}

	void Field::FinalizeInEndPhaseEnd()
	{
		m_pFollowers->FinalizeInEndPhaseEnd();
	}

	void Field::ActivateOstensiblyCirculation(bool isRightDirection)
	{
		m_rotationStagingDegree += algorithm::Tertiary(isRightDirection, +0.0001f, -0.0001f);

		BattleInformation::ActionInformation actionInformation = { BattleInformation::ACTION_KIND::ROTATION, BattleInformation::CurrentPlayer() };
		BattleInformation::PushQueBack(actionInformation);
	}

	void Field::Rotate(bool isRightDirection)
	{
		m_rotationNum += ((isRightDirection) ? -1 : +1);
	}

	void Field::Update()
	{
		m_pFollowers->Update();
	}

	void Field::Render()
	{
		m_pBackVertices->Render(m_rGameFramework.GetTexture(_T("BATTLE_BACK")));

		for (auto& pVertices : m_pVertices)
		{
			int index = static_cast<int>(&pVertices - &m_pVertices[0]);

			if (index == 2)
			{
				pVertices->AddRotationZ(0.5f * algorithm::Tertiary(index % 2, +1.0f, -1.0f));
			}

			if (index == 1)
			{
				pVertices->SetRotationZ(m_pFollowers->ROTATION_DEGREE * m_rotationNum + m_rotationStagingDegree);
			}

			pVertices->Render(m_rGameFramework.GetTexture(pTEXTURE_KEYS[index]));
		}

		m_pGraphicFilterVertices->Render(m_rGameFramework.GetTexture(_T("DIGITAL_FILTER")));

		m_pFollowers->Render(m_rotationStagingDegree);
	}

	void Field::RenderDummyButton()
	{
		m_pEndButtonDummyVertices->Render(m_rGameFramework.GetTexture(_T("END_MAIN_BUTTON")));
	}

	bool Field::UpdateOstensiblyCirculation()
	{
		//回転方向の判定
		if (m_rotationStagingDegree == 0.0f) return true;
		bool isRightDirection = algorithm::Tertiary(m_rotationStagingDegree < 0.0f, true, false);

		float RotationDegree = m_pFollowers->ROTATION_DEGREE;
		float sign = algorithm::Tertiary(isRightDirection, -1.0f, +1.0f);

		if (fabsf(m_rotationStagingDegree += sign * (RotationDegree / 30.0f)) <= RotationDegree) return false;

		m_rotationStagingDegree = 0.0f;

		Rotate(isRightDirection);
		m_pFollowers->Circulate(isRightDirection);

		return true;
	}

	void Field::GetFollowerZone(FollowerData** ppFollowerData)
	{
		m_pFollowers->GetFollowerZone(ppFollowerData);
	}

	void Field::SetFollower(int index, Follower* pFollower)
	{
		m_pFollowers->SetFollower(index, pFollower);
	}

	void Field::ActivateAbirity(int index)
	{
		m_pFollowers->ActivateAbirity(index);
	}

	void Field::AttackPlayer(int originIndex, HP* pHP)
	{
		m_pFollowers->AttackPlayer(originIndex, pHP);
	}

	void Field::AttackOrMove(int originIndex, int destIndex)
	{
		m_pFollowers->AttackOrMove(originIndex, destIndex);
	}

	Field::Followers::Followers()
	{
		gameframework::WindowParam::GetWindowSize(&m_windowSize);

		m_windowCenter.x = m_windowSize.m_width  * 0.5f;
		m_windowCenter.y = m_windowSize.m_height * 0.5f;
	}

	Field::Followers::~Followers()
	{

	}

	void Field::Followers::SetFollower(int index, Follower* pFollower)
	{
		m_followerDatas[index].m_pFollower = pFollower;
		m_followerDatas[index].m_isSummoned = true;
	}

	bool Field::Followers::UpdateAttackRoutine()
	{
		static bool isRoutineStart = true;

		if (isRoutineStart)
		{
			RegisterEffect(m_actionOriginIndex, m_actionDestIndex);

			isRoutineStart = false;
		}

		if (m_attackEffectFramesLeft-- > 0) return false;

		static int spaceFramesAfterAttack = 0;

		if (!m_followerDatas[m_actionOriginIndex].m_isAttacked)
		{
			Attack();

			RegisterEffect(m_actionDestIndex, m_actionOriginIndex);

			spaceFramesAfterAttack = 0;

			return false;
		}

		if (spaceFramesAfterAttack == 0)
		{
			Counter();
		}

		if (spaceFramesAfterAttack++ < 30) return false;

		return isRoutineStart = true;
	}

	bool Field::Followers::UpdateMovingRoutine()
	{
		static bool isRoutineStart = true;

		if (isRoutineStart)
		{
			RegisterEffect(m_actionOriginIndex, m_actionDestIndex);

			m_followerDatas[m_actionOriginIndex].m_pFollower->Rect().SetColor(0x00FFFFFF);

			isRoutineStart = false;
		}

		if ((m_attackEffectFramesLeft-- > 0)) return false;

		Move(m_actionOriginIndex, m_actionDestIndex);

		m_followerDatas[m_actionDestIndex].m_pFollower->Rect().SetColor(0xFFFFFFFF);

		return isRoutineStart = true;
	}

	bool Field::Followers::UpdateDestroyingRoutine()
	{
		static bool isRoutineStart = true;

		if (isRoutineStart)
		{
			m_EffectTakesFrame = EFFECT_TAKES_FRAME_MAX;

			isRoutineStart = false;
		}

		Vertices& rCard = m_followerDatas[m_deadFollowerIndicies.front()].m_pFollower->Rect();

		rCard.FadeOut(EFFECT_TAKES_FRAME_MAX, 255, 0);

		if (m_EffectTakesFrame-- > 0) return false;

		DestroyFollower(m_deadFollowerIndicies.front());

		m_deadFollowerIndicies.pop_front();

		return isRoutineStart = true;
	}

	void Field::Followers::SearchAndActivateDestroyingFollower()
	{
		auto IsSameDeadFollowerIndex = [&](int index)->bool
		{
			for (auto& deadIndex : m_deadFollowerIndicies)
			{
				if (deadIndex == index) return true;
			}

			return false;
		};

		for (auto& followerData : m_followerDatas)
		{
			if (!followerData.m_pFollower) continue;

			if (followerData.m_pFollower->HP() > 0) continue;

			int index = static_cast<int>(&followerData - &m_followerDatas[0]);
			CardAbilityMediator::Unregister(&followerData);
			CardAbilityMediator::Activator(Ability::KILLED, &followerData);

			if (IsSameDeadFollowerIndex(index)) continue;

			m_deadFollowerIndicies.push_back(index);

			BattleInformation::PushQueBack(ActionInformation(ACTION_KIND::FOLLOWER_DESTROYING,
				followerData.m_pFollower->Owner()));
		}
	}

	void Field::Followers::DestroyFollower(int index)
	{
		Follower** ppCard = &m_followerDatas[index].m_pFollower;

		if (!(*ppCard)) return;

		m_pCemetaryTmp.push_back(*ppCard);
		
		m_followerDatas[index].m_pFollower = nullptr;

		EmptyFollower(index);
	}

	void Field::Followers::Circulate(bool isRightDirection)
	{
		m_fieldRotationNum += algorithm::Tertiary(isRightDirection, -1, +1);

		//0~9に正規化する
		const int ROTATION_NUM_MAX = 10;

		m_fieldRotationNum %= ROTATION_NUM_MAX;

		if (m_fieldRotationNum >= 0) return;

		m_fieldRotationNum = ROTATION_NUM_MAX + m_fieldRotationNum;
	}

	void Field::Followers::FinalizeInEndPhaseEnd()
	{
		for (auto& followerData : m_followerDatas)
		{
			int index = static_cast<int>(&followerData - &m_followerDatas[0]);

			InitializeFollowerDataState(index);
		}
	}

	void Field::Followers::AttackPlayer(int originIndex, HP* pHP)
	{
		if (!CanTakeAction(originIndex)) return;

		pHP->Damaged(m_followerDatas[originIndex].m_pFollower->Attack());

		m_followerDatas[originIndex].m_isAttacked = true;
	}

	void Field::Followers::Update()
	{
		JudgeFollowersZone();

		SearchAndActivateDestroyingFollower();
	}

	void Field::Followers::Render(float rotationStagingDegree)
	{
		CreateBackRects(rotationStagingDegree);

		for (auto& followerData : m_followerDatas)
		{
			int index = static_cast<int>(&followerData - &m_followerDatas[0]);

			followerData.m_pVertices->Render(nullptr);

			if (!followerData.m_pFollower) continue;

			Vertices& rVertices = *followerData.m_pVertices;

			followerData.m_pFollower->Render(rVertices.GetCenter(), rVertices.GetSize());

			if (!followerData.m_isSelected)continue;

			followerData.m_pVertices->GetColor() = 0x88FFFFFF;

			Shader& rShader = Shader::CreateAndGetRef();

			rShader.Render(followerData.m_pVertices, m_rGameFramework.GetTexture(_T("SELECTING_CARD_FRAME")));
		}
	}

	void Field::Followers::GetFollowerZone(FollowerData** ppFollowerData)
	{
		*ppFollowerData = m_followerDatas;
	}

	void Field::Followers::ActivateAbirity(int index)
	{
		//効果発動イベントディスパッチ
		CardAbilityMediator::Activator(Ability::ODRERED,&m_followerDatas[index]);
	}

	void Field::Followers::EmptyFollower(int index)
	{
		delete m_followerDatas[index].m_pFollower;

		InitializeFollowerDataState(index);
	}

	void Field::Followers::InitializeFollowerDataState(int index)
	{
		m_followerDatas[index].m_isSelected = false;
		m_followerDatas[index].m_isMoved	= false;
		m_followerDatas[index].m_isAttacked = false;
		m_followerDatas[index].m_isSummoned = false;
	}

	void Field::Followers::AttackOrMove(int originIndex, int destIndex)
	{
		if (!CanTakeAction(originIndex)) return;

		auto Normalize = [&](int index)
		{
			return (index % (_countof(m_followerDatas)));
		};

		if (destIndex != Normalize(originIndex + 2) && destIndex != Normalize(originIndex + 3)) return;

		if (m_followerDatas[destIndex].m_pFollower)
		{
			ActivateAttackRoutine(originIndex, destIndex);

			return;
		}

		ActivateMovingRoutine(originIndex, destIndex);
	}

	void Field::Followers::ActivateAttackRoutine(int originIndex, int destIndex)
	{
		if (BattleInformation::IsWaitingAction()) return;

		BattleInformation::PushQueBack(ActionInformation(ACTION_KIND::ATTACK, BattleInformation::CurrentPlayer()));

		m_actionOriginIndex = originIndex;
		m_actionDestIndex = destIndex;
	}

	void Field::Followers::ActivateMovingRoutine(int originIndex, int destIndex)
	{
		if (BattleInformation::IsWaitingAction()) return;

		BattleInformation::PushQueBack(ActionInformation(ACTION_KIND::MOVING, BattleInformation::CurrentPlayer()));

		m_actionOriginIndex = originIndex;
		m_actionDestIndex = destIndex;
	}

	void Field::Followers::RegisterEffect(int originIndex, int destIndex)
	{
		m_rGameFramework.RegisterGraphicEffect(
			new AttackEffect(m_followerDatas[originIndex].m_pVertices->GetCenter(),
				m_followerDatas[destIndex].m_pVertices->GetCenter(), ATTACK_EFFECT_TAKES_FRAMES));

		m_attackEffectFramesLeft = ATTACK_EFFECT_TAKES_FRAMES + ATTACK_EFFECT_SPACE_TAKES_FRAMES;
	}

	void Field::Followers::Attack()
	{
		(*m_followerDatas[m_actionDestIndex].m_pFollower) -= m_followerDatas[m_actionOriginIndex].m_pFollower;

		m_followerDatas[m_actionOriginIndex].m_isAttacked = true;
	}

	void Field::Followers::Counter()
	{
		(*m_followerDatas[m_actionOriginIndex].m_pFollower) -= m_followerDatas[m_actionDestIndex].m_pFollower;
	}

	void Field::Followers::Move(int originIndex, int destIndex)
	{
		EmptyFollower(destIndex);

		m_followerDatas[destIndex].m_isAttacked = m_followerDatas[originIndex].m_isAttacked;
		m_followerDatas[destIndex].m_isMoved = m_followerDatas[originIndex].m_isMoved;
		m_followerDatas[destIndex].m_isSummoned = m_followerDatas[originIndex].m_isSummoned;
		m_followerDatas[destIndex].m_pFollower = m_followerDatas[originIndex].m_pFollower;

		m_followerDatas[originIndex].m_pFollower = nullptr;

		m_followerDatas[destIndex].m_isMoved = true;

		EmptyFollower(originIndex);

		//移動イベントディスパッチ
	}

	void Field::Followers::CreateBackRects(float rotationStagingDegree)
	{
		//フィールドの中心からフォロワーを配置する位置のベクトル
		D3DXVECTOR3 posVecByCenter(0.0f, -m_windowSize.m_height * 0.25f, 0.0f);

		D3DXVECTOR3 windowCenter(m_windowCenter.x, m_windowCenter.y, posVecByCenter.z);

		gameframework::algorithm::D3DXVec3RotationZ(&posVecByCenter, ROTATION_DEGREE * m_fieldRotationNum + rotationStagingDegree);

		RectSize cardSize;
		cardSize.m_height = 1.4f * (cardSize.m_width = m_windowSize.m_width * 0.05f);

		for (auto& followerData : m_followerDatas)
		{
			//フォロワーは72°ずつ回転して配置される
			followerData.m_pVertices->GetCenter() = windowCenter + posVecByCenter;

			followerData.m_pVertices->GetSize() = cardSize;

			gameframework::algorithm::D3DXVec3RotationZ(&posVecByCenter, 2.0f * ROTATION_DEGREE);
		}
	}

	void Field::Followers::JudgeFollowersZone()
	{
		const int FOLLOWERS_NUM = _countof(m_followerDatas);

		//相手のゾーンの配列番号の始まり
		int opponentZoneStartElementNum = (FOLLOWERS_NUM - 1 - m_fieldRotationNum / 2) % FOLLOWERS_NUM;

		//1回転するたびに頂点を求めるための量が変わる
		int opponentZoneFollowersNum = algorithm::Tertiary((m_fieldRotationNum % 2) == 0, 3, 2);

		auto IsInOpponentZone = [&](int index)->bool
		{
			for (int i = 0; i < opponentZoneFollowersNum; ++i)
			{
				if (index != (opponentZoneStartElementNum + i) % FOLLOWERS_NUM) continue;
				
				return false;
			}

			return true;
		};

		for (auto& followerData : m_followerDatas)
		{
			int index = static_cast<int>(&followerData - &m_followerDatas[0]);

			followerData.m_isOpponentZone = IsInOpponentZone(index);

			if (BattleInformation::CurrentPlayer() == PLAYER_KIND::OPPONENT) continue;

			followerData.m_isOpponentZone = !followerData.m_isOpponentZone;
		}
	}

	void Field::LocaleField(Vertices* pVertices)
	{
		pVertices->GetCenter() = { m_windowCenter.x, m_windowCenter.y, 1.0f };

		pVertices->GetSize() = m_windowSize;
	}

	void Field::LocaleButton()
	{
		Vertices& rEndButton = *m_pEndButtonDummyVertices;

		RectSize windowSize;
		WindowParam::GetWindowSize(&windowSize);

		rEndButton.GetCenter() = { windowSize.m_width, windowSize.m_height * 0.5f, 0.88f };

		RectSize size;
		size.m_width = size.m_height = windowSize.m_width * 0.17f;
		rEndButton.GetSize() = size;

		rEndButton.SetColor(0xFF888888);
	}
} // namespace summonersaster
