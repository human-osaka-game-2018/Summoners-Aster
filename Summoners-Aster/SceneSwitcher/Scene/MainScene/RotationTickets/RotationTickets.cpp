#include "RotationTickets.h"

namespace summonersaster
{
	using namespace gameframework;

	RotationTickets::RotationTickets(int retentionMax, const D3DXVECTOR2& baseCenterWindowMulti)
		:Object(0.08f), RETENTION_MAX(retentionMax)
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

		m_pVertices.resize(RETENTION_MAX);

		for (auto& pVertices : m_pVertices)
		{
			GameFrameworkFactory::Create(&pVertices);
		}
	}

	void RotationTickets::Finalize()
	{
		for (auto& pVertices : m_pVertices)
		{
			delete pVertices;
		}
	}

	void RotationTickets::LoadResource()
	{

	}

	void RotationTickets::Render()
	{
		RectSize size;
		size.m_width = size.m_height = m_windowSize.m_width * 0.02f;

		for (auto& pVertices : m_pVertices)
		{
			int index = static_cast<int>(&pVertices - &m_pVertices[0]);

			if (index >= m_retentionNum)
			{
				pVertices->SetColor(0xFF666666);
			}

			D3DXVECTOR3 center(m_baseCenter.x + m_windowSize.m_width * 0.01f * index, m_baseCenter.y, m_baseCenter.z);
			pVertices->SetCenterAndSize(center, size);

			pVertices->Render(m_rGameFramework.GetTexture(_T("ROTATION_TICKET")));
		}
	}
}
