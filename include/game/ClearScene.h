#pragma once
#include "BaseScene.h"

class ClearScene :
	public BaseScene
{

private:
	// �e�X�g�p�X�v���C�g��`��
	std::unique_ptr<class Sprite> test;
	class Sprite* clear_bg = nullptr;
	class Sprite* head = nullptr;
	std::unique_ptr<class Sprite> debug;

public:
	ClearScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana);
	~ClearScene();

	void Initalize();
	void Update();
	void Draw3D();
	void Draw2D();
	void ChangeScene();
};

