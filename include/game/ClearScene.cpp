#include "ClearScene.h"
#include "App.h"
#include "Input.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "GameScene.h"
#include "Resources.h"
#include"TitleScene.h"

#include "Game.h"

ClearScene::ClearScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana) :
	BaseScene(commonData, sceneMana)
{
}

ClearScene::~ClearScene() {
	delete clear_bg;
	delete head;
}

void ClearScene::Initalize()
{
	test = std::make_unique<Sprite>(Resource::GetInstance()->GetImage().whiteImage, Vector2{ 640,360 }, Vector2{ 100,100 });
	debug = std::make_unique<Sprite>(Resource::GetInstance()->GetImage().debugImage, Vector2{ 0,0 }, Vector2{ 200,100 });
	debug->SetTextureRect({ 0,0 }, { 128,64 });
	test->SetColor(Color::ToVector4(0xFFFF00FF));
	clear_bg = new Sprite;
	clear_bg->SetPosition({ 640,360 });
	clear_bg->SetSize({ 1280,720 });
	clear_bg->SetTextureHandle(Resource::GetInstance()->GetImage().ClearImage);
	clear_bg->SetTextureRect({ 0,0 }, { 1280, 720 });
	clear_bg->SetAnchorPoint(clear_bg->GetSize() * 0.5f);
	clear_bg->SetColor(Color::White);

	head = new Sprite;
	head->SetPosition({ 600,250 });
	head->SetSize({ 500,500 });
	head->SetTextureHandle(Resource::GetInstance()->GetImage().HeadImage);
	head->SetTextureRect({ 0,0 }, { 500, 500 });
	head->SetAnchorPoint(head->GetSize() * 0.5f);
	head->SetColor(Color::White);

}

void ClearScene::Update()
{
	

}

void ClearScene::Draw3D()
{
}

void ClearScene::Draw2D()
{
	//Sprite::Draw(test.get(), m_commonData->camera2D.get());

	//if (Game::IsDebugMode()) {
	//	Sprite::Draw(debug.get(), m_commonData->camera2D.get());
	//}

	Sprite::Draw(clear_bg, m_commonData->camera2D.get());
	//Sprite::Draw(head, m_commonData->camera2D.get());
}

void ClearScene::ChangeScene()
{
	auto input = App::GetInstance()->GetInput();

	if (input->IsKeyTrigger(DIK_SPACE) || input->IsPadButtonTrigger(0,kPadButtonA)) {
		m_sceneMana->ChangeStart(kSceneIdTitle);
	}
}