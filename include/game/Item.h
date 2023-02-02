#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Shape.h"
#include "Collision2D.h"

class CameraTransform;
class Sprite;

class Item {

protected:
	static class CameraTransform* s_camera;

public:
	static void camera(CameraTransform* camera) { s_camera = camera; }

public:
	enum TypeId {
		kItemTypeCarrot,
		kItemTypeBucket,
		kItemTypeEye,

		kItemTypeCount
	};

protected:
	WorldTransform m_transform;
	Collider2D::Circle m_collider;

	Sprite* m_sprite;

	bool m_get = false;
public:
	Item();
	virtual ~Item();

	void position(const Vector3& pos) { m_transform.position = pos; }
	void scale(const Vector3& sca) { m_transform.scale = sca; }
	void parent(WorldTransform* parent) { m_transform.parent = parent; }
	const Collider2D::Circle& collider() const { return m_collider; }
	bool isGet() const { return m_get; }

	virtual void Initalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Draw2D() = 0;
	void PreCollision();
	void OnCollision();

	virtual TypeId typeId() const = 0;
};