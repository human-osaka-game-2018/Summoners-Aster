#include "Card.h"

using namespace gameframework;

namespace summonersaster
{
	Card::~Card()
	{
		Finalize();
	}

	void Card::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);
		GameFrameworkFactory::Create(&m_pCostStream);
		LoadResource();
	}

	void Card::LoadResource()
	{
		m_rGameFramework.CreateTexture(pTEXTURE_KEY, m_texturePath.c_str());
	}

	void Card::Finalize()
	{
		Release();
	}

	void Card::Release()
	{
		delete m_pRect;
		delete m_pCostStream;
	}

	void Card::Update()
	{

	}

	void Card::Render(const D3DXVECTOR3& center, const RectSize& size, const Degree& rotationZ)
	{
		RenderCard(center, size, rotationZ);
	}

	Card::Card(TYPE type, const tstring& name, const tstring& texturePath, int cost, PLAYER_KIND owner)
		: CARD_TYPE(type), m_name(name), m_texturePath(texturePath), m_cost(cost), pTEXTURE_KEY(m_name.c_str()), m_owner(owner)
	{
		Initialize();
	}

	Card::Card(TYPE type, const tstring& name, const tstring& texturePath, int cost, PLAYER_KIND owner, const TCHAR* pTextureKey)
		: CARD_TYPE(type), m_name(name), m_texturePath(texturePath), m_cost(cost), pTEXTURE_KEY(pTextureKey), m_owner(owner)
	{
		Initialize();
	}

	void Card::RenderCard(const D3DXVECTOR3& center, const RectSize& size, const Degree& rotationZ)
	{
		m_pRect->GetCenter() = { center.x, center.y, center.z };
		m_pRect->SetSize(size);
		m_pRect->SetRotationZ(rotationZ);

		m_pRect->Render(m_rGameFramework.GetTexture(pTEXTURE_KEY));

		m_pRect->GetColor()[Color::COMPONENT::RED]	 = algorithm::Tertiary(m_owner == PLAYER_KIND::OPPONENT, 0x00, 0xFF);
		m_pRect->GetColor()[Color::COMPONENT::GREEN] = algorithm::Tertiary(m_owner == PLAYER_KIND::OPPONENT, 0x00, 0x00);
		m_pRect->GetColor()[Color::COMPONENT::BLUE]	 = algorithm::Tertiary(m_owner == PLAYER_KIND::OPPONENT, 0xFF, 0x00);
		m_pRect->Render(m_rGameFramework.GetTexture(_T("CARD_FRAME")));

		m_pRect->GetColor()[Color::COMPONENT::RED]   = 0xFF;
		m_pRect->GetColor()[Color::COMPONENT::GREEN] = 0xFF;
		m_pRect->GetColor()[Color::COMPONENT::BLUE]  = 0xFF;
		m_pRect->Render(m_rGameFramework.GetTexture(_T("COST")));
		if (-90.0f==rotationZ.Raw() ) return;

		if (m_isInCemetery) return;

		(*m_pCostStream) = totstring(m_cost);
		m_pCostStream->SetTopLeft(D3DXVECTOR2(center.x - size.m_width * 0.37f, center.y - size.m_height * 0.475f));
		m_pCostStream->Render(m_rGameFramework.GetFont(_T("CARD")), DT_CENTER);
	}
} // namespace summonersaster
