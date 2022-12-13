#pragma once
#include "WinApp.h"
#include <memory>

class Game
{

private:
	class Engine* m_engine = nullptr;
	std::unique_ptr<class SceneManager> m_sceneMana;

public:
	Game();
	~Game();
	bool Initalize();
	void Finalize();
	void Run();

};

