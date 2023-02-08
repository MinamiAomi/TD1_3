#include "Game.h"
#include "TextureManager.h"
#include "App.h"
#include "Input.h"
#include "Resources.h"
#include "Sprite.h"
#include "Model.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include <cassert>
#include "Stage.h"
#include "Block.h"

#include "Map.h"
#include "Wall.h"
#include "Cube.h"

bool Game::m_isDebugMode = false;

Game::Game()
{}
Game::~Game()
{}
bool Game::Initalize(){

	const int windowWidth = 1280;
	const int windowHight = 720;
	const std::string windowTitle = "á‹Ê“]‚ª‚µ";

	m_app = App::GetInstance();
	m_app->Initalize(windowWidth, windowHight, windowTitle);
	m_app->GetDirectXCommon()->SetClearColor(Color::ToVector4(0x3399AAFF));

	m_resource = Resource::GetInstance();
	m_resource->Initalize(m_app->GetTextureManager());

	m_sceneMana = SceneManager::GetInstance();
	m_sceneMana->Initalize();

	Block::StaticInitalize();
	Cube::GetInstance();
	Wall::StaticInitalize();
	//Stage::LoadJson();
	Map::LoadJson();

	return true;
}

void Game::Finalize() 
{
	//Stage::SaveJson();
	Map::SaveJson();
}

void Game::Run() 
{
	while (m_app->WindowQuit() == false) {
		m_app->BeginFrame();
		TimeManager::GetInstance()->Update();
		if (m_app->GetInput()->IsKeyTrigger(DIK_TAB)) {
			m_isDebugMode ^= true;
		}

		m_sceneMana->ChangeScene();
		m_sceneMana->Update();
		m_sceneMana->Draw();

		m_app->EndFrame();
	}
}

