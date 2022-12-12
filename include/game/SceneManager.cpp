#include "SceneManager.h"
#include "BaseScene.h"

SceneManager::SceneManager(class Game* game) : 
	GameObject(game) 
{

}

SceneManager::~SceneManager() 
{
}

void SceneManager::Init()
{
	Transition<class Title>();
	m_commonData.reset(new SceneCommonData);
}

void SceneManager::Update()
{
	m_scene->Update();
}

void SceneManager::Draw()
{
	m_scene->Draw();
}

