#pragma once
#include "BaseScene.h"
#include <memory>

class GameScene :
	public BaseScene
{

private:
	unsigned int m_curStageNumber = 0;	// 現在のステージ
	std::unique_ptr<class Stage> m_curStage;	// 現在のステージ

	std::unique_ptr<class Sprite> debug;

public:
	GameScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana);
	~GameScene();

	void Initalize();
	void Update();
	void Draw();
	void ChangeScene();
};

