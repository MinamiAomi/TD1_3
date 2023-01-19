#pragma once
#include "WorldTransform.h"

class TestObj
{
private:
	WorldTransform m_transform = {};
	class Model* m_model = nullptr;
	class CameraTransform* m_camera = nullptr;


public:
	TestObj();
	~TestObj();

	void Initalize(class CameraTransform* camera);
	void Update();
	void Draw(class CameraTransform* camera);

};

