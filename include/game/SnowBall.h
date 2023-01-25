#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Shape.h"
#include "Collision2D.h"


class SnowBall
{

private:
	WorldTransform m_transform;
	float m_radius = 0.5f;

	Collider2D::Circle m_collider;

	Vector2 m_velocity;
	float m_mass = 10.0f;

	float m_gravity = 9.8f * 8;

	class CameraTransform* m_camera = nullptr;

public:
	SnowBall();
	~SnowBall();

	void camera(CameraTransform* camera) { m_camera = camera; }

	void Initalize();
	void Update();
	void PreCollision();
	void OnCollision(const Vector2& closestPoint);
	void Draw();

	const Collider2D::Circle collider()const { return m_collider; }

	void Collision(std::vector<std::unique_ptr<class Block>>& blocks);

};

