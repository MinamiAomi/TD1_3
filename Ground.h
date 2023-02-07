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

	WorldTransform m_transform;
	Model* m_model = nullptr;

	std::unique_ptr<Material> m_material;

public:
	Ground();
	~Ground();

	WorldTransform* world() { return &m_world; }

	void Initalize();
	void Update();
	void Draw(CameraTransform* camera);
};

