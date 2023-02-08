#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include <array>


class CameraTransform;
class Model;
class Material;

class Ground
{
private:
	WorldTransform m_world;
	WorldTransform m_center;

	WorldTransform m_transform;
	Model* m_model = nullptr;

	Vector2 m_tilt;

	std::unique_ptr<Material> m_material;


public:
	Ground();
	~Ground();

	WorldTransform* world() { return &m_world; }
	Vector3 normal() const { return m_world.rotate * Vector3::UnitY; }

	void Initalize();
	void Update();
	void Draw(CameraTransform* camera);
};

