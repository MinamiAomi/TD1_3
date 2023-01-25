#include "Player.h"
#include "App.h"
#include "Input.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initalize()
{
	m_transform.Initalize();
	m_transform.scale = { 1.0f,1.0f,1.0f };
	m_camera.Initalize();
	m_camera.position = { 0.0f,0.0f,-15.0f };

	float as = 1280.0f / 720.0f;
	left = -as;
	right = left + as * 2;
	top = 1.0f;
	bottom = top - 2.0f;
	float width = 0.05f;

	m_blocks[kLeftBlock].center({ left, 0.0f });
	m_blocks[kLeftBlock].width(width);
	m_blocks[kLeftBlock].height(1.0f - width);
	
	m_blocks[kTopBlock].center({ 0.0f, top });
	m_blocks[kTopBlock].width(as + width);
	m_blocks[kTopBlock].height(width);
	
	m_blocks[kRightBlock].center({ right, 0.0f });
	m_blocks[kRightBlock].width(width);
	m_blocks[kRightBlock].height(1.0f - width);
	
	m_blocks[kBottomBlock].center({ 0.0f, bottom });
	m_blocks[kBottomBlock].width(as + width);
	m_blocks[kBottomBlock].height(width);


	for (auto& it : m_blocks) {
		it.rotate(0.0f);
		it.parent(&m_transform);
		it.Initalize();
	}

}

void Player::Update()
{
	Input();
	//m_transform.position.x += 0.1f * m_moveInput.x;
	//m_transform.position.y += 0.1f * m_moveInput.y;

	auto input = App::GetInstance()->GetInput();


	Vector2 move = 0.1f * m_moveInput;
	m_transform.position.xy(m_transform.position.xy() + move);
	m_camera.position.xy(m_camera.position.xy() + move);
	m_camera.target.xy(m_camera.target.xy() + move);


	m_camera.position.z += 0.1f * m_scaleInput;
	float dist = Math::Abs(m_camera.position.z - m_camera.target.z);
	m_transform.scale = { dist / 4.6f, dist / 4.6f, 1.0f };
	//m_camera.position.y = dist / 3.5f;


	m_transform.UpdateMatrix();
	m_camera.UpdateMatrix();
}

void Player::PreCollision()
{
	m_transform.UpdateMatrix();
	for (auto& it : m_blocks) {
		it.PreCollision2();
	}
}

void Player::Draw()
{
	m_transform.UpdateMatrix();
	for (auto& it : m_blocks) {
		it.Draw();
	}
}

void Player::Input()
{
	auto input = App::GetInstance()->GetInput();

	m_moveInput = Vector2::Zero;
	m_scaleInput = 0.0f;
	m_rotateInput = 0.0f;

	if (input->IsKeyPressed(DIK_W)) {
		m_moveInput.y += 1.0f;
		m_isKeyMoveInput = true;
	}
	if (input->IsKeyPressed(DIK_S)) {
		m_moveInput.y += -1.0f;
		m_isKeyMoveInput = true;
	}
	if (input->IsKeyPressed(DIK_D)) {
		m_moveInput.x += 1.0f;
		m_isKeyMoveInput = true;
	}
	if (input->IsKeyPressed(DIK_A)) {
		m_moveInput.x += -1.0f;
		m_isKeyMoveInput = true;
	}

	// k¬
	if (input->IsKeyPressed(DIK_SPACE) || input->IsPadButtonPressed(0,kPadLeftTrigger)) {
		m_scaleInput += 1.0f;
	}
	// Šg‘å
	if (input->IsKeyPressed(DIK_LSHIFT) || input->IsPadButtonPressed(0, kPadRightTrigger)) {
		m_scaleInput += -1.0f;
	}
}
