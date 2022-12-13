#include "SceneManager.h"
#include "BaseScene.h"

SceneManager::SceneManager() 
{

}

SceneManager::~SceneManager() 
{
}

void SceneManager::Initalize()
{
	m_commonData.reset(new SceneCommonData);
	Transition<class Title>();
}

void SceneManager::Update()
{
	m_scene->Update();
}

void SceneManager::Draw()
{
	m_scene->Draw();
}

