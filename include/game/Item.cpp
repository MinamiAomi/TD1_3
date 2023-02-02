#include "Item.h"
#include "Collision2D.h"
#include "Sprite.h"
CameraTransform* Item::s_camera = nullptr;

Item::Item() {
	m_transform.Initalize();
	m_sprite = std::make_unique<Sprite>();
	m_get = false;
}

Item::~Item() {
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
