#include "TitleScene.h"
#include "App.h"
#include "Input.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "GameScene.h"
#include "Resources.h"
#include "ClearScene.h"

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
	pushA = std::make_unique<Sprite>(Resource::GetInstance()->GetImage().pushAImage, Vector2{ 640,560 }, Vector2{ 24 * 10,8 * 10 });
	pushA->SetTextureRect({ 0,0 }, { 96,32 });
	pushA->SetSize(Vector2{ 24 * 10,8 * 10 });
	pushA->SetAnchorPoint(pushA->GetSize() * 0.5f);
	test->SetColor(Color::ToVector4(0xFFFF00FF));
	t = new Sprite;
	t->SetPosition({ 640,360 });
	t->SetSize({ 1280,720 });
	t->SetTextureHandle(Resource::GetInstance()->GetImage().TitleImage);
	t->SetTextureRect({ 0,0 }, { 1280, 720 });
	t->SetAnchorPoint(t->GetSize() * 0.5f);
	t->SetColor(Color::White);

	theta = 0.0f;
}

void TitleScene::Update()
{
	theta += Math::ToRadians(1.0f);
	Vector2 pos = pushA->GetPosition();
	pushA->SetPosition({ pos.x,pos.y + cosf(theta) * 0.5f });
}

void TitleScene::Draw3D()
{
}

void TitleScene::Draw2D()
{
	//Sprite::Draw(test.get(), m_commonData->camera2D.get());



	Sprite::Draw(t, m_commonData->camera2D.get());
	Sprite::Draw(pushA.get(), m_commonData->camera2D.get());
}

void TitleScene::ChangeScene()
{
	auto input = App::GetInstance()->GetInput();

	if (input->IsKeyTrigger(DIK_SPACE) || input->IsPadButtonTrigger(0, kPadButtonA)) {
		m_sceneMana->ChangeStart(kSceneIdMain);
	}
}