#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Collision2D.h"
#include "ClearItem.h"
#include <array>

class Ball
{
private:
	WorldTransform m_transform;
	float m_radius = 1.0f;
	Vector3 m_velocity;
	Vector3 m_acceleration;
	float m_mass = 1.0f;
	Vector3 m_gravityAcceleration = -Vector3::UnitY * 9.8f;
	float m_inertia = 0.0f;
	
	Vector3 m_normal;	// ínñ ÇÃñ@ê¸

	Collider2D::Circle m_collider;

	std::array<bool,ClearItem::kTypeCount> m_itemFlag;
	std::array<WorldTransform,ClearItem::kTypeCount> m_itemTrans;

public:
	Ball();
	~Ball();

	void parent(WorldTransform* parent) { m_transform.parent = parent; }
	void normal(const Vector3& normal) { m_normal = normal; }

	const Collider2D::Circle& collider() const { return m_collider; }
	bool isCanGoal() { return m_itemFlag[ClearItem::kTypeCarrot] == true && m_itemFlag[ClearItem::kTypeBucket] == true; }

	void Initalize();
	void Update();
	void Draw(class CameraTransform* camera);
	void OnCollisionWall(const Vector2& closestPoint);
	void OnCollisionItem(ClearItem::Type type);
};

