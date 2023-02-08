#include "Wall.h"
#include "Resources.h"
#include "Model.h"
#include "CameraTransform.h"
#include "Material.h"
#include "DirectXCommon.h"
#include "Cube.h"

CameraTransform* Wall::s_camera = nullptr;
std::unique_ptr<Material> Wall::s_material = nullptr;

void Wall::StaticInitalize() {
	s_material = Material::Create();
	s_material->CreateBuffer(DirectXCommon::GetInstance()->GetDevice());
	s_material->SetTextureHandle(Resource::GetInstance()->GetImage().wallImage);
}

Wall::Wall()
{
	m_transform.Initalize();
}

Wall::~Wall()
{

}

void Wall::Pos(const Vector2& pos)
{
	m_center = pos;
	m_transform.position = { m_center.x, 2.0f, m_center.y };
}

void Wall::IncAngle(float angle)
{
	m_angle += angle;
	m_transform.rotate = Quaternion::CreateFromAngleAxis(m_angle, -Vector3::UnitY);
}

void Wall::IncWidth(float width)
{
	m_width += width;
	m_transform.scale.x = m_width;
}

void Wall::IncHeight(float height)
{
	m_height += height;
	m_transform.scale.z = m_height;
}

void Wall::Initalize(const Vector2& pos, float angle, float width, float height)
{
	m_center = pos;
	m_width = width;
	m_height = height;
	m_angle = angle;
	
	static constexpr float y = 2.0f;

	m_transform.position = { m_center.x, y, m_center.y };
	m_transform.rotate = Quaternion::CreateFromAngleAxis(m_angle, -Vector3::UnitY);
	m_transform.scale = { m_width, 1.0f, m_height };

	m_transform.UpdateMatrix();
}

void Wall::Update()
{
	m_collider.center = m_center;

	Matrix33 rot = Matrix33::CreateRotation(m_angle);
	m_collider.direction[0] = rot.GetX();
	m_collider.direction[1] = rot.GetY();

	m_collider.size[0] = m_width;
	m_collider.size[1] = m_height;
}

void Wall::Draw()
{
	m_transform.UpdateMatrix();
	Cube::GetInstance()->Draw(s_material.get(), &m_transform, s_camera);
}
