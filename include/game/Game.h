#pragma once
#include "WinApp.h"
#include <memory>

class Game
{

private:
	class App* m_app = nullptr;
	class Resource* m_resource = nullptr;
	std::unique_ptr<class SceneManager> m_sceneMana;
	
	static bool m_isDebugMode;

public:
	Game();
	~Game();
	bool Initalize();
	void Finalize();
	void Run();

};

