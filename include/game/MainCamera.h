#pragma once
#include "CameraTransform.h"
#include "MathUtility.h"

class MainCamera
{

private:
	CameraTransform m_camera;

	float m_moveSpeed;

public:
	MainCamera();
	~MainCamera();

	void Initalize();
	void Update();

	CameraTransform* GetCameraTransform() { return &m_camera; }
};

