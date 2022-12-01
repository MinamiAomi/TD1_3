#include "Game.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Input.h"
#include "Sprite.h"
#include <cassert>

Game::Game()
{}
Game::~Game()
{}
bool Game::Initalize(){

	m_winApp = WinApp::GetInstance();
	m_winApp->Initialize(m_windowWidth, m_windowHeight, "á‹Ê“]‚ª‚µ");

	m_dixCom = DirectXCommon::GetInstance();
	m_dixCom->Initialize(m_winApp);

	m_texMana = TextureManager::GetInstance();
	m_texMana->Initialize(m_dixCom);

	m_input = Input::GetInstance();
	m_input->Initialize(m_winApp);

	Sprite::StaticInitalize(m_dixCom, m_texMana, m_windowWidth, m_windowHeight);
	
	assert(m_winApp != nullptr);
	assert(m_dixCom != nullptr);
	assert(m_texMana != nullptr);
	assert(m_input != nullptr);

	return true;
}

void Game::Finalize() 
{
	m_winApp->Finalize();
}

void Game::Run() 
{
	GameLoop();
}

void Game::GameLoop()
{
	while (m_winApp->WindowQUit() == false) {
		BeginFrame();

		

		EndFrame();
	}
}

void Game::BeginFrame()
{
	m_dixCom->PreDraw();
	m_input->Update();
}

void Game::EndFrame()
{
	m_dixCom->PostDraw();
}
