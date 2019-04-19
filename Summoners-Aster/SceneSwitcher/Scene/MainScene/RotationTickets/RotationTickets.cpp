#include "RotationTickets.h"

namespace summonersaster
{
	using namespace gameframework;

	RotationTickets::RotationTickets(int retentionMax)
		:Object(0.08f), RETENTION_MAX(retentionMax)
	{
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

		m_rGameFramework.ReleaseTexture(_T("ROTATION_TICKET"));
	}

	void RotationTickets::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("ROTATION_TICKET"), _T("Textures/Battle_rotationTicket.png"));
	}

	void RotationTickets::Render()
	{
		D3DXVECTOR3 baseCenter(m_windowCenter.x * 0.9f, m_windowCenter.y * 1.75f, m_z);

		RectSize size;
		size.m_width = size.m_height = m_windowSize.m_width * 0.02f;

		for (auto& pVertices : m_pVertices)
		{
			int index = static_cast<int>(&pVertices - &m_pVertices[0]);

			if (index >= m_retentionNum)
			{
				pVertices->SetColor(0xFF666666);
			}

			D3DXVECTOR3 center(baseCenter.x + m_windowSize.m_width * 0.01f * index, baseCenter.y, baseCenter.z);
			pVertices->SetCenterAndSize(center, size);

			pVertices->Render(m_rGameFramework.GetTexture(_T("ROTATION_TICKET")));
		}
	}
}
