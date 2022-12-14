#include "Game.h"
#include "TextureManager.h"
#include "Engine.h"
#include "Resource.h"
#include "Sprite.h"
#include "Model.h"
#include "SceneManager.h"
#include <cassert>

Game::Game()
{}
Game::~Game()
{}
bool Game::Initalize(){

	const int windowWidth = 1280;
	const int windowHight = 720;
	const std::string windowTitle = "á‹Ê“]‚ª‚µ";

	m_engine = Engine::GetInstance();
	m_engine->Initalize(windowWidth, windowHight, windowTitle);
	

	m_resource = Resource::GetInstance();
	m_resource->Initalize(m_engine->GetTextureManager());

	m_sceneMana = std::make_unique<SceneManager>();
	m_sceneMana->Initalize(m_engine, m_resource);

	return true;
}

void Game::Finalize() 
{
}

void Game::Run() 
{
	while (m_engine->WindowQuit() == false) {
		m_engine->BeginFrame();

		m_sceneMana->Update();
		m_sceneMana->Draw();

		m_engine->EndFrame();
	}
}

