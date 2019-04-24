#include "HP.h"

using namespace gameframework;

namespace summonersaster
{
HP::HP(const D3DXVECTOR2& m_TexturCenter):m_Center(m_TexturCenter)
{
}

HP::~HP()
{
}

void HP::Render()
{
	m_rGameFramework.GetFontSize(_T("MP"), &m_PolygonSize);

	D3DXVECTOR2 topLeft(m_Center.x + m_PolygonSize.m_width * 3.0f, m_Center.y - m_PolygonSize.m_height * 2.0f);

	SetVertex(D3DXVECTOR3(topLeft.x + (m_PolygonSize.m_width * 3.8f),
		topLeft.y - (m_PolygonSize.m_height * 3.5f), 0.88f), m_PolygonSize * 10, 0xFF999999);

	(*m_pStream) = totstring(m_Hp);

	Color color = 0xFFB0D7ED;
	if (m_Hp <= MAX_CAPACITY * 0.5f)
	{
		color = 0xFFF5BB00;
	}

	if (m_Hp == 0) 
	{
		color = 0xFFFF0000;
	}
	DrawTexture(_T("HP"));
	WriteWords(topLeft, _T("MP"), DT_CENTER, color);
}

void HP::Damaged(unsigned int damage)
{
	if (m_Hp < damage)
	{
		m_Hp = 0;
	}
	else m_Hp -= damage;
	if (m_Hp < 0) 
	{
		m_Hp = 0;
		//死亡通知を流す
	}
}

void HP::Recover(unsigned int heal)
{
	m_Hp += heal;
	if (m_Hp > MAX_CAPACITY) 
	{
		m_Hp = MAX_CAPACITY;
	}
}
}
