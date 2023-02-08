#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Collision2D.h"

class CameraTransform;

class Goal {

private:
	bool m_isClear = false;

	WorldTransform m_transform;
	Collider2D::Circle m_collider;

	Vector2 m_center;
	float radius = {};

public:
	Goal();
	~Goal();

	void parent(WorldTransform* world) { m_transform.parent = world; }
	bool isClear() const { return m_isClear; }

	const Collider2D::Circle& collider() const { return m_collider; }

	void Initalize(const Vector2& pos);
	void Update();
	void Draw(CameraTransform* camera);
	void OnCollision();
};

