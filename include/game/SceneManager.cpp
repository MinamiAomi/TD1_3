#include "SceneManager.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "Camera2D.h"

SceneManager* SceneManager::GetInstance() {
	static SceneManager instance;
	return &instance;
}

void SceneManager::Initalize()
{
	m_commonData = std::make_shared<SceneCommonData>();
	m_commonData->camera2D = std::make_unique<Camera2D>();
	m_commonData->camera2D->UpdateMatrix();

	Transition<TitleScene>();
}

void SceneManager::Update()
{
	m_scene->Update();
}

void SceneManager::Draw()
{
	m_scene->Draw3D();
	m_scene->Draw2D();
}

void SceneManager::ChangeScene()
{
	m_scene->ChangeScene();
}

