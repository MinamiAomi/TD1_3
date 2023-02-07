#pragma once
#include "BaseScene.h"
#include <memory>
#include <array>

#include "WorldTransform.h"
#include "CameraTransform.h"

class GameScene :
	public BaseScene
{

private:
	std::unique_ptr<class Ground> m_ground;
	CameraTransform m_camera;
	std::array<std::unique_ptr<class Wall>, 4> m_walls;
//	std::unique_ptr<class Stage> m_stage;	// 現在のステージ
//	std::unique_ptr<class SnowBall> m_snowBall; //　雪玉
//	std::unique_ptr<class Player> m_player;	// プレイヤー
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

