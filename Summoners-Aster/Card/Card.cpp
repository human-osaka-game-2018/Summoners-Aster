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
		GameFrameworkFactory::Create(&m_pNameStream);

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
		delete m_pNameStream;
	}

	void Card::Update()
	{

	}

	void Card::Render(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType, const Degree& rotationZ)
	{
		RenderCard(center, size, renderingType, rotationZ);
	}

	Card::Card(TYPE type, const tstring& name, const tstring& texturePath, int cost, std::vector<Ability> abilities)
		: CARD_TYPE(type), m_name(name), m_texturePath(texturePath), m_cost(cost), pTEXTURE_KEY(m_name.c_str()),
		m_owner(PLAYER_KIND::PROPONENT)
	{
		for (int abilityNum = 0; abilityNum < abilities.size(); ++abilityNum)
		{
			Ability ability((abilities[abilityNum].activationEvent), (abilities[abilityNum].execute));
			m_abilities.push_back(ability);
		}

		Initialize();
	}

	Card::Card(TYPE type, const tstring& name, const tstring& texturePath, int cost, PLAYER_KIND owner, const TCHAR* pTextureKey, std::vector<Ability> pAbilities)
		: CARD_TYPE(type), m_name(name), m_texturePath(texturePath), m_cost(cost), pTEXTURE_KEY(pTextureKey), m_owner(owner)
	{
		for (int abilityNum = 0; abilityNum < pAbilities.size(); ++abilityNum)
		{
			Ability ability((pAbilities[abilityNum].activationEvent),(pAbilities[abilityNum].execute));
			m_abilities.push_back(ability);
		}

		Initialize();
	}

	bool Card::RenderCard(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType, const Degree& rotationZ)
	{
		m_pRect->GetCenter() = { center.x, center.y, center.z };
		m_pRect->SetSize(size);
		m_pRect->SetRotationZ(rotationZ);

		m_pRect->Render(m_rGameFramework.GetTexture(pTEXTURE_KEY));

		if (renderingType == Card::RENDERING_TYPE::REVERSE)
		{
			m_pRect->Render(m_rGameFramework.GetTexture(_T("CARD_BACK")));

			return true;
		}

		m_pRect->GetColor()[Color::COMPONENT::RED]	 = algorithm::Tertiary(m_owner == PLAYER_KIND::OPPONENT, 0xDD, 0xFF);
		m_pRect->GetColor()[Color::COMPONENT::GREEN] = algorithm::Tertiary(m_owner == PLAYER_KIND::OPPONENT, 0xDD, 0xFF);
		m_pRect->GetColor()[Color::COMPONENT::BLUE]	 = algorithm::Tertiary(m_owner == PLAYER_KIND::OPPONENT, 0xDD, 0xFF);
		m_pRect->Render(m_rGameFramework.GetTexture(_T("CARD_FRAME")));

		m_pRect->GetColor()[Color::COMPONENT::RED]   = 0xFF;
		m_pRect->GetColor()[Color::COMPONENT::GREEN] = 0xFF;
		m_pRect->GetColor()[Color::COMPONENT::BLUE]  = 0xFF;
		m_pRect->Render(m_rGameFramework.GetTexture(_T("COST")));
		if (-90.0f==rotationZ.Raw() ) return false;

		if (m_isInCemetery) return false;

		(*m_pCostStream) = totstring(m_cost);
		m_pCostStream->SetTopLeft(D3DXVECTOR2(center.x - size.m_width * 0.366f, center.y - size.m_height * 0.452f));
		SetStreamColor(m_pCostStream);
		m_pCostStream->Render(m_rGameFramework.GetFont(FontName(renderingType)), DT_CENTER);

		*m_pNameStream = m_name;
		m_pNameStream->SetTopLeft(D3DXVECTOR2(center.x, center.y - size.m_height * 0.465f));
		SetStreamColor(m_pNameStream);
		m_pNameStream->Render(m_rGameFramework.GetFont(NameFontName(renderingType)), DT_CENTER);

		return false;
	}

	const TCHAR* Card::FontName(RENDERING_TYPE renderingType)
	{
		switch (renderingType)
		{
		case RENDERING_TYPE::SMALL:
			return _T("CARD_S");

		case RENDERING_TYPE::MIDDLE:
			return _T("CARD_M");

		case Card::RENDERING_TYPE::LARGE:
			return _T("CARD_L");

		case Card::RENDERING_TYPE::REVERSE:
			return _T("CARD_M");
		}

		return _T("CARD_M");
	}

	const TCHAR* Card::NameFontName(RENDERING_TYPE renderingType)
	{
		switch (renderingType)
		{
		case RENDERING_TYPE::SMALL:
			return _T("NAME_S");

		case RENDERING_TYPE::MIDDLE:
			return _T("NAME_M");

		case Card::RENDERING_TYPE::LARGE:
			return _T("NAME_L");

		case Card::RENDERING_TYPE::REVERSE:
			return _T("NAME_M");
		}

		return _T("NAME_M");
	}

	void Card::SetStreamColor(Stream* pStream)
	{
		Color streamColor = 0xFFFFFFFF;
		streamColor[Color::COMPONENT::ALPHA] = m_pRect->GetColor()[Color::COMPONENT::ALPHA];

		pStream->SetColor(streamColor);
	}
} // namespace summonersaster
