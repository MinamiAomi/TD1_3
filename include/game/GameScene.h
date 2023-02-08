#pragma once
#include "BaseScene.h"
#include <memory>
#include <vector>

#include "WorldTransform.h"
#include "CameraTransform.h"

class GameScene :
	public BaseScene
{

private:
	int m_frame = 0;

	CameraTransform m_camera;
	std::unique_ptr<class Ground> m_ground;
	std::unique_ptr<class Ball> m_ball;
	std::unique_ptr<class Map> m_map;
//	std::unique_ptr<class Stage> m_stage;	// 現在のステージ
//	std::unique_ptr<class SnowBall> m_snowBall; //　雪玉
//	std::unique_ptr<class Player> m_player;	// プレイヤー
//	std::unique_ptr<class TestObj> m_test;
	int m_stickTexNum = 0;
	std::unique_ptr<class Sprite> m_stick;
	
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

