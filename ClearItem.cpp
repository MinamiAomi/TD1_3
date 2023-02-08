#include "ClearItem.h"
#include "Resources.h"
#include "Model.h"

ClearItem::ClearItem()
{
	m_transform.Initalize();
}

ClearItem::~ClearItem()
{
}

void ClearItem::Initalize(Type type, const Vector2& center, float radius)
{
	m_isGet = false;

	m_type = type;
	m_center = center;
	m_radius = radius;

	m_transform.position = { m_center.x,2.0f,m_center.y };
	m_transform.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(45.0f),Vector3::UnitX);
	m_transform.scale = Vector3(m_radius);

	m_transform.UpdateMatrix();
}

void ClearItem::Update()
{
	m_transform.rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(1.0f), Vector3::UnitY) * m_transform.rotate;

	m_collider.center = m_center;
	m_collider.radius = 2.0f;
}

void ClearItem::Draw(CameraTransform* camera)
{
	m_transform.UpdateMatrix();
	switch (m_type)
	{
	case ClearItem::kTypeCarrot:
		Resource::GetInstance()->GetModel().carrot->Draw(&m_transform, camera);
		break;
	case ClearItem::kTypeBucket:
		Resource::GetInstance()->GetModel().bucket->Draw(&m_transform, camera);
		break;
	}

}

void ClearItem::OnCollision()
{
	m_isGet = true;
}
