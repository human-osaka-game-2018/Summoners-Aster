#include "ObjectIntegrator.h"

#include <algorithm>

namespace summonersaster
{
	ObjectIntegrator::ObjectIntegrator()
	{

	}

	ObjectIntegrator::~ObjectIntegrator()
	{
		Release();
	}

	void ObjectIntegrator::ReloadResources()
	{
		for (auto& pObject : m_pObjects)
		{
			pObject->LoadResource();
		}
	}

	void ObjectIntegrator::Update()
	{
		for (auto pObject : m_pObjects)
		{
			pObject->Update();
		}
	}

	void ObjectIntegrator::Render()
	{
		std::sort(m_pObjects.begin(), m_pObjects.end(), IsFarther);

		for (auto pObject : m_pObjects)
		{
			pObject->Render();
		}
	}

	void ObjectIntegrator::Register(Object* pObject)
	{
		if (!pObject) return;

		m_pObjects.push_back(pObject);
	}

	void ObjectIntegrator::Release()
	{
		for (auto pObject : m_pObjects)
		{
			delete pObject;
		}

		//要素数を0にする
		m_pObjects.clear();
		//キャパシティを要素数と同じにする
		m_pObjects.shrink_to_fit();
	}

	bool ObjectIntegrator::IsFarther(const Object* pCompares, const Object* pCompared)
	{
		return (pCompares->GetZ() > pCompared->GetZ());
	}
} // namespace summonersaster
