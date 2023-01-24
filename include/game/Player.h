#pragma once
#include "MathUtility.h"
#include "WorldTransform.h"
#include "CameraTransform.h"
#include <array>
#include "Block.h"

class Player
{
public:

	enum BlocksIndex {
		kLeftBlock,
		kTopBlock,
		kRightBlock,
		kBottomBlock,

		kBlockCount
	};

private:
	// プレイヤーが動かせる領域となるブロック 4辺
	std::array<Block, kBlockCount> m_blocks;
	// トランスフォーム
	WorldTransform m_transform;
	// カメラ
	CameraTransform m_camera;

	Vector2 m_moveInput = {};
	float m_scaleInput = {};
	float m_rotateInput = {};
	bool m_isKeyMoveInput = false;

public:
	Player();
	~Player();

	std::array<Block, kBlockCount> blocks() const { return m_blocks; }
	CameraTransform* camera() { return &m_camera; }

	void Initalize();
	void Update();
	void PreCollision();
	void Draw();

private:
	void Input();
};

