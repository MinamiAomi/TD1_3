#pragma once
#include "WinApp.h"

class Game
{

private:
	class Engine* m_engine = nullptr;
	class SceneManager* m_sceneMana = nullptr;

public:
	Game();
	~Game();
	bool Initalize();
	void Finalize();
	void Run();

};

