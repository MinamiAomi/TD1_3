#include "Block.h"
#include "CameraTransform.h"
#include "Model.h"
#include "Resource.h"
#include "SceneManager.h"
#include "SceneCommonData.h"

float Block::s_zWidth = 5;
CameraTransform* Block::s_camera = nullptr;

Block::Block()
{
	m_model = nullptr;
	m_world.Initalize();
}

Block::~Block()
{
	m_model = nullptr;
}

void Block::Initalize(const BlockJsonData& data, float z_width, WorldTransform* parent)
{
	m_model = Resource::GetInstance()->GetModel().cube.get();

	m_rect.center = data.position;
	m_rect.theta = data.rotation;
	m_rect.width = data.width;
	m_rect.height = data.height;


	m_world.position = { m_rect.center,0.0f };
	m_world.scale = { m_rect.width,m_rect.height,z_width };
	m_world.rotate = Quaternion(m_rect.theta, Vector3::UnitZ);

	m_world.parent = parent;

	m_collider.center = m_world.position.xy();
	Matrix33 rotMat = Matrix33::CreateRotation(m_rect.theta);
	m_collider.direction[0] = rotMat.GetX();
	m_collider.direction[1] = rotMat.GetY();

	m_collider.size[0] = m_world.scale.x;
	m_collider.size[1] = m_world.scale.y;

}

void Block::Initalize()
{
	m_model = Resource::GetInstance()->GetModel().cube.get();

	m_world.position = { m_rect.center,0.0f };
	m_world.scale = { m_rect.width,m_rect.height,s_zWidth };
	m_world.rotate = Quaternion(m_rect.theta, Vector3::UnitZ);

	m_collider.center = m_world.position.xy();
	Matrix33 rotMat = Matrix33::CreateRotation(m_rect.theta);
	m_collider.direction[0] = rotMat.GetX();
	m_collider.direction[1] = rotMat.GetY();

	m_collider.size[0] = m_world.scale.x;
	m_collider.size[1] = m_world.scale.y;
}

void Block::Update()
{


}

void Block::PreCollision()
{
	m_world.UpdateMatrix();

	m_collider.center = m_world.worldMatrix.GetTranslation().xy();

	Matrix33 rotMat = Matrix33::CreateRotation(m_rect.theta + m_world.parent->rotate.Angle());
	m_collider.direction[0] = rotMat.GetX();
	m_collider.direction[1] = rotMat.GetY();

	m_collider.size[0] = m_rect.width;
	m_collider.size[1] = m_rect.height;
}

void Block::Draw()
{
	m_world.UpdateMatrix();
	m_model->Draw(&m_world, s_camera);
}

Block::operator BlockJsonData() const
{
	return { 0,m_rect.center,m_rect.theta,m_rect.width,m_rect.height };
}
