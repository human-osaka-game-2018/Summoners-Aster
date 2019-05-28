#include "Weapon.h"

namespace summonersaster
{
	using namespace gameframework;

	Weapon::Weapon(const tstring& name, const tstring& texturePath, int cost, int hitPoint, std::vector<Ability> abilities)
		: Card(TYPE::WEAPON, name, texturePath, cost, abilities), m_hP(hitPoint)
	{
		gameframework::GameFrameworkFactory::Create(&m_pHPStream);
	}

	Weapon::Weapon(const tstring& name, const tstring& texturePath, int cost, int hitPoint, PLAYER_KIND owner, const TCHAR* pTextureKey, std::vector<Ability> abilities)
		: Card(TYPE::WEAPON, name, texturePath, cost, owner, pTextureKey, abilities), m_hP(hitPoint)
	{
		gameframework::GameFrameworkFactory::Create(&m_pHPStream);
	}

	Weapon::~Weapon()
	{
	}

	void Weapon::CreateCopy(Card** ppCard, PLAYER_KIND owner)const
	{
		*ppCard = new Weapon(m_name, m_texturePath, m_cost, m_hP, owner, pTEXTURE_KEY, m_abilities);
	}

	void Weapon::Render(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType, const Degree& rotationZ)
	{
		if (RenderCard(center, size, renderingType, rotationZ)) return;
		RenderHP(center, size, renderingType);
	}

	void Weapon::RenderHP(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType)
	{
		m_pRect->Render(m_rGameFramework.GetTexture(_T("HP")));
		m_pHPStream->SetTopLeft(D3DXVECTOR2(center.x - size.m_width * 0.377f, center.y + size.m_height * 0.345f));

		if (m_isInCemetery) return;

		int hPForRendering = algorithm::Tertiary(m_hP < 0, 0, m_hP);

		(*m_pHPStream) = totstring(hPForRendering);
		SetStreamColor(m_pHPStream);
		m_pHPStream->Render(m_rGameFramework.GetFont(FontName(renderingType)), DT_CENTER);
	}

} // namespace summonersaster
