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
	test.reset(new Sprite);
}

TitleScene::~TitleScene() {}

void TitleScene::Initalize()
{
	m_commonData->resource->GetImage().whiteImage;
	test->SetPosition({ 0,0 });
	test->SetTextureHandle(0);
}

void TitleScene::Update()
{
	auto input = m_commonData->engine->GetInput();

	if (input->IsKeyTrigger(DIK_T)) {
		m_sceneMana->Transition<GameScene>();
	}

}

void TitleScene::Draw()
{
}
