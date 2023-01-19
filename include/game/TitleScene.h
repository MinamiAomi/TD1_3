#pragma once
#include "BaseScene.h"

class TitleScene :
    public BaseScene
{

private:
	// �e�X�g�p�X�v���C�g��`��
	std::unique_ptr<class Sprite> test;
	class Sprite* t = nullptr;
	std::unique_ptr<class Sprite> debug;

public:
	TitleScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana);
	~TitleScene();

	void Initalize();
	void Update();
	void Draw();
	void ChangeScene();
};

