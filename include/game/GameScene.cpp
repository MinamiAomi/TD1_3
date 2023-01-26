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


#include "Model.h"
#include "Resource.h"

GameScene::GameScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana) :
	BaseScene(commonData, sceneMana) {
	world.Initalize();
}

GameScene::~GameScene() {}

void GameScene::Initalize()
{
	Block::zWidth(1);
	m_stage = std::make_unique<Stage>();
	m_stage->Initalize();
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
	m_stage->Update(m_player->positionXY());
	m_snowBall->Update();
	//m_test->Update();
	// “–‚½‚è”»’è

	m_player->PreCollision();
	m_stage->PreCollision();
	m_snowBall->PreCollision();

	std::vector<const Collider2D::OBB*> blocks;
	const Collider2D::Circle& player = m_snowBall->collider();

	for (auto& it : m_player->blocks()) {
		blocks.emplace_back(&it.collider());
	}
	for (auto& it : m_stage->blocks()) {
		blocks.emplace_back(&it->collider());
	}

	Vector2 closestPoint;
	for (auto& block : blocks) {
		if (Collision2D::Hit_Circle_OBB(player, *block, closestPoint)) {
			m_snowBall->OnCollision(closestPoint);
		}

	}


}

void GameScene::Draw3D()
{
	m_stage->Draw3D();
	m_snowBall->Draw();
	m_player->Draw();
	//m_test->Draw();

	Resource::GetInstance()->GetModel().axis->Draw(&world, m_player->camera());

}

void GameScene::Draw2D() {
	m_stage->Draw2D();
	if (Game::IsDebugMode()) {
		//	Sprite::Draw(debug.get(), m_commonData->camera2D.get());
	}
}

void GameScene::ChangeScene() 
{
	auto input = App::GetInstance()->GetInput();

	if (input->IsKeyTrigger(DIK_T)) {
		m_sceneMana->Transition<TitleScene>();
	}
}