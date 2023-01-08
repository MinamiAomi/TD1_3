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
	m_transform.position = { 0,0,-50 };
}

void MainCamera::Update()
{
	Input();
	Move();
	m_camera.UpdateWithTransform(m_transform);
}

void MainCamera::Input() {
	
	auto input = Input::GetInstance();

	moveInput = Vector3::Zero;
	lookInput = Vector2::Zero;


	// �O��ړ�
	if (input->IsKeyPressed(DIK_W)) {
		moveInput.z += 1.0f;
	}
	if (input->IsKeyPressed(DIK_S)) {
		moveInput.z -= 1.0f;
	}
	// ���E�ړ�
	if (input->IsKeyPressed(DIK_D)) {
		moveInput.x += 1.0f;
	}
	if (input->IsKeyPressed(DIK_A)) {
		moveInput.x -= 1.0f;
	}
	// �㉺�ړ�
	if (input->IsKeyPressed(DIK_SPACE)) {
		moveInput.y += 1.0f;
	}
	if (input->IsKeyPressed(DIK_LSHIFT)) {
		moveInput.y -= 1.0f;
	}

	// �}�E�X����
	mouseInput = input->IsMousePressed(kMouseButtonRight);

	if (mouseInput == true) {
		lookInput = input->GetMouseMove();
	}
	else {
		// �������_�ړ�
		if (input->IsKeyPressed(DIK_UP)) {
			lookInput.y += -1.0f;	// �s�b�`�p���t�̂���
		}
		if (input->IsKeyPressed(DIK_DOWN)) {
			lookInput.y -= -1.0f;	// �s�b�`�p���t�̂���
		}
		// �������_�ړ�
		if (input->IsKeyPressed(DIK_RIGHT)) {
			lookInput.x += 1.0f;
		}
		if (input->IsKeyPressed(DIK_LEFT)) {
			lookInput.x -= 1.0f;
		}
	}
}

void MainCamera::Move() {
	
	// �����ړ�
	if (lookInput.IsZero() == false) {
		if (lookInput.y != 0.0f) {
			m_pitchAngle += lookInput.y * m_lookSpeed;
			m_pitchAngle = Math::Clamp(m_pitchAngle, m_upperPitchAngle, m_lowerPitchAngle);

		}
		if (lookInput.x != 0.0f) {
			m_yawAngle += lookInput.x * m_lookSpeed;
			m_yawAngle = Math::Loop(m_yawAngle, Math::Radian);
			
		}
		m_transform.rotate = Quaternion::CreateFromYaw(m_yawAngle) * Quaternion::CreateFromPitch(m_pitchAngle);
	}


	// �ړ����Ă���
	if (moveInput.IsZero() == false) {
		Vector3 xzMove = m_transform.rotate * Multipliy(moveInput, Vector3(1.0f, 0.0f, 1.0f));
		m_transform.position += Normalize(Vector3(xzMove.x, moveInput.y, xzMove.z)) * m_moveSpeed;
	}

}