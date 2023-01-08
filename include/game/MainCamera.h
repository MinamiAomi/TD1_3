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

	float m_yawAngle = 0.0f; // �U�����
	float m_pitchAngle = 0.0f; // �㉺�̊p�x
	float m_upperPitchAngle = Math::ToRadians(-89.0f); // ���グ��Ƃ��̍ő�p
	float m_lowerPitchAngle = Math::ToRadians(89.0f); // �����낷�Ƃ��̍ő�p
	
	// ���͕ϐ�
	// �}�E�X�ɂ���Ďn�_�ړ�
	bool mouseInput = false;
	// �ړ��ix : ���E.�E���{ y : �㉺.�オ�{ �� : �O�� �O���{�j
	Vector3 moveInput = {};
	// �����ړ��ix : ����.�E���{ y : ����.�オ�{�j
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

