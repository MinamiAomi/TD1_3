#pragma once
#include "WinApp.h"

struct WindowData {
	int windowWidth = 1280;
	int windowHight = 720;
	std::string windowTitle = "Title";
};

class App
{

private:
	WindowData m_windowData = {};

	class WinApp* m_winApp = nullptr;
	class DirectXCommon* m_dixCom = nullptr;
	class TextureManager* m_texMana = nullptr;
	class Input* m_input = nullptr;

public:
	static App* GetInstance();

	const WindowData& GetWindowData() const { return m_windowData; }
	WinApp* GetWinApp() { return m_winApp; }
	DirectXCommon* GetDirectXCommon() { return m_dixCom; }
	TextureManager* GetTextureManager() { return m_texMana; }
	Input* GetInput() { return m_input; }

	void Initalize(int windowWidth, int windowHeight, const std::string& windowTitle);
	void BeginFrame();
	void EndFrame();
	bool WindowQuit();
	void Finalize();

private:
	App() = default;
	~App() = default;
	App(const App&) = delete;
	const App& operator=(const App&) = delete;
};

