#pragma once
#include "BaseScene.h"


class TitleScene :
    public BaseScene
{

private:

	std::unique_ptr<class Sprite> test;

public:
	TitleScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana);
	~TitleScene();

	void Initalize();
	void Update();
	void Draw();

};

