#include "Goal.h"
#include "Resource.h"
#include "Model.h"
#include "CameraTransform.h"

CameraTransform* Goal::s_camera = nullptr;

Goal::Goal()
{
	m_transform.Initalize();
}

Goal::~Goal()
{
}

void Goal::Initalize()
{

	m_rect.width = 0.3f;
	m_rect.height = 0.3f;

	m_transform.position = { m_rect.center,0.0f };
	m_transform.scale = { m_rect.width,m_rect.height,1 };
	m_transform.rotate = Quaternion(m_rect.rotate, Vector3::UnitZ);

	m_collider.center = m_transform.position.xy();
	Matrix33 rotMat = Matrix33::CreateRotation(m_rect.rotate);
	m_collider.direction[0] = rotMat.GetX();
	m_collider.direction[1] = rotMat.GetY();

	m_collider.size[0] = m_transform.scale.x;
	m_collider.size[1] = m_transform.scale.y;
}

void Goal::Update()
{
}

void Goal::Draw()
{
	m_transform.UpdateMatrix();
	Resource::GetInstance()->GetModel().cube->Draw(&m_transform,s_camera);
}

void Goal::PreCollision(float a)
{
	m_transform.UpdateMatrix();

	m_collider.center = m_transform.worldMatrix.GetTranslation().xy();

	Matrix33 rotMat;
	float rotate = a + m_rect.rotate;
	rotMat = Matrix33::CreateRotation(rotate);

	m_collider.direction[0] = rotMat.GetX();
	m_collider.direction[1] = rotMat.GetY();

	m_collider.size[0] = m_rect.width;
	m_collider.size[1] = m_rect.height;
}

void Goal::OnCollision()
{
	
}
