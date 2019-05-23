#ifndef SCENE_H
#define SCENE_H

#include <tchar.h>
#include <vector>

#include <GameFramework.h>

#include "KindBase.h"
#include "BattleEnums.h"

namespace summonersaster
{
	using gameframework::GameFramework;
	using gameframework::RectSize;

	/// <summary>
	/// シーンの基底クラス
	/// </summary>
	class Scene :public KindBase
	{
	public:
		virtual ~Scene();

		void LoadTexture()
		{
			
		}

	protected:
		Scene();

		void CreateTexture(const TCHAR* pTextureKey, const TCHAR* pTexturePath);

		void CreateFont(const TCHAR* pFontKey, const RectSize& fontSize, const TCHAR* pTexturePath);

		void ReleaseResources();

		virtual void LoadResources() {};


		void Load();

		void LoadAnimation(gameframework::Stream* pStream, gameframework::Vertices* pRect);

		void MouseEffecter(int* frameCount);

		std::vector<const TCHAR*> m_pTextureKeys;
		std::vector<const TCHAR*> m_pFontKeys;
		static bool isLoadEnd;
		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();
	};
} // namespace summonersaster

#endif //!SCENE_H
