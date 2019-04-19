#include "Field.h"

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

		LoadResource();
	}

	Field::~Field()
	{
		for (auto& textureKey : pTEXTURE_KEYS)
		{
			m_rGameFramework.ReleaseTexture(textureKey);
		}
	}

	void Field::LoadResource()
	{
		m_rGameFramework.CreateTexture(pTEXTURE_KEYS[0], _T("Textures/Battle_rotationStar1.png"));
		m_rGameFramework.CreateTexture(pTEXTURE_KEYS[1], _T("Textures/Battle_rotationStar2.png"));
		m_rGameFramework.CreateTexture(pTEXTURE_KEYS[2], _T("Textures/Battle_rotationStar3.png"));
		m_rGameFramework.CreateTexture(pTEXTURE_KEYS[3], _T("Textures/Battle_rotationStar4.png"));
		m_rGameFramework.CreateTexture(pTEXTURE_KEYS[4], _T("Textures/Battle_rotationStar5.png"));
		m_rGameFramework.CreateTexture(pTEXTURE_KEYS[5], _T("Textures/Battle_rotationStar6.png"));
		m_rGameFramework.CreateTexture(_T("BATTLE_BACK"), _T("Textures/Battle_background01.png"));
		m_rGameFramework.CreateTexture(_T("DIGITAL_FILTER"), _T("Textures/Battle_digitalFilter.png"));
	}

	void Field::Initialize(bool isPropnentPrecedence)
	{
		m_rotationNum += algorithm::Tertiary(isPropnentPrecedence, 0, 1);

		m_pFollowers->Initialized(isPropnentPrecedence);
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

	void Field::Rotate(bool isRightDirection)
	{
		m_pFollowers->Circulation(isRightDirection);

		m_rotationNum += ((isRightDirection) ? +1 : -1);
	}

	void Field::Update(PLAYER_KIND currentPlayerKind)
	{
		m_pFollowers->Update(currentPlayerKind);
	}

	void Field::Render()
	{
		m_pBackVertices->Render(m_rGameFramework.GetTexture(_T("BATTLE_BACK")));

		for (auto& pVertices : m_pVertices)
		{
			int index = static_cast<int>(&pVertices - &m_pVertices[0]);

			pVertices->AddRotationZ(0.5f * algorithm::Tertiary(index % 2, +1.0f, -1.0f));

			if (index <= 1)
			{
				pVertices->SetRotationZ(m_pFollowers->ROTATION_DEGREE * m_rotationNum);
			}

			pVertices->Render(m_rGameFramework.GetTexture(pTEXTURE_KEYS[index]));
		}

		m_pGraphicFilterVertices->Render(m_rGameFramework.GetTexture(_T("DIGITAL_FILTER")));

		m_pFollowers->Render();
		m_pEndButtonDummyVertices->Render(m_rGameFramework.GetTexture(_T("END_MAIN_BUTTON")));
	}

	void Field::GetFollowerZone(FollowerData** ppFollowerData)
	{
		m_pFollowers->GetFollowerZone(ppFollowerData);
	}

	void Field::SetFollower(int index, Follower* pFollower)
	{
		m_pFollowers->SetFollower(index, pFollower);
	}

	void Field::DestroyDeadFollower(std::vector<Card*>* pCemetary)
	{
		m_pFollowers->DestroyDeadFollower(pCemetary);
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

	void Field::Followers::Initialized(bool isPropnentPrecedence)
	{
		//先行は頂点が二つなのでそうなるように回転させる
		m_fieldRotationNum = (isPropnentPrecedence) ? 0 : 1;
	}

	void Field::Followers::SetFollower(int index, Follower* pFollower)
	{
		m_followerDatas[index].m_pFollower = pFollower;
		m_followerDatas[index].m_isSummoned = true;
	}

	void Field::Followers::DestroyDeadFollower(std::vector<Card*>* pCemetary)
	{
		for (auto& followerData : m_followerDatas)
		{
			if (!followerData.m_pFollower) continue;

			if (followerData.m_pFollower->HP() > 0) continue;

			int index = static_cast<int>(&followerData - &m_followerDatas[0]);

			pCemetary->push_back(DestroyFollower(index));
		}
	}

	Card* Field::Followers::DestroyFollower(int index)
	{
		Card* retvalTmp = m_followerDatas[index].m_pFollower;

		m_followerDatas[index].m_pFollower = nullptr;

		EmptyFollower(index);

		return retvalTmp;
	}

	void Field::Followers::Circulation(bool isRightDirection)
	{
		m_fieldRotationNum += ((isRightDirection) ? +1 : -1);

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
		pHP->Damaged(m_followerDatas[originIndex].m_pFollower->Attack());
	}

	void Field::Followers::Update(PLAYER_KIND currentPlayerKind)
	{
		JudgeFollowersZone(currentPlayerKind);
	}

	void Field::Followers::Render()
	{
		CreateBackRects();

		for (auto& followerData : m_followerDatas)
		{
			//フォロワーが置かれていなかったら
			if (!followerData.m_pFollower)
			{
				followerData.m_pVertices->Render(nullptr);

				continue;
			}

			Vertices& rVertices = *followerData.m_pVertices;

			followerData.m_pFollower->Render(rVertices.GetCenter(), rVertices.GetSize());
		}
	}

	void Field::Followers::GetFollowerZone(FollowerData** ppFollowerData)
	{
		*ppFollowerData = m_followerDatas;
	}

	void Field::Followers::ActivateAbirity(int index)
	{
		//効果発動イベントディスパッチ
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
		if (m_followerDatas[originIndex].m_isSummoned ||
			m_followerDatas[originIndex].m_isAttacked ||
			m_followerDatas[originIndex].m_isMoved) return;

		if (m_followerDatas[destIndex].m_pFollower)
		{
			Attack(originIndex, destIndex);

			return;
		}

		auto Normalize = [&](int index)
		{
			return (index % (_countof(m_followerDatas)));
		};

		if (destIndex != Normalize(originIndex + 2) && destIndex != Normalize(originIndex + 3)) return;

		Move(originIndex, destIndex);
	}

	void Field::Followers::Attack(int originIndex, int destIndex)
	{
		(*m_followerDatas[destIndex].m_pFollower) -= m_followerDatas[originIndex].m_pFollower;

		m_followerDatas[originIndex].m_isAttacked = true;

		//攻撃イベントディスパッチ
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

	void Field::Followers::CreateBackRects()
	{
		//フィールドの中心からフォロワーを配置する位置のベクトル
		D3DXVECTOR3 posVecByCenter(0.0f, -m_windowSize.m_height * 0.25f, 0.0f);

		//回転されていた場合初期値をずらす
		gameframework::algorithm::D3DXVec3RotationZ(&posVecByCenter, ROTATION_DEGREE * m_fieldRotationNum);

		D3DXVECTOR3 windowCenter(m_windowCenter.x, m_windowCenter.y, posVecByCenter.z);

		RectSize cardSize;
		cardSize.m_height = 1.4f * (cardSize.m_width = m_windowSize.m_width * 0.03f);

		for (auto& followerData : m_followerDatas)
		{
			//フォロワーは72°ずつ回転して配置される
			gameframework::algorithm::D3DXVec3RotationZ(&posVecByCenter, 2.0f * ROTATION_DEGREE);

			followerData.m_pVertices->GetCenter() = windowCenter + posVecByCenter;

			followerData.m_pVertices->GetSize() = cardSize;
		}
	}

	void Field::Followers::JudgeFollowersZone(PLAYER_KIND currentPlayerKind)
	{
		const int FOLLOWERS_NUM = _countof(m_followerDatas);

		//相手のゾーンの配列番号の始まり
		int opponentZoneStartElementNum = (FOLLOWERS_NUM - 1 + m_fieldRotationNum / 2);

		opponentZoneStartElementNum %= FOLLOWERS_NUM;

		//2回転するたびに頂点を求めるための量が変わる
		int opponentZoneFollowersNum = (m_fieldRotationNum / 2) ? 3 : 2;

		for (auto& followerData : m_followerDatas)
		{
			int index = static_cast<int>(&followerData - &m_followerDatas[0]);

			followerData.m_isOpponentZone =
				(opponentZoneStartElementNum <= index && index <= opponentZoneStartElementNum + opponentZoneFollowersNum) ?
				true : false;

			if (currentPlayerKind == PLAYER_KIND::PROPONENT) continue;

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

		rEndButton.GetCenter() = { windowSize.m_width, windowSize.m_height * 0.5f, 0.008f };

		RectSize size;
		size.m_width = size.m_height = windowSize.m_width * 0.17f;
		rEndButton.GetSize() = size;

		rEndButton.SetColor(0xFF888888);
	}
} // namespace summonersaster
