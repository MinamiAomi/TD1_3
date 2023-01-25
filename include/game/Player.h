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
	// �v���C���[����������̈�ƂȂ�u���b�N 4��
	std::array<Block, kBlockCount> m_blocks;
	// �g�����X�t�H�[��
	WorldTransform m_transform;
	// �J����
	CameraTransform m_camera;

	Vector2 m_moveInput = {};
	float m_scaleInput = {};
	float m_rotateInput = {};
	bool m_isKeyMoveInput = false;

	float left;
	float right;
	float top;
	float bottom;

public:
	Player();
	~Player();

	std::array<Block, kBlockCount> blocks() const { return m_blocks; }
	CameraTransform* camera() { return &m_camera; }
	Vector2 positionXY() const { return m_camera.position.xy(); }

	void Initalize();
	void Update();
	void PreCollision();
	void Draw();

private:
	void Input();
};

