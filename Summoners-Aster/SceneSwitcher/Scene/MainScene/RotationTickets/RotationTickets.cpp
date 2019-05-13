#include "RotationTickets.h"

namespace summonersaster
{
	using namespace gameframework;

	RotationTickets::RotationTickets(const D3DXVECTOR2& baseCenterWindowMulti)
		:Object(0.9001f)
	{
		m_baseCenter = 
		{ 
			m_windowCenter.x * baseCenterWindowMulti.x,  
			m_windowCenter.y * baseCenterWindowMulti.y,
			m_z 
		};

		Initialize();
		LoadResource();
	}

	RotationTickets::~RotationTickets()
	{
		Finalize();
	}

	void RotationTickets::Initialize()
	{
		m_retentionNum = RETENTION_MAX;

		GameFrameworkFactory::Create(&m_pVertices);
	}

	void RotationTickets::Finalize()
	{
		delete m_pVertices;
	}

	void RotationTickets::LoadResource()
	{

	}

	void RotationTickets::Render()
	{
		RectSize size;
		size.m_width = size.m_height = 150.0f;
		
		D3DXVECTOR3 center(m_baseCenter.x, m_baseCenter.y, m_baseCenter.z);
		m_pVertices->SetCenterAndSize(center, size);

		const TCHAR* pTEXTURE_KEYS[RETENTION_MAX + 1] =
		{
			_T("ROTATION_TICKET_FRAME"),
			_T("ROTATION_TICKET1"),
			_T("ROTATION_TICKET2"),
			_T("ROTATION_TICKET3")
		};

		m_pVertices->SetColor(0xFFFFFFFF);

		m_pVertices->Render(m_rGameFramework.GetTexture(pTEXTURE_KEYS[0]));

		for (int i = 0; i < RETENTION_MAX; ++i)
		{
			m_pVertices->SetColor(algorithm::Tertiary(i < m_retentionNum, 0xFFFFFFFF, 0xFF333333));

			m_pVertices->Render(m_rGameFramework.GetTexture(pTEXTURE_KEYS[i + 1]));
		}
	}
}
