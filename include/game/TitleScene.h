#pragma once
#include "BaseScene.h"

class TitleScene :
    public BaseScene
{


public:
	TitleScene(std::shared_ptr<SceneCommonData> commonData) : BaseScene(commonData) {
	}
	~TitleScene() {}

	void Initalize();
	void Update();
	void Draw();

};

