#include "GameScene.h"
#include "App.h"
#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Resource.h"
#include "Stage.h"

#include "Game.h"
#include "Sprite.h"

GameScene::GameScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana) :
	BaseScene(commonData, sceneMana) {
}

GameScene::~GameScene() {}

void GameScene::Initalize()
{
	m_curStage.reset(new Stage());
	m_curStage->Initalize(0);

	debug = std::make_unique<Sprite>(m_commonData->resource->GetImage().debugImage, Vector2{ 0,0 }, Vector2{ 200,100 });
	debug->SetTextureRect({ 0,0 }, { 128,64 });
}

void GameScene::Update()
{

	m_curStage->Update();
}

void GameScene::Draw()
{
	m_curStage->Draw();

	if (Game::IsDebugMode()) {
		Sprite::Draw(debug.get(), m_commonData->camera2D.get());
	}
}

void GameScene::ChangeScene() 
{
	auto input = m_commonData->engine->GetInput();

	if (input->IsKeyTrigger(DIK_T)) {
		m_sceneMana->Transition<TitleScene>();
	}
}