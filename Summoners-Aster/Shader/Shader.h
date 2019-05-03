#ifndef SHADER_H

#include <GameFramework.h>

#include <d3dx9.h>

namespace summonersaster
{
	using gameframework::Singleton;
	using gameframework::LPDIRECT3DDEVICE;
	using gameframework::DirectXParam;
	using gameframework::LPTEXTURE;
	using gameframework::Vertices;

	class Shader :public Singleton<Shader>
	{
	public:
		friend Singleton<Shader>;

		~Shader()
		{
			Finalize();
		}

		void Render(Vertices* pVertices, LPTEXTURE pTexture)
		{
			D3DXVECTOR4 color;
			color.x = 1.0f;
			color.y = 1.0f;
			color.z = 1.0f;
			color.w = 1.0f;

			m_pDirectXGraphicDevice->SetVertexDeclaration(m_pVertexFormatDeclaration);

			m_pShader->SetTechnique(m_pTechnique);
			m_pShader->SetVector(m_pColor, &color); 
			m_pShader->CommitChanges();

			m_pShader->Begin(0, 0);
			m_pShader->BeginPass(0);

			pVertices->Render(pTexture);

			m_pShader->EndPass();
			m_pShader->End();
		}

	private:
		enum VERTEX_COMPONENT
		{
			POSITION,
			COLOR,
			TEXTURE_UV,
			MAX
		};

		Shader()
		{
			Initialize();
		}

		void Initialize()
		{
			DirectXParam::GetDirectXGraphicDevice()->Get(&m_pDirectXGraphicDevice);

			D3DVERTEXELEMENT9 vertexFormat[MAX + 1];
			CreateVertexElement(vertexFormat);
			
			m_pDirectXGraphicDevice->CreateVertexDeclaration(vertexFormat, &m_pVertexFormatDeclaration);

			if (!LoadShader())
			{
				MessageBox(
					0,
					_T("アプリケーションを終了します"),
					_T("シェーダファイルを読み込むことができませんでした"),
					MB_OK | MB_ICONERROR);

				PostQuitMessage(0);

				return;
			}

			m_pTechnique = m_pShader->GetTechniqueByName("StandardDraw");
			m_pMatrix	 = m_pShader->GetParameterByName(nullptr, "g_blendingMatrix");
			m_pColor	 = m_pShader->GetParameterByName(nullptr, "g_color");
			m_pTexture	 = m_pShader->GetParameterByName(nullptr, "g_texture");
		}

		void Finalize()
		{
			if (!m_pShader)
			{
				m_pShader->Release();
			}
		}

		void CreateVertexElement(D3DVERTEXELEMENT9* pVertexElement)
		{
			pVertexElement[POSITION]	= { 0, 0,
				D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 };

			pVertexElement[COLOR]		= { 0, pVertexElement[POSITION].Offset + sizeof(D3DXVECTOR3) + sizeof(float),
				D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 };

			pVertexElement[TEXTURE_UV]	= { 0, pVertexElement[COLOR].Offset + sizeof(DWORD),
				D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 };

			pVertexElement[MAX]			= D3DDECL_END();
		}

		bool LoadShader()
		{
			LPD3DXBUFFER error = nullptr;
			D3DXCreateEffectFromFile(m_pDirectXGraphicDevice,
				_T("Shader/CustomAdditionShader.hlsl"),
				0,
				0,
				D3DXSHADER_DEBUG,
				0,
				&m_pShader,
				&error);

			if (m_pShader) return true;

			return false;
		}

		LPDIRECT3DVERTEXDECLARATION9 m_pVertexFormatDeclaration = nullptr;
		LPD3DXEFFECT m_pShader	= nullptr;
		D3DXHANDLE m_pTechnique = nullptr;
		D3DXHANDLE m_pMatrix	= nullptr;
		D3DXHANDLE m_pColor		= nullptr;
		D3DXHANDLE m_pTexture	= nullptr;

		LPDIRECT3DDEVICE m_pDirectXGraphicDevice = nullptr;
	};
}// namespace summonersaster

#endif // !SHADER_H
