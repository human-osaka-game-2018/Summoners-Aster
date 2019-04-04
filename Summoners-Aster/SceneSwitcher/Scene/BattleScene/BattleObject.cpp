#include "BattleObject.h"

using namespace gameframework;
namespace summonersaster
{

BattleObject::BattleObject()
{
	GameFrameworkFactory::Create(&m_pRect);
	GameFrameworkFactory::Create(&m_pStream);
}

BattleObject::~BattleObject()
{
	delete m_pRect;
	delete m_pStream;
}

void BattleObject::SetVertex(const D3DXVECTOR3& center, const RectSize& size, const Color& color)
{
	m_pRect->SetCenterAndSizeAndColor(center, size, color);
}

void BattleObject::SetVertex(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs)
{
	m_pRect->SetCenterAndSizeAndColorAndTextureUVs(center, size, color,textureUVs);
}

void BattleObject::DrowTexture(const TCHAR* pTextureKey)
{
	m_pRect->Render(m_rGameFramework.GetTexture(pTextureKey));
}

void BattleObject::WriteWords(D3DXVECTOR2 topLeft, const TCHAR* fontKey, int format)
{
	m_pStream->SetTopLeft(topLeft);
	m_pStream->Render(m_rGameFramework.GetFont(fontKey), format);
}

void BattleObject::WriteWords(const D3DXVECTOR2 topLeft, const TCHAR* fontKey, int format, const gameframework::Color& color)
{
	m_pStream->SetTopLeft(topLeft);
	m_pStream->SetColor(color);
	m_pStream->Render(m_rGameFramework.GetFont(fontKey), format);
}

void BattleObject::SetString(const TCHAR* words)
{
	const tstring& str = words;
	(*m_pStream) = str;

}
}
