#include "Goal.h"
#include "Resources.h"
#include "Model.h"

Goal::Goal()
{
	m_transform.Initalize();
}

Goal::~Goal()
{
}

void Goal::Initalize(const Vector2& pos)
{
	m_center = pos;
	
	m_transform.position = { m_center.x,2.1f,m_center.y };
	m_transform.rotate = Quaternion::Identity;
	m_transform.scale = { 1.2f,1.2f,1.2f };
	m_isClear = false;

	m_transform.UpdateMatrix();
}

void Goal::Update()
{
	m_collider.center = m_center;
	m_collider.radius = 2.8f;
}

void Goal::Draw(CameraTransform* camera)
{
	m_transform.UpdateMatrix();
	Resource::GetInstance()->GetModel().sphere->Draw(&m_transform, camera);
}

void Goal::OnCollision()
{
	m_isClear = true;
}
