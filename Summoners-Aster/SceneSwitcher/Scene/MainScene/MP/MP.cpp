#include "MP.h"

namespace summonersaster
{
using namespace gameframework;

MP::MP(const D3DXVECTOR3& center) :m_Center(center)
{	
	for (auto& pVertices : m_pVertices)
	{
		GameFrameworkFactory::Create(&pVertices);
	}

	LocaleMP();

	GameFrameworkFactory::Create(&m_pStream);
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
	LocaleStream();

	DrawTexture(_T("MP_FRAME"));

	for (auto& pVertices : m_pVertices)
	{
		int index = static_cast<int>(&pVertices - &m_pVertices[0]);

		//現在のMPの最大値の範囲外
		if (m_Capacity - 1 < index)
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
	mPSize.m_width = mPSize.m_height = 150.0f;

	for (auto& pVertices : m_pVertices)
	{
		int index = static_cast<int>(&pVertices - &m_pVertices[0]);

		pVertices->SetSize(mPSize);
		pVertices->SetCenter(m_Center);
		pVertices->SetRotationZ((360.0f / MAX_CAPACITY) * index);
	}

	SetVertex(m_Center, mPSize, 0xFFFFFFFF);
}

void MP::LocaleStream()
{
	RectSize fontSize;
	m_rGameFramework.GetFontSize(_T("MP"), &fontSize);

	D3DXVECTOR2 topLeft(m_Center.x, m_Center.y - fontSize.m_height * 0.5f);
	m_pStream->SetTopLeft(topLeft);

	m_pStream->SetColor(0xFFFF6E00);
}

void MP::InitializeStream()
{
	(*m_pStream) = totstring(m_UsablePoint);
	*m_pStream += _T("/");
	(*m_pStream) += totstring(m_Capacity);
}
}
