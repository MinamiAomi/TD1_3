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

TitleScene::~TitleScene() {
	delete t;
}

void TitleScene::Initalize()
{
	test = std::make_unique<Sprite>(Resource::GetInstance()->GetImage().whiteImage, Vector2{640,360}, Vector2{100,100});
	debug = std::make_unique<Sprite>(Resource::GetInstance()->GetImage().debugImage, Vector2{ 0,0 }, Vector2{ 200,100 });
	debug->SetTextureRect({ 0,0 }, { 128,64 });
	test->SetColor(Color::ToVector4(0xFFFF00FF));
	t = new Sprite;
	t->SetPosition({ 640,360 });
	t->SetSize({ 1280,720 });
	t->SetTextureHandle(Resource::GetInstance()->GetImage().TitleImage);
	t->SetTextureRect({ 0,0 }, { 1280, 720 });
	t->SetAnchorPoint(t->GetSize() * 0.5f);
	t->SetColor(Color::White);

	
}

void TitleScene::Update()
{
	

}

void TitleScene::Draw()
{
	//Sprite::Draw(test.get(), m_commonData->camera2D.get());

	if (Game::IsDebugMode()) {
		Sprite::Draw(debug.get(), m_commonData->camera2D.get());
	}

	Sprite::Draw(t, m_commonData->camera2D.get());
}

void TitleScene::ChangeScene()
{
	auto input = App::GetInstance()->GetInput();

	if (input->IsKeyTrigger(DIK_T)) {
		m_sceneMana->Transition<GameScene>();
	}
}