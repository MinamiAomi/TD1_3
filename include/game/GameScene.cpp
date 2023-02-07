#include "GameScene.h"
#include "App.h"
#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "ClearScene.h"
#include "Resource.h"
#include "Stage.h"
#include "Player.h"
#include "SnowBall.h"
#include "Game.h"
#include "Sprite.h"
#include "TestObj.h"
#include "Item.h"
#include "Goal.h"
#include "Model.h"
#include "Resource.h"
#include <utility>

#include "Ground.h"
#include "Wall.h"

GameScene::GameScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana) :
	BaseScene(commonData, sceneMana) {
	world.Initalize();
}

GameScene::~GameScene() {}

void GameScene::Initalize()
{
	m_camera.Initalize();
	m_camera.position = { 0.0f,20.0f,-30.0f };
	m_camera.target = { 0.0f,0.0f,0.0f };
	Wall::camera(&m_camera);
	m_ground = std::make_unique<Ground>();
	m_ground->Initalize();
	for (auto& it : m_walls) {
		it = std::make_unique<Wall>();
		it->parent(m_ground->world());
	}
	float width = 0.5f;
	float dist = 2.5f;
	m_walls[0]->position({-10.0f,2.0f,0.0f});
	m_walls[1]->position({ 10.0f,2.0f,0.0f });
	m_walls[2]->position({ 0.0f,2.0f,10.0f });
	m_walls[3]->position({ 0.0f,2.0f,-10.0f });
	m_walls[0]->scale({ 1.0f,1.0f,11.0f });
	m_walls[1]->scale({ 1.0f,1.0f,11.0f });
	m_walls[2]->scale({ 9.0f,1.0f,1.0f });
	m_walls[3]->scale({ 9.0f,1.0f,1.0f });
//	Block::zWidth(1);
//	m_stage = std::make_unique<Stage>();
//	m_stage->Initalize();
//	m_player = std::make_unique<Player>();
//	m_player->Initalize();
//	m_snowBall = std::make_unique<SnowBall>();
//	m_snowBall->Initalize();
//	Block::camera(m_player->camera());
//	Item::camera(m_player->camera());
//	Goal::camera(m_player->camera());
//	m_stage->camera(m_player->camera());
//	m_snowBall->camera(m_player->camera());
	//m_test = std::make_unique<TestObj>();
	//m_test->Initalize();

	//debug = std::make_unique<Sprite>(m_commonData->resource->GetImage().debugImage, Vector2{ 0,0 }, Vector2{ 200,100 });
	//debug->SetTextureRect({ 0,0 }, { 128,64 });
}

void GameScene::Update()
{
//	m_player->Update();
//	m_stage->Update(m_player->positionXY());
//	m_snowBall->Update();
	//m_test->Update();
	// “–‚½‚è”»’è

//	m_player->PreCollision();
//	m_stage->PreCollision();
//	m_snowBall->PreCollision();

//	std::vector<std::pair<Block::Type,const Collider2D::OBB*>> blocks;
//	const Collider2D::Circle& player = m_snowBall->collider();
//	
//	for (auto& it : m_player->blocks()) {
//		blocks.push_back({ it.typeId(), &it.collider() });
//	}
//	for (auto& it : m_stage->blocks()) {
//		blocks.push_back({ it->typeId(), &it->collider() });
//	}
//	
//
//	Vector2 closestPoint;
//	for (auto& block : blocks) {
//		if (Collision2D::Hit_Circle_OBB(player, *block.second, closestPoint)) {
//			m_snowBall->OnCollisionBlock(closestPoint,block.first);
//		}
//	}
//	for (auto& item : m_stage->items()) {
//		if (item->isGet() == false) {
//			if (Collision2D::Hit_Circle_Circle(player, item->collider())) {
//				m_snowBall->OnCollisionItem(item->typeId());
//				item->OnCollision();
//
//			}
//		}
//	}
//
//	if (m_snowBall->canGoal() == true) {
//		if (Collision2D::Hit_Circle_OBB(player, m_stage->goal()->collider(), closestPoint)) {
//			m_snowBall->OnCollisionGoal();
//			m_stage->goal()->OnCollision();
//		}
//	}

	auto input = Input::GetInstance();


	m_ground->Update();

	for (auto& it : m_walls) {
		it->Update();
	}

	m_camera.UpdateMatrix();
}

void GameScene::Draw3D()
{
//	m_stage->Draw3D();
//	m_snowBall->Draw();
//	m_player->Draw();
	//m_test->Draw();

//	Resource::GetInstance()->GetModel().axis->Draw(&world, m_player->camera());

	m_ground->Draw(&m_camera);
	for (auto& it : m_walls) {
		it->Draw();
	}
}

void GameScene::Draw2D() {
//	m_stage->Draw2D();
	if (Game::IsDebugMode()) {
		//	Sprite::Draw(debug.get(), m_commonData->camera2D.get());
	}
}

void GameScene::ChangeScene() 
{
	auto input = App::GetInstance()->GetInput();

	if (input->IsKeyTrigger(DIK_T)) {
		m_sceneMana->Transition<TitleScene>();
		return;
	}
//	if (m_snowBall->isGameClear() == true) {
//		m_sceneMana->Transition<ClearScene>();
//		return;
//	}
//	if (m_snowBall->isGameOver() == true) {
//		m_sceneMana->Transition<GameScene>();
//		return;
//	}
}