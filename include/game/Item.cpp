#include "Item.h"
#include "Collision2D.h"

CameraTransform* Item::s_camera = nullptr;

Item::Item() {
	m_transform.Initalize();
	m_get = false;
}

void Item::PreCollision()
{
	m_transform.UpdateMatrix();

	m_collider.center = m_transform.worldMatrix.GetTranslation().xy();
	m_collider.radius = 0.3f;
}

void Item::OnCollision() {
	m_get = true;
}
