#pragma once
#include "BaseScene.h"

class GameScene :
	public BaseScene
{

private:


public:
	GameScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana);
	~GameScene();

	void Initalize();
	void Update();
	void Draw();

};

