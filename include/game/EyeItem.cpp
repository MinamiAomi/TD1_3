#include "EyeItem.h"
#include "Model.h"
#include "Resource.h"
#include "SceneManager.h"
#include "SceneCommonData.h"

void EyeItem::Initalize()
{
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

void EyeItem::OnCollision()
{
}