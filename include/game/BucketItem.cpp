#include "BucketItem.h"
#include "Model.h"
#include "Resource.h"
#include "SceneManager.h"
#include "SceneCommonData.h"
#include "Sprite.h"

#include "Resource.h"

void BucketItem::Initalize()
{
	//m_transform.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(45.0f), Vector3::UnitX);
	m_sprite->SetTextureHandle(Resource::GetInstance()->GetImage().NumberImage);
	m_sprite->SetPosition({ 100,0 });
	m_sprite->SetSize({ 100,100 });
	m_sprite->SetTextureRect({ 32 * 2,0 }, { 32,32 });
	
}

void BucketItem::Update()
{
	m_transform.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(0.5f), Vector3::UnitY) * m_transform.rotate;
}

void BucketItem::Draw()
{
	m_transform.UpdateMatrix();
	Resource::GetInstance()->GetModel().carrot->Draw(&m_transform, s_camera);
}

void BucketItem::Draw2D()
{
	Sprite::Draw(m_sprite, SceneManager::GetInstance()->commonData().camera2D.get());
}

void BucketItem::OnCollision()
{
}