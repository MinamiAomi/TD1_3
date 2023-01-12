#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Shape.h"
#include "Collision2D.h"


class SnowBall
{

private:
	WorldTransform m_transform;
	float m_radius = 3.0f;

	Collider2D::Circle m_collider;

	Vector2 m_velocity;
	float m_mass = 10.0f;

	float m_gravity = 9.8f * 8;


public:
	SnowBall();
	~SnowBall();

	void Initalize();
	void Update();
	void Draw(class CameraTransform* camera);

	void SetCollider();
	const Collider2D::Circle GetCollider()const { return m_collider; }

	void Collision(std::vector<std::unique_ptr<class Block>>& blocks);

};
