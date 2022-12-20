#pragma once
#include "WinApp.h"
#include <memory>

class Game
{

private:
	class Engine* m_engine = nullptr;
	class Resource* m_resource = nullptr;
	std::unique_ptr<class SceneManager> m_sceneMana;
	bool m_isEditMode = false;

public:
	Game();
	~Game();
	bool Initalize();
	void Finalize();
	void Run();

};

