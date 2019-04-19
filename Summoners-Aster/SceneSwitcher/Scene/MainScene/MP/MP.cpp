#include "MP.h"

namespace summonersaster
{
using namespace gameframework;

MP::MP()
{
	m_rGameFramework.CreateTexture(_T("MP_FRAME"), _T("Textures/Battle_mPFrame.png"));
	m_rGameFramework.CreateTexture(_T("MP"), _T("Textures/Battle_mP.png"));

	RectSize fontSize;
	fontSize.m_height = 2.0f * (fontSize.m_width = 18.0f);

	m_rGameFramework.CreateFont(_T("MP"), fontSize, _T("IPAex明朝"));

	for (auto& pVertices : m_pVertices)
	{
		GameFrameworkFactory::Create(&pVertices);
	}

	LocaleMP();

	GameFrameworkFactory::Create(&m_pStream);
	LocaleStream();
}

MP::~MP()
{
	for (auto& pVertices : m_pVertices)
	{
		delete pVertices;
	}
}

void MP::Render()
{
	DrawTexture(_T("MP_FRAME"));

	for (auto& pVertices : m_pVertices)
	{
		int index = static_cast<int>(&pVertices - &m_pVertices[0]);

		//現在のMPの最大値の範囲外
		if (m_Capacity < index)
		{
			pVertices->SetColor(0xFF333333);
		}

		//使用済みのMP
		if (m_UsablePoint - 1 < index && index < m_Capacity)
		{
			pVertices->SetColor(0xFF888888);
		}

		//残っているMP
		if (index < m_UsablePoint)
		{
			pVertices->SetColor(0xFFFFFFFF);
		}

		pVertices->Render(m_rGameFramework.GetTexture(_T("MP")));
	}
	
	InitializeStream();
	m_pStream->Render(m_rGameFramework.GetFont(_T("MP")), DT_CENTER);
}

void MP::IncreaseCapacity()
{
	if (m_Capacity == MAX_CAPACITY) return;
	++m_Capacity;
}

bool MP::Paid(const int paidMp)
{
	if (paidMp > m_UsablePoint) return false;
	m_UsablePoint -= paidMp;
	return true;
}

void MP::RenewUsablePoints()
{
	m_UsablePoint = m_Capacity;
}

void MP::LocaleMP()
{
	RectSize mPSize;
	mPSize.m_width = mPSize.m_height = 190.0f;

	for (auto& pVertices : m_pVertices)
	{
		int index = static_cast<int>(&pVertices - &m_pVertices[0]);

		pVertices->SetSize(mPSize);
		pVertices->SetCenter(m_center);
		pVertices->SetRotationZ((360.0f / MAX_CAPACITY) * index);
	}

	SetVertex(m_center, mPSize, 0xFFFFFFFF);
}

void MP::LocaleStream()
{
	RectSize fontSize;
	m_rGameFramework.GetFontSize(_T("MP"), &fontSize);

	D3DXVECTOR2 topLeft(m_center.x, m_center.y - fontSize.m_height * 0.5f);
	m_pStream->SetTopLeft(topLeft);

	m_pStream->SetColor(0xFFFF6E00);
}

void MP::InitializeStream()
{
	TCHAR retentionTmp[3];
	_itot_s(m_UsablePoint, retentionTmp, _countof(retentionTmp), 10);

	*m_pStream = retentionTmp;

	*m_pStream += _T("/");

	_itot_s(m_Capacity, retentionTmp, _countof(retentionTmp), 10);
	*m_pStream += retentionTmp;
}
}
