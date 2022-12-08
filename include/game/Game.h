#pragma once
#include "WinApp.h"

class Game
{

private:
	const unsigned int m_windowWidth = 1280; // �E�B���h�E��
	const unsigned int m_windowHeight = 720; // �E�B���h�E��

	class WinApp* m_winApp = nullptr;
	class DirectXCommon* m_dixCom = nullptr;
	class TextureManager* m_texMana = nullptr;
	class Input* m_input = nullptr;
	class SceneManager* m_sceneMana = nullptr;

public:
	Game();
	~Game();
	bool Initalize();
	void Finalize();
	void Run();

private:
	void GameLoop();
	void BeginFrame();
	void EndFrame();
};

