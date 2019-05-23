#include "Scene.h"

#include <thread>

#include "Cursor.h"
#include "ClickEffect.h"
#include "HoldEffect.h"

namespace summonersaster
{
	using namespace gameframework;
	bool Scene::isLoadEnd = false;

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

	void Scene::Load()
	{
		isLoadEnd = false;

		Stream* pStream = nullptr;
		Vertices* pRect = nullptr;
		Vertices* pBGRect = nullptr;
		GameFrameworkFactory::Create(&pRect);
		GameFrameworkFactory::Create(&pBGRect);
		m_rGameFramework.CreateTexture(_T("LOADSTAR"), _T("Textures/SummonCircle.png"));
		m_rGameFramework.CreateTexture(_T("BACK"), _T("Textures/HomeBack.png"));

		Cursor cursor;
		int frameCount = 0;


		GameFrameworkFactory::Create(&pStream);
		(*pStream) = _T("Now Loading");
		m_rGameFramework.CreateFont(_T("Load"), RectSize(50,70), _T("IPAex明朝"));

		std::thread subThread([this] {return LoadResources(); });
		while (!isLoadEnd)
		{
			if (!m_rGameFramework.CanStartNextFrame()) continue;
			
			m_rGameFramework.PrepareInFrame();

			pBGRect->GetCenter() = { 800, 450, 1.0f };
			pBGRect->SetSize(RectSize(1600, 900));
			pBGRect->Render(m_rGameFramework.GetTexture(_T("BACK")));

			LoadAnimation(pStream, pRect);
			MouseEffecter(&frameCount);
			m_rGameFramework.UpdateGraphicEffects();
			m_rGameFramework.RenderGraphicEffects();

			cursor.Update();
			cursor.Render();
			m_rGameFramework.FinishInFrame();


		}

		subThread.join();

		m_rGameFramework.ReleaseTexture(_T("LOADSTAR"));
		m_rGameFramework.ReleaseTexture(_T("BACK"));
		m_rGameFramework.ReleaseFont(_T("Load"));

		delete pStream;
		delete pRect;
	}

	void Scene::LoadAnimation(Stream* pStream, Vertices* pRect)
	{
		OutputDebugString(L"ロード中\n");
		static float deg = 0;
		deg += 1.0f;
		pRect->GetCenter() = { 1500,800 ,0};
		pRect->SetSize(RectSize(200,200));
		pRect->SetRotationZ(deg);
		pRect->Render(m_rGameFramework.GetTexture(_T("LOADSTAR")));


		pStream->SetTopLeft(D3DXVECTOR2(1000, 800));
		pStream->Flash(60, 40, 255);

		pStream->Render(m_rGameFramework.GetFont(_T("Load")), DT_CENTER);

	}

	void Scene::MouseEffecter(int* frameCount) {
		if (m_rGameFramework.MouseIsPressed(DirectX8Mouse::DIM_LEFT))
		{
			m_rGameFramework.RegisterGraphicEffect(new ClickEffect());
		}

		if (m_rGameFramework.MouseIsHeld(DirectX8Mouse::DIM_LEFT) && !((++*frameCount) % 3))
		{
			POINT cursorPoint = { 0, 0 };
			m_rGameFramework.CursorPos(&cursorPoint);
			D3DXVECTOR3 cursorPos(static_cast<float>(cursorPoint.x), static_cast<float>(cursorPoint.y), 0.0f);
			//rGameFramework.RegisterGraphicEffect(new SummonEffect(cursorPos));

			m_rGameFramework.RegisterGraphicEffect(new HoldEffect());
		}

	}
} // namespace summonersaster
