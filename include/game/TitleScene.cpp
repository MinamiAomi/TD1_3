#include "TitleScene.h"
#include "App.h"
#include "Input.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "GameScene.h"
#include "Resource.h"

#include "Game.h"

TitleScene::TitleScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana) :
	BaseScene(commonData, sceneMana) 
{
}

TitleScene::~TitleScene() {}

void TitleScene::Initalize()
{
	test = std::make_unique<Sprite>(m_commonData->resource->GetImage().whiteImage, Vector2{ 640,360 }, Vector2{ 100,100 });
	debug = std::make_unique<Sprite>(m_commonData->resource->GetImage().debugImage, Vector2{ 0,0 }, Vector2{ 200,100 });
	debug->SetTextureRect({ 0,0 }, { 128,64 });
	test->SetColor(Color::ToVector4(0xFFFF00FF));
}

void TitleScene::Update()
{
	

}

void TitleScene::Draw()
{
	Sprite::Draw(test.get(), m_commonData->camera2D.get());

	if (Game::IsDebugMode()) {
		Sprite::Draw(debug.get(), m_commonData->camera2D.get());
	}
}

void TitleScene::ChangeScene()
{
	auto input = m_commonData->engine->GetInput();

	if (input->IsKeyTrigger(DIK_T)) {
		m_sceneMana->Transition<GameScene>();
	}
}