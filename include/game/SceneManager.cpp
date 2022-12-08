#include "SceneManager.h"
#include "BaseScene.h"

SceneManager* SceneManager::GetInstance() 
{
	static SceneManager instance;
	return &instance;
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	m_scene->Update();
}

void SceneManager::Draw()
{
	m_scene->Draw();
}

