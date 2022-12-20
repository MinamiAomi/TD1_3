#pragma once
#include "BaseScene.h"

class GameScene :
	public BaseScene
{

private:
	unsigned int m_curStageNumber = 0;	// ���݂̃X�e�[�W
	std::unique_ptr<class Stage> m_curStage;	// ���݂̃X�e�[�W

public:
	GameScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana);
	~GameScene();

	void Initalize();
	void Update();
	void Draw();
	void ChangeScene();
};

