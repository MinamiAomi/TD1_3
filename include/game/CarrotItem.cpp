#include "CarrotItem.h"
#include "Model.h"
#include "Resource.h"
#include "SceneManager.h"
#include "SceneCommonData.h"

void CarrotItem::Initalize()
{
}

void CarrotItem::Update()
{
}

void CarrotItem::Draw()
{
	m_transform.UpdateMatrix();
	Resource::GetInstance()->GetModel().carrot->Draw(&m_transform, s_camera);
}

void CarrotItem::OnCollision()
{
}
