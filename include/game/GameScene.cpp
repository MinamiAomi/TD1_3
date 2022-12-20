#include "GameScene.h"
#include "Engine.h"
#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Resource.h"
#include "Stage.h"

GameScene::GameScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana) :
	BaseScene(commonData, sceneMana) {
}

GameScene::~GameScene() {}

void GameScene::Initalize()
{
	m_curStage.reset(new Stage());
	m_curStage->Initalize(0);
}

void GameScene::Update()
{

	m_curStage->Update();
}

void GameScene::Draw()
{
	m_curStage->Draw();
}

void GameScene::ChangeScene() 
{
	auto input = m_commonData->engine->GetInput();

	if (input->IsMouseTrigger(kMouseButtonLeft)) {
		m_sceneMana->Transition<TitleScene>();
	}
}