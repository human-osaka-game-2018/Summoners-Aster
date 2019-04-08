#include "MainScene.h"

namespace summonersaster
{
	MainScene::MainScene()
	{

	}

	MainScene::~MainScene()
	{

	}

	void MainScene::Initialize()
	{
		
	}

	void MainScene::Finalize()
	{
		
	}

	void MainScene::Update()
	{
		m_rStepSwitcher.Update();
	}

	void MainScene::Render()
	{
		m_rStepSwitcher.Render();
	}

} // namespace summonersaster
