#pragma once
#include "Scene/Scene.h"

#include "CardFolder.h"

namespace summonersaster
{
using namespace gameframework;

class CardShow :
	public Scene
{
public:
	/// <summary>
/// 初期化を行う
/// </summary>
	void Initialize()override;

	/// <summary>
	/// 終了処理を行う
	/// </summary>
	void Finalize()override;

	void LoadResources();

	/// <summary>
	/// 更新を行う
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画を行う
	/// </summary>
	void Render()override;
	void SwapCards();
private:
	Card* m_pCards[3];
	gameframework::Vertices* m_pRect = nullptr;
	gameframework::Vertices* m_pPolygon = nullptr;

};
}
