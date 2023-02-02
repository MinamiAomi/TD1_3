#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Shape.h"
#include "Collision2D.h"
#include "Item.h"
#include "Block.h"

class Sprite;

class SnowBall
{

private:
	WorldTransform m_transform;
	float m_radius = 0.5f;

	Collider2D::Circle m_collider;

	Vector2 m_velocity;
	float m_mass = 10.0f;

	float m_gravity = 9.8f * 8;

	Vector2 normal = {};
	Vector2 prePos = {};

	class CameraTransform* m_camera = nullptr;

	bool m_goalItems[Item::kItemTypeCount] = {};

	bool m_isGameOver = false;


public:
	SnowBall();
	~SnowBall();

	void camera(CameraTransform* camera) { m_camera = camera; }
	bool canGoal() const {
		return m_goalItems[Item::kItemTypeCarrot] && 
			m_goalItems[Item::kItemTypeBucket] && 
			m_goalItems[Item::kItemTypeEye];
	}
	bool isGameOver() const { return m_isGameOver; }

	void Initalize();
	void Update();
	void PreCollision();
	void OnCollisionBlock(const Vector2& closestPoint, Block::Type blockType);
	void OnCollisionItem(Item::TypeId type);
	void OnCollisionGoal();
	void Draw();

	const Collider2D::Circle collider()const { return m_collider; }

	void Collision(std::vector<std::unique_ptr<class Block>>& blocks);

};

