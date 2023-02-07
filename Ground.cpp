#include "Ground.h"
#include "Resource.h"
#include "Model.h"
#include "CameraTransform.h"
#include "Material.h"
#include "DirectXCommon.h"
#include "Cube.h"
#include "Input.h"

Ground::Ground() {
	m_transform.Initalize();
}

Ground::~Ground()
{
}

void Ground::Initalize()
{
	m_world.position = Vector3::Zero;
	m_world.rotate = Quaternion::Identity;
	m_world.scale = { 1.0f,1.0f,1.0f };
	m_transform.position = Vector3::Zero;
	m_transform.scale = { 11.0f,1.0f,11.0f };
	m_transform.parent = &m_world;
	m_material = Material::Create();
	m_material->CreateBuffer(DirectXCommon::GetInstance()->GetDevice());
	m_material->SetTextureHandle(Resource::GetInstance()->GetImage().groundImage);
}

void Ground::Update()
{
	auto input = Input::GetInstance();

	if (input->IsKeyPressed(DIK_D)) {
		m_world.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(1.0f), Vector3::UnitZ) * m_world.rotate;
	}
	if (input->IsKeyPressed(DIK_A)) {
		m_world.rotate = Quaternion::CreateFromAngleAxis(-Math::ToRadians(1.0f), Vector3::UnitZ) * m_world.rotate;
	}
	if (input->IsKeyPressed(DIK_W)) {
		m_world.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(1.0f), Vector3::UnitX) * m_world.rotate;
	}
	if (input->IsKeyPressed(DIK_S)) {
		m_world.rotate = Quaternion::CreateFromAngleAxis(-Math::ToRadians(1.0f), Vector3::UnitX) * m_world.rotate;
	}

	m_world.UpdateMatrix();
}

void Ground::Draw(CameraTransform* camera)
{
	m_transform.UpdateMatrix();
	Cube::GetInstance()->Draw(m_material.get(), &m_transform, camera);
}
