#pragma once
#include "BaseScene.h"

class TitleScene :
    public BaseScene
{

private:
	// テスト用スプライトを描画
	std::unique_ptr<class Sprite> test;
	class Sprite* t = nullptr;
	std::unique_ptr<class Sprite> pushA;
	float theta = 0.0f;

public:
	TitleScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana);
	~TitleScene();

	void Initalize();
	void Update();
	void Draw3D();
	void Draw2D();
	void ChangeScene();
};

