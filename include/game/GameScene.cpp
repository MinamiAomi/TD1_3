#include "GameScene.h"
#include "App.h"
#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "ClearScene.h"
#include "Resources.h"
#include "Game.h"
#include "Sprite.h"
#include "Item.h"
#include "Goal.h"
#include "Model.h"
#include <utility>

#include "Ground.h"
#include "Map.h"
#include "Wall.h"
#include "Ball.h"
#include "ClearItem.h"

GameScene::GameScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana) :
	BaseScene(commonData, sceneMana) {
	world.Initalize();
}

GameScene::~GameScene() {}

void GameScene::Initalize()
{
	m_frame = 0;

	m_camera.Initalize();
	m_camera.position = { 0.0f,25.0f,-20.0f };
	m_camera.target = { 0.0f,0.0f,0.0f };
	Wall::camera(&m_camera);
	m_ground = std::make_unique<Ground>();
	m_ground->Initalize();
	m_ball = std::make_unique<Ball>();
	m_ball->Initalize();
	m_ball->parent(m_ground->world());
	m_map = std::make_unique<Map>();
	m_map->Initalize(m_ground->world(), &m_camera);
	
	m_stickTexNum = 0;
	m_stick = Sprite::Create(Resource::GetInstance()->GetImage().stickImage, { 0.0f,720 - 100 }, { 100.0f,100.0f });
	m_stick->SetTextureRect({ 0.0f,0.0f }, { 64.0f,64.0f });
	m_camera.UpdateMatrix();
}

void GameScene::Update()
{
	m_frame++;
	if (m_frame % 20 == 0) {
		m_stickTexNum++;
		if (m_stickTexNum >= 4) {
			m_stickTexNum = 0;
		}
	}

	auto input = Input::GetInstance();


	m_ground->Update();

	m_map->Update();
	m_ball->normal(m_ground->normal());
	m_ball->Update();
	
	Vector2 closestPoint;
	for (auto& wall : m_map->walls()) {
		if (Collision2D::Hit_Circle_OBB(m_ball->collider(), wall->collider(), closestPoint)) {
			m_ball->OnCollisionWall(closestPoint);
		}
	}
	for (auto& item : m_map->items()) {
		if (item->isGet() == false) {
			if (Collision2D::Hit_Circle_Circle(m_ball->collider(), item->collider())) {
				m_ball->OnCollisionItem(item->type());
				item->OnCollision();
			}
		}
	}
	if (m_ball->isCanGoal() == true) {
		if (Collision2D::Hit_Circle_Circle(m_ball->collider(), m_map->goal()->collider())) {
			m_map->goal()->OnCollision();
		}
	}
	m_camera.UpdateMatrix();
}

void GameScene::Draw3D()
{
	m_camera.UpdateMatrix();

	m_ground->Draw(&m_camera);
	m_map->Draw();
	m_ball->Draw(&m_camera);
}

void GameScene::Draw2D() {
//	m_stage->Draw2D();
	if (Game::IsDebugMode()) {
		//	Sprite::Draw(debug.get(), m_commonData->camera2D.get());
	}
	m_stick->SetTextureRect({ m_stickTexNum * 64.0f,0.0f }, { 64.0f,64.0f });
	Sprite::Draw(m_stick.get(), m_commonData->camera2D.get());

}

void GameScene::ChangeScene() 
{
	auto input = App::GetInstance()->GetInput();

	if (input->IsKeyTrigger(DIK_T)) {
		m_sceneMana->ChangeStart(kSceneIdTitle);
		return;
	}
	if (m_map->goal()->isClear() == true) {
		m_sceneMana->ChangeStart(kSceneIdClear);
		return;
	}
//	if (m_snowBall->isGameOver() == true) {
//		m_sceneMana->Transition<GameScene>();
//		return;
//	}
}