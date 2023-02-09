#include "Ground.h"
#include "Resources.h"
#include "Model.h"
#include "CameraTransform.h"
#include "Material.h"
#include "DirectXCommon.h"
#include "Cube.h"
#include "Input.h"

Ground::Ground() {
	m_transform.Initalize();
	m_center.Initalize();
}

Ground::~Ground()
{
}

void Ground::Initalize()
{
	auto input = Input::GetInstance();
	//input->SetLeftStickDeadZone(0,0);

	m_world.position = Vector3::Zero;
	m_world.rotate = Quaternion::Identity;
	m_world.scale = { 1.0f,1.0f,1.0f };
	m_center.position = { 0.0f,2.0f,0.0f };
	m_center.parent = &m_world;
	m_transform.position = Vector3::Zero;
	m_transform.scale = { 11.0f,1.0f,11.0f };
	m_transform.parent = &m_world;
	m_material = Material::Create();
	m_material->CreateBuffer(DirectXCommon::GetInstance()->GetDevice());
	m_material->SetTextureHandle(Resource::GetInstance()->GetImage().groundImage);
	m_world.UpdateMatrix();
	m_transform.UpdateMatrix();
}

void Ground::Update()
{
	auto input = Input::GetInstance();

	Vector2 tmp;

	tmp = input->GetLeftStick(0);
	
	if (input->IsKeyPressed(DIK_D)) {
		tmp.x += 32000;
	}
	if (input->IsKeyPressed(DIK_A)) {
		tmp.x += -32000;
	}
	if (input->IsKeyPressed(DIK_W)) {
		tmp.y += 32000;
	}
	if (input->IsKeyPressed(DIK_S)) {
		tmp.y += -32000;
	}

	if (tmp.IsZero() == false) {
		m_tilt = tmp;

		float length = m_tilt.Length();
		float angle = length / 70000;
		Vector2 dir = m_tilt.Normalized();
		Vector3 axis = Cross({ dir.x,0.0f,dir.y }, -Vector3::UnitY).Normalized();

		m_world.rotate = Quaternion::CreateFromAngleAxis(angle, axis);
	}
	else {
		m_world.rotate = Quaternion::Slerp(0.2f, m_world.rotate, Quaternion::Identity);
		float i = m_world.rotate.LengthSquare();
		if (isnan(m_world.rotate.LengthSquare())) {
			m_world.rotate = Quaternion::Identity;
		}
	}

	m_center.position = normal() * 3;
	m_world.UpdateMatrix();
}

void Ground::Draw(CameraTransform* camera)
{
	//m_center.UpdateMatrix();
	m_world.UpdateMatrix();
	m_transform.UpdateMatrix();
	Cube::GetInstance()->Draw(m_material.get(), &m_transform, camera);
	//Resource::GetInstance()->GetModel().axis->Draw(&m_center, camera);
}
