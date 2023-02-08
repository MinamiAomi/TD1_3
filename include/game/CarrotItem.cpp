#include "CarrotItem.h"
#include "Model.h"
#include "Resources.h"
#include "SceneManager.h"
#include "SceneCommonData.h"
#include "Sprite.h"


void CarrotItem::Initalize()
{
	m_transform.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(45.0f), Vector3::UnitX);
	m_sprite->SetTextureHandle(Resource::GetInstance()->GetImage().NumberImage);
	m_sprite->SetPosition({0,0});
	m_sprite->SetSize({100,100});
	m_sprite->SetTextureRect({ 32 * 1,0 }, { 32,32 });
}

void CarrotItem::Update()
{
	m_transform.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(0.5f),Vector3::UnitY) * m_transform.rotate;
}

void CarrotItem::Draw()
{
	m_transform.UpdateMatrix();
	Resource::GetInstance()->GetModel().carrot->Draw(&m_transform, s_camera);
}

void CarrotItem::Draw2D()
{
	Sprite::Draw(m_sprite.get(), SceneManager::GetInstance()->commonData().camera2D.get());
}

void CarrotItem::OnCollision()
{
}
