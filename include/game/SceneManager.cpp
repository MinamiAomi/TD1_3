#include "SceneManager.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "Camera2D.h"
#include "Fead.h"

SceneManager* SceneManager::GetInstance() {
	static SceneManager instance;
	return &instance;
}

void SceneManager::Initalize()
{
	m_commonData = std::make_shared<SceneCommonData>();
	m_commonData->camera2D = std::make_unique<Camera2D>();
	m_commonData->camera2D->UpdateMatrix();
	m_fead = std::make_unique<Fead>();
	m_fead->Initalize();

	Transition<TitleScene>();
}

void SceneManager::Update()
{
	if (m_fead->isActive()) {
		m_fead->Update();
	}
	else {
		m_scene->Update();
	}
}

void SceneManager::Draw()
{
	m_scene->Draw3D();
	m_scene->Draw2D();
	if (m_fead->isActive()) {
		m_fead->Draw();
	}
}

void SceneManager::ChangeScene()
{
	if (!m_fead->isActive()) {
		m_scene->ChangeScene();
	}
}

void SceneManager::ChangeStart(SceneId scene)
{
	m_fead->StartFeadOut(scene);
}

