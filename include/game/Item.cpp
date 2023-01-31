#include "Item.h"

CameraTransform* Item::s_camera = nullptr;

Item::Item() {
	m_transform.Initalize();
}