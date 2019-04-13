#include "Field.h"

using namespace gameframework;

namespace summonersaster
{
	FollowerData::FollowerData()
	{
		GameFrameworkFactory::Create(&m_pVertices);
		m_pVertices->SetColor(0xFF444444);
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
	}

	Field::~Field()
	{

	}

	void Field::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("FIELD"), _T("Texture/Battle_star.png"));
	}

	void Field::Initialize(bool isPropnentPrecedence)
	{
		GameFrameworkFactory::Create(&m_pVertices);
		LocaleField();

		m_pFollowers = new Followers(isPropnentPrecedence);

		LoadResource();
	}

	void Field::Finalize()
	{
		delete m_pVertices;
		delete m_pFollowers;

		m_rGameFramework.ReleaseTexture(_T("FIELD"));
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
		m_pVertices->SetRotationZ(m_pFollowers->ROTATION_DEGREE * m_rotationNum);
		m_pVertices->Render(m_rGameFramework.GetTexture(_T("FIELD")));
		m_pFollowers->Render();
	}

	void Field::GetFollowerZone(FollowerData** ppFollowerData)
	{
		m_pFollowers->GetFollowerZone(ppFollowerData);
	}

	void Field::SetFollower(int index, Card* pFollower)
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

	Field::Followers::Followers(bool isPropnentPrecedence)
	{
		gameframework::WindowParam::GetWindowSize(&m_windowSize);

		m_windowCenter.x = m_windowSize.m_width  * 0.5f;
		m_windowCenter.y = m_windowSize.m_height * 0.5f;

		//先行は頂点が二つなのでそうなるように回転させる
		m_fieldRotationNum = (isPropnentPrecedence) ? 0 : 1;
	}

	Field::Followers::~Followers()
	{

	}

	void Field::Followers::SetFollower(int index, Card* pFollower)
	{
		m_followerDatas[index].m_pFollower = pFollower;
		m_followerDatas[index].m_isSummoned = true;
	}

	void Field::Followers::DestroyDeadFollower(std::vector<Card*>* pCemetary)
	{
		for (auto& followerData : m_followerDatas)
		{
			if (!followerData.m_pFollower) continue;

			//if (followerData.m_pFollower->GetHP() > 0) continue;

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
		//*pHP -= *m_followerDatas[originIndex].m_pFollower;
	}

	void Field::Followers::Update(PLAYER_KIND currentPlayerKind)
	{
		JudgeFollowersZone(currentPlayerKind);
	}

	void Field::Followers::Render()
	{
		CreateBackRects();
		SetFollowerPos();

		for (auto& followerData : m_followerDatas)
		{
			//フォロワーが置かれていなかったら
			if (!followerData.m_pFollower)
			{
				followerData.m_pVertices->Render(nullptr);

				continue;
			}

			//followerData.m_pFollower->Render();
		}
	}

	void Field::Followers::GetFollowerZone(FollowerData** ppFollowerData)
	{
		*ppFollowerData = m_followerDatas;
	}

	void Field::Followers::ActivateAbirity(int index)
	{
		//m_followerDatas[index].m_pFollower->ActivateAbirity();
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
			return (index % (sizeof(m_followerDatas) / sizeof(FollowerData))); 
		};

		if (destIndex != Normalize(originIndex + 2) || destIndex != Normalize(originIndex + 3)) return;

		Move(originIndex, destIndex);
	}

	void Field::Followers::Attack(int originIndex, int destIndex)
	{
		//m_followerDatas[destIndex].m_pFollower - m_followerDatas[originIndex].m_pFollower;

		m_followerDatas[originIndex].m_isAttacked = true;

		//攻撃イベントディスパッチ
	}

	void Field::Followers::Move(int originIndex, int destIndex)
	{
		EmptyFollower(destIndex);

		m_followerDatas[destIndex] = m_followerDatas[originIndex];

		m_followerDatas[destIndex].m_isMoved = true;

		EmptyFollower(originIndex);

		//移動イベントディスパッチ
	}

	void Field::Followers::CreateBackRects()
	{
		//フィールドの中心からフォロワーを配置する位置のベクトル
		D3DXVECTOR3 posVecByCenter(0.0f, -m_windowSize.m_height * 0.3f, 0.0f);

		//回転されていた場合初期値をずらす
		gameframework::algorithm::D3DXVec3RotationZ(&posVecByCenter, ROTATION_DEGREE * m_fieldRotationNum);

		D3DXVECTOR3 windowCenter(m_windowCenter.x, m_windowCenter.y, posVecByCenter.z);

		RectSize cardSize;
		cardSize.m_height = 1.4f * (cardSize.m_width = m_windowSize.m_width * 0.02f);

		for (auto& followerData : m_followerDatas)
		{
			//フォロワーは36°ずつ回転して配置される
			gameframework::algorithm::D3DXVec3RotationZ(&posVecByCenter, ROTATION_DEGREE);

			followerData.m_pVertices->GetCenter() = windowCenter + posVecByCenter;

			followerData.m_pVertices->GetSize() = cardSize;
		}
	}

	void Field::Followers::SetFollowerPos()
	{
		for (auto& followerData : m_followerDatas)
		{
			if (!followerData.m_pFollower) continue;

			//followerData.m_pFollower->GetVertices() = followerData.m_pVertices;
		}
	}

	void Field::Followers::JudgeFollowersZone(PLAYER_KIND currentPlayerKind)
	{
		const int FOLLOWERS_NUM = sizeof(m_followerDatas) / sizeof(FollowerData);

		//相手のゾーンの配列番号の始まり
		int opponentZoneStartElementNum = (FOLLOWERS_NUM - 1 + m_fieldRotationNum / 2);

		opponentZoneStartElementNum %= FOLLOWERS_NUM;

		//回転するたびに頂点の量が変わる
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

	void Field::LocaleField()
	{
		m_pVertices->GetCenter() = { m_windowCenter.x, m_windowCenter.y, 0.0f };

		RectSize size;
		size.m_width = size.m_height = m_windowSize.m_width * 0.33f;
		m_pVertices->GetSize() = size;
	}
} // namespace summonersaster
