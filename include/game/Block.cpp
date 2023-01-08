#include "Block.h"
#include "CameraTransform.h"
#include "Model.h"
#include "Resource.h"

Block::Block()
{
	m_world.Initalize();
}

Block::~Block()
{
	m_model = nullptr;
}

void Block::Initalize(const BlockJsonData& data, float z_width)
{
	m_model = Resource::GetInstance()->GetModel().cube.get();

	m_rect.center = data.position;
	m_rect.theta = data.rotation;
	m_rect.width = data.width;
	m_rect.height = data.height;


	m_world.position = { m_rect.center,0.0f };
	m_world.scale = { m_rect.width,m_rect.height,z_width };
	m_world.rotate = Quaternion(m_rect.theta, Vector3::UnitZ);
	
}

void Block::Update()
{

}

void Block::Draw(class CameraTransform* camera)
{
	m_world.UpdateMatrix();
	m_model->Draw(&m_world, camera);
}

Block::operator BlockJsonData() const
{
	return { 0,m_rect.center,m_rect.theta,m_rect.width,m_rect.height };
}
