#pragma once
#include "WorldTransform.h"

class TestObj
{
private:
	WorldTransform m_transform = {};
	WorldTransform m_transform2 = {};
	class Model* m_model = nullptr;
	class CameraTransform* m_camera = nullptr;
	Quaternion rotation;


public:
	TestObj();
	~TestObj();

	void Initalize(class CameraTransform* camera);
	void Update();
	void Draw(class CameraTransform* camera);

};

