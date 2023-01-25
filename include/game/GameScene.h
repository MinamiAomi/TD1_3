#pragma once
#include "BaseScene.h"
#include <memory>

#include "WorldTransform.h"

class GameScene :
	public BaseScene
{

private:
	std::unique_ptr<class Stage> m_stage;	// 現在のステージ
	std::unique_ptr<class SnowBall> m_snowBall; //　雪玉
	std::unique_ptr<class Player> m_player;	// プレイヤー
//	std::unique_ptr<class TestObj> m_test;
	std::unique_ptr<class Sprite> debug;
	
	WorldTransform world;

public:
	GameScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana);
	~GameScene();

	void Initalize();
	void Update();
	void Draw3D();
	void Draw2D();
	void ChangeScene();
};

