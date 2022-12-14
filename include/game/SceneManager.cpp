#include "SceneManager.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "Camera2D.h"

SceneManager::SceneManager() 
{

}

SceneManager::~SceneManager() 
{
}

void SceneManager::Initalize(class Engine* engine, class Resource* resource)
{
	m_commonData = std::make_shared<SceneCommonData>();
	m_commonData->engine = engine;
	m_commonData->resource = resource;
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
	m_scene->Draw();
}

