#include "SceneManager.h"
#include "BaseScene.h"
#include "TitleScene.h"

SceneManager::SceneManager() 
{

}

SceneManager::~SceneManager() 
{
}

void SceneManager::Initalize(class Engine* engine, class Resource* resource)
{
	m_commonData.reset(new SceneCommonData);
	Transition<TitleScene>();
	m_commonData->engine = engine;
	m_commonData->resource = resource;
}

void SceneManager::Update()
{
	m_scene->Update();
}

void SceneManager::Draw()
{
	m_scene->Draw();
}

