#pragma once
#include "WorldTransform.h"
#include "CameraTransform.h"
#include "MathUtility.h"

class MainCamera
{

private:
	WorldTransform m_transform;
	CameraTransform m_camera;

	float m_moveSpeed = 1.0f;
	float m_lookSpeed = Math::ToRadians(1.0f);

	float m_yawAngle = 0.0f; // 振り向き
	float m_pitchAngle = 0.0f; // 上下の角度
	float m_upperPitchAngle = Math::ToRadians(-89.0f); // 見上げるときの最大角
	float m_lowerPitchAngle = Math::ToRadians(89.0f); // 見下ろすときの最大角
	
	// 入力変数
	// マウスによって始点移動
	bool mouseInput = false;
	// 移動（x : 左右.右が＋ y : 上下.上が＋ ｚ : 前後 前が＋）
	Vector3 moveInput = {};
	// 視線移動（x : 水平.右が＋ y : 垂直.上が＋）
	Vector2 lookInput = {};

public:
	MainCamera();
	~MainCamera();

	void Initalize();
	void Update();

	CameraTransform* GetCameraTransform() { return &m_camera; }

private:
	void Input();
	void Move();
};

