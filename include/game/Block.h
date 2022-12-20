#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Shape.h"
#include "jsonLoader.h"


class Block
{

private:

	Shape2D::RectAngle m_rect;

	// 3D—p
	WorldTransform m_world;
	class Model* m_model;

public:
	Block();
	~Block();
	

	void Initalize(const BlockJsonData& data, float z_width);
	void Update();

	void Draw(class CameraTransform* camera);

	operator BlockJsonData() const;
};

