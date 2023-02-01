#include "CarrotItem.h"
#include "Model.h"
#include "Resource.h"
#include "SceneManager.h"
#include "SceneCommonData.h"

void CarrotItem::Initalize()
{
	m_transform.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(45.0f), Vector3::UnitX);


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

void CarrotItem::OnCollision()
{
}
