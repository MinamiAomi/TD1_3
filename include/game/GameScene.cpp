#include "GameScene.h"
#include "App.h"
#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Resource.h"
#include "Stage.h"
#include "Player.h"
#include "SnowBall.h"
#include "Game.h"
#include "Sprite.h"
#include "TestObj.h"

GameScene::GameScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana) :
	BaseScene(commonData, sceneMana) {
}

GameScene::~GameScene() {}

void GameScene::Initalize()
{
	Block::zWidth(1);
	m_stage = std::make_unique<Stage>();
	m_stage->Initalize(0);
	m_player = std::make_unique<Player>();
	m_player->Initalize();
	m_snowBall = std::make_unique<SnowBall>();
	m_snowBall->Initalize();
	Block::camera(m_player->camera());
	m_snowBall->camera(m_player->camera());
	//m_test = std::make_unique<TestObj>();
	//m_test->Initalize();

	//debug = std::make_unique<Sprite>(m_commonData->resource->GetImage().debugImage, Vector2{ 0,0 }, Vector2{ 200,100 });
	//debug->SetTextureRect({ 0,0 }, { 128,64 });
}

void GameScene::Update()
{
	m_player->Update();
	m_stage->Update();
	m_snowBall->Update();
	//m_test->Update();
	// “–‚½‚è”»’è


}

void GameScene::Draw()
{
	m_stage->Draw();
	m_snowBall->Draw();
	m_player->Draw();
	//m_test->Draw();

	if (Game::IsDebugMode()) {
		Sprite::Draw(debug.get(), m_commonData->camera2D.get());
	}
}

void GameScene::ChangeScene() 
{
	auto input = App::GetInstance()->GetInput();

	if (input->IsKeyTrigger(DIK_T)) {
		m_sceneMana->Transition<TitleScene>();
	}
}