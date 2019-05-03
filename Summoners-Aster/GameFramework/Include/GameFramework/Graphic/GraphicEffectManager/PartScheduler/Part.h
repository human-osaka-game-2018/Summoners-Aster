#ifndef PART_H
#define PART_H

#include <tchar.h>

#include "../../../Vertices.h"
#include "../../Texture.h"
#include "../../TextureManager.h"
#include "../../ColorBlender.h"
#include "../BehaviorScheduler/BehaviorScheduler.h"
#include "../BehaviorScheduler/Behavior.h"
#include "../BehaviorScheduler/ColorChange.h"
#include "../BehaviorScheduler/Diffuse.h"
#include "../BehaviorScheduler/Flash.h"
#include "../BehaviorScheduler/FollowUpCursor.h"
#include "../BehaviorScheduler/RotationZ.h"
#include "../BehaviorScheduler/Scaling.h"
#include "../BehaviorScheduler/Locale.h"
#include "../Shape/Shape.h"
#include "../Shape/SizeDifferenceSquare.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	using BehaviorData = BehaviorScheduler::NodeData;

	/// <summary>
	/// エフェクトを構成するパーツクラス
	/// </summary>
	class Part
	{
	public:
		virtual ~Part();

		/// <remarks>
		/// Graphicクラスで入れる
		/// </remarks>
		static void SetGraphicHelper(ColorBlender* pColorBlender, TextureManager* pTextureManager);
		
		/// <summary>
		/// 矩形を変形させたりする
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="isAdditionBlendMode">加算合成を行うか</param>
		virtual void Render(bool isAdditionBlendMode);

		inline bool IsEnd()const
		{
			return m_isEnd;
		}

		/// <summary>
		/// 画像などの読み込み
		/// </summary>
		void LoadResource();

	protected:
		Part(const Part& part) = delete;

		explicit Part(const TCHAR* pTexturePath);

		Part& operator=(const Part& part) = delete;

		void Initialize();

		void Finalize();

		void Release();

		void UpdateVertices();

		int m_lifeFrame = 0;
		bool m_isEnd = false;

		const TCHAR* TEXTURE_KEY;
		Vertices* m_pVertices = nullptr;

		static ColorBlender* m_pColorBlender;
		static TextureManager* m_pTextureManager;
		BehaviorScheduler m_behaviorScheduler;
	};
}

#endif //!PART_H
