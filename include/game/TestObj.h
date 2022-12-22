#pragma once
#include "WorldTransform.h"

class TestObj
{
private:
	WorldTransform m_transform = {};
	class Model* m_model = nullptr;

public:
	TestObj();
	~TestObj();

	void Initalize();
	void Update();
	void Draw(class CameraTransform* camera);

};

