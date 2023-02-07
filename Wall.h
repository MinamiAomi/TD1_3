#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"

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
	
public:
	Wall();
	~Wall();

	void position(const Vector3& pos) { m_transform.position = pos; }
	void rotate(const Quaternion& rot) { m_transform.rotate = rot; }
	void scale(const Vector3& scale) { m_transform.scale = scale; }
	void parent(WorldTransform* parent) { m_transform.parent = parent; }

	void Initalize();
	void Update();
	void Draw();

};

