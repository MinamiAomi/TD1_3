#include "MainCamera.h"
#include "Input.h"


MainCamera::MainCamera()
{
	m_camera.Initalize();
}

MainCamera::~MainCamera()
{
}

void MainCamera::Initalize()
{
	m_camera.position = { 0,0,-50 };
	m_camera.target = { 0,0,0 };
	m_moveSpeed = 1.0f;
}

void MainCamera::Update()
{
	auto input = Input::GetInstance();

	if (input->IsKeyPressed(DIK_W)) {
		m_camera.MoveVector(Vector3::UnitY * m_moveSpeed);
	}
	if (input->IsKeyPressed(DIK_S)) {
		m_camera.MoveVector(-Vector3::UnitY * m_moveSpeed);
	}

	if (input->IsKeyPressed(DIK_D)) {
		m_camera.MoveVector(Vector3::UnitX * m_moveSpeed);
	}
	if (input->IsKeyPressed(DIK_A)) {
		m_camera.MoveVector(-Vector3::UnitX * m_moveSpeed);
	}

	m_camera.UpdateMatrix();
}
