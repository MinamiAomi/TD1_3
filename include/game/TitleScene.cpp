#include "TitleScene.h"
#include "Engine.h"
#include "Input.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "GameScene.h"
#include "Resource.h"

TitleScene::TitleScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana) :
	BaseScene(commonData, sceneMana) 
{
}

TitleScene::~TitleScene() {}

void TitleScene::Initalize()
{
	test = std::make_unique<Sprite>(m_commonData->resource->GetImage().whiteImage, Vector2{ 0,0 }, Vector2{ 100,100 });
	test->SetColor(Color::ToVector4(0xFFFF00FF));
}

void TitleScene::Update()
{
	auto input = m_commonData->engine->GetInput();

	if (input->IsMouseTrigger(kMouseButtonLeft)) {
		m_sceneMana->Transition<GameScene>();
	}

}

void TitleScene::Draw()
{
	Sprite::Draw(test.get(), m_commonData->camera2D.get());
}
