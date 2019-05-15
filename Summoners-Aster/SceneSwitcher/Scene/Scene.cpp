#include "Scene.h"

namespace summonersaster
{
	Scene::~Scene()
	{

	}

	Scene::Scene()
	{

	}

	void Scene::CreateTexture(const TCHAR* pTextureKey, const TCHAR* pTexturePath)
	{
		m_pTextureKeys.push_back(pTextureKey);

		m_rGameFramework.CreateTexture(pTextureKey, pTexturePath);
	}

	void Scene::CreateFont(const TCHAR* pFontKey, const RectSize& fontSize, const TCHAR* pTexturePath)
	{
		m_pFontKeys.push_back(pFontKey);

		m_rGameFramework.CreateFont(pFontKey, fontSize, pTexturePath);
	}

	void Scene::ReleaseResources()
	{
		for (auto& pKey : m_pTextureKeys)
		{
			m_rGameFramework.ReleaseTexture(pKey);
		}

		for (auto& pFont : m_pFontKeys)
		{
			m_rGameFramework.ReleaseFont(pFont);
		}
	}
} // namespace summonersaster
