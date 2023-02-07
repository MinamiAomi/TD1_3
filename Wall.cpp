#include "Wall.h"
#include "Resource.h"
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

void Wall::Initalize()
{

}

void Wall::Update()
{
}

void Wall::Draw()
{
	m_transform.UpdateMatrix();
	Cube::GetInstance()->Draw(s_material.get(), &m_transform, s_camera);
}
