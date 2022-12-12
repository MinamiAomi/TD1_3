#include "Engine.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Input.h"
#include "Sprite.h"
#include "Model.h"
#include <cassert>

Engine* Engine::GetInstance()
{
    static Engine instance;
    return &instance;
}

void Engine::Initalize(int windowWidth, int windowHeight, const std::string& windowTitle)
{
	m_windowData = { windowWidth,windowHeight,windowTitle };

	m_winApp = WinApp::GetInstance();
	m_winApp->Initialize(windowWidth, windowHeight, windowTitle);

	m_dixCom = DirectXCommon::GetInstance();
	m_dixCom->Initialize(m_winApp);

	m_texMana = TextureManager::GetInstance();
	m_texMana->Initialize(m_dixCom);

	m_input = Input::GetInstance();
	m_input->Initialize(m_winApp);

	Sprite::StaticInitalize(m_dixCom, m_texMana, windowWidth, windowHeight);

	Model::StaticInitalize(m_dixCom, m_texMana);

	assert(m_winApp != nullptr);
	assert(m_dixCom != nullptr);
	assert(m_texMana != nullptr);
	assert(m_input != nullptr);
}

void Engine::BeginFrame()
{
	m_dixCom->PreDraw();
	m_input->Update();
}

void Engine::EndFrame()
{
	m_dixCom->PostDraw();
}

bool Engine::WindowQuit()
{
	return m_winApp->WindowQuit();
}

void Engine::Finalize()
{
	m_winApp->Finalize();
}
