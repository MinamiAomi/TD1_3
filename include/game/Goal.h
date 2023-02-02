#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Shape.h"
#include "Collision2D.h"

class CameraTransform;

class Goal
{
private:
	static CameraTransform* s_camera;

public:

	static void camera(CameraTransform* camera) { s_camera = camera; }
private:
	Shape2D::RectAngle m_rect;
	WorldTransform m_transform;
	
	Collider2D::OBB m_collider;

public:
	Goal();
	~Goal();



	void position(const Vector2& pos) { m_rect.center = pos; }
	void rotate(float rot) { m_rect.rotate = rot; }
	void parent(WorldTransform* parent) { m_transform.parent = parent; }
	const Collider2D::OBB& collider() const { return m_collider; }

	void Initalize();
	void Update();
	void Draw();
	void PreCollision(float a);
	void OnCollision();


};

