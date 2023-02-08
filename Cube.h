#pragma once
#include <memory>

class Meth;
class Material;
class WorldTransform;
class CameraTransform;

class Cube
{
private:
	std::unique_ptr<Meth> m_meth;

public:
	static Cube* GetInstance();

	void Draw(Material* material, WorldTransform* world, CameraTransform* camera);

private:
	Cube() { InternalInitalize(); }
	~Cube() = default;
	Cube(const Cube&) = delete;
	const Cube& operator=(const Cube&) = delete;

	void InternalInitalize();
};

