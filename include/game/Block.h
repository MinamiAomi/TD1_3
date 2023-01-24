#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Shape.h"
#include "jsonLoader.h"
#include "Collision2D.h"

class Block
{
private:
	// Zé≤ï˚å¸ÇÃïù
	static float s_zWidth;
	// ã§óLÉJÉÅÉâ
	static class CameraTransform* s_camera;

public:
	static void zWidth(float zWidth) { s_zWidth = zWidth; }
	static float zWidth() { return s_zWidth; }
	static void camera(CameraTransform* camera) { s_camera = camera; }

private:

	Shape2D::RectAngle m_rect;

	// 3Dóp
	WorldTransform m_world;
	class Model* m_model;

	
	Collider2D::OBB m_collider;

public:
	Block();
	~Block();
	
	void center(const Vector2& center) { m_rect.center = center; }
	void width(float width) { m_rect.width = width; }
	void height(float height) { m_rect.height = height; }
	void rotate(float rotate) { m_rect.theta = rotate; }
	void parent(WorldTransform* parent) { m_world.parent = parent; }



	void Initalize(const BlockJsonData& data, float z_width, WorldTransform* parent);
	void Initalize();
	void Update();
	void PreCollision();
	void Draw();
	
	const Collider2D::OBB& collider() const { return m_collider; }

	operator BlockJsonData() const;
};

