#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Collision2D.h"

class CameraTransform;
class Material;

class Wall
{
private:
	static CameraTransform* s_camera;
	static std::unique_ptr<Material> s_material;

public:
	static void camera(CameraTransform* camera) { s_camera = camera; }
	static void StaticInitalize();

private:
	WorldTransform m_transform;
	
	Vector2 m_center;
	float m_width = 0.0f;
	float m_height = 0.0f;
	float m_angle = 0.0f;

	Collider2D::OBB m_collider;

public:
	Wall();
	~Wall();

	void position(const Vector3& pos) { m_transform.position = pos; }
	void rotate(const Quaternion& rot) { m_transform.rotate = rot; }
	void scale(const Vector3& scale) { m_transform.scale = scale; }
	
	void Pos(const Vector2& pos);
	void IncAngle(float angle);
	void IncWidth(float width);
	void IncHeight(float height);

	const Vector2& center() const { return m_center; }
	float angle() const { return m_angle; }
	float width() const { return m_width; }
	float height() const { return m_height; }

	void parent(WorldTransform* parent) { m_transform.parent = parent; }

	const Collider2D::OBB& collider() const { return m_collider; }

	void Initalize(const Vector2& pos, float angle, float width, float height);
	void Update();
	void Draw();

};

