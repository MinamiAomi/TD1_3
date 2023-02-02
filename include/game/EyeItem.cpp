#include "EyeItem.h"
#include "Model.h"
#include "Resource.h"
#include "SceneManager.h"
#include "SceneCommonData.h"
#include "Sprite.h"

#include "Resource.h"

void EyeItem::Initalize()
{
	//m_transform.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(45.0f), Vector3::UnitX);
	m_sprite->SetTextureHandle(Resource::GetInstance()->GetImage().NumberImage);
	m_sprite->SetPosition({ 200,0 });
	m_sprite->SetSize({ 100,100 });
	m_sprite->SetTextureRect({ 32 * 3,0 }, { 32,32 });
}

void EyeItem::Update()
{
	m_transform.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(0.5f), Vector3::UnitY) * m_transform.rotate;
}

void EyeItem::Draw()
{
	m_transform.UpdateMatrix();
	Resource::GetInstance()->GetModel().carrot->Draw(&m_transform, s_camera);
}

void EyeItem::Draw2D()
{
	Sprite::Draw(m_sprite.get(), SceneManager::GetInstance()->commonData().camera2D.get());
}


void EyeItem::OnCollision()
{
}