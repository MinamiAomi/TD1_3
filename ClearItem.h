#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Collision2D.h"

class CameraTransform;

class ClearItem
{
public:
	enum Type {
		kTypeCarrot,
		kTypeBucket,

		kTypeCount
	};

private:
	bool m_isGet = false;

	WorldTransform m_transform;
	Collider2D::Circle m_collider;

	Vector2 m_center;
	float m_radius = {};

	Type m_type = kTypeCarrot;

public:
	ClearItem();
	~ClearItem();

	void parent(WorldTransform* parent) { m_transform.parent = parent; }

	const Collider2D::Circle& collider() const { return m_collider; }
	Type type() const { return m_type; }
	bool isGet() const { return m_isGet; }

	void Initalize(Type type, const Vector2& center, float radius);
	void Update();
	void Draw(CameraTransform* camera);
	void OnCollision();
};

