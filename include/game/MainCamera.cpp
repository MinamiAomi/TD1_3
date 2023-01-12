#include "MainCamera.h"
#include "Input.h"

#include "Game.h"

MainCamera::MainCamera()
{
	m_camera.Initalize();
	m_worldCenter.Initalize();
}

MainCamera::~MainCamera()
{
}

void MainCamera::Initalize()
{
	m_worldCenter.position = Vector3::Zero;
	m_transform.position = { 0,0,-50 };
}

void MainCamera::Update()
{
	Input();
	Move();
	m_worldCenter.UpdateMatrix();
	m_camera.UpdateWithTransform(m_transform);
}

void MainCamera::Input() {
	
	auto input = Input::GetInstance();

	debugMoveInput = Vector3::Zero;
	debugLookInput = Vector2::Zero;

	moveInput = Vector2::Zero;

	// �O��ړ�
	if (input->IsKeyPressed(DIK_W)) {
		debugMoveInput.z += 1.0f;
		moveInput.y += -1.0f;
	}
	if (input->IsKeyPressed(DIK_S)) {
		debugMoveInput.z -= 1.0f;
		moveInput.y += 1.0f;
	}
	// ���E�ړ�
	if (input->IsKeyPressed(DIK_D)) {
		debugMoveInput.x += 1.0f;
		moveInput.x += -1.0f;
	}
	if (input->IsKeyPressed(DIK_A)) {
		debugMoveInput.x -= 1.0f;
		moveInput.x += 1.0f;
	}
	// �㉺�ړ�
	if (input->IsKeyPressed(DIK_SPACE)) {
		debugMoveInput.y += 1.0f;
	}
	if (input->IsKeyPressed(DIK_LSHIFT)) {
		debugMoveInput.y -= 1.0f;
	}

	// �}�E�X����
	mouseInput = input->IsMousePressed(kMouseButtonRight);

	if (mouseInput == true) {
		debugLookInput = input->GetMouseMove();
	}
	else {
		//// �������_�ړ�
		//if (input->IsKeyPressed(DIK_UP)) {
		//	debugLookInput.y += -1.0f;	// �s�b�`�p���t�̂���
		//}
		//if (input->IsKeyPressed(DIK_DOWN)) {
		//	debugLookInput.y -= -1.0f;	// �s�b�`�p���t�̂���
		//}
		//// �������_�ړ�
		//if (input->IsKeyPressed(DIK_RIGHT)) {
		//	debugLookInput.x += 1.0f;
		//}
		//if (input->IsKeyPressed(DIK_LEFT)) {
		//	debugLookInput.x -= 1.0f;
		//}
	}

	rotationInput = 0;

	if (input->IsKeyPressed(DIK_E)) {
		rotationInput += -1;
	}
	if (input->IsKeyPressed(DIK_Q)) {
		rotationInput += 1;
	}
}

void MainCamera::Move() {
	
	if (Game::IsDebugMode()) {

		// �����ړ�
		if (debugLookInput.IsZero() == false) {
			if (debugLookInput.y != 0.0f) {
				m_pitchAngle += debugLookInput.y * m_lookSpeed;
				m_pitchAngle = Math::Clamp(m_pitchAngle, m_upperPitchAngle, m_lowerPitchAngle);

			}
			if (debugLookInput.x != 0.0f) {
				m_yawAngle += debugLookInput.x * m_lookSpeed;
				m_yawAngle = Math::Loop(m_yawAngle, Math::Radian);

			}
			m_transform.rotate = Quaternion::CreateFromYaw(m_yawAngle) * Quaternion::CreateFromPitch(m_pitchAngle);
		}


		// �ړ����Ă���
		if (debugMoveInput.IsZero() == false) {
			Vector3 xzMove = m_transform.rotate * Multipliy(debugMoveInput, Vector3(1.0f, 0.0f, 1.0f));
			m_transform.position += Normalize(Vector3(xzMove.x, debugMoveInput.y, xzMove.z)) * m_moveSpeed;
		}

	}
	else {

		if (moveInput.IsZero() == false) {
			Vector3 pos = m_worldCenter.position;
			moveInput *= m_worldMoveSpeed;
			pos += {moveInput, pos.z};
			m_worldCenter.position = pos;
		}

		if (rotationInput != 0) {
			Quaternion rot = Quaternion::CreateFromAngleAxis(m_worldRotationSpeed * rotationInput, Vector3::UnitZ);
			m_worldCenter.rotate = rot * m_worldCenter.rotate;
		}

	}
}