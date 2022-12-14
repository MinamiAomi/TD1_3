#pragma once
#include "BaseScene.h"

class GameScene :
	public BaseScene
{


public:
	GameScene(std::shared_ptr<SceneCommonData> commonData) : BaseScene(commonData) {
	}
	~GameScene() {}

	void Initalize();
	void Update();
	void Draw();

};

