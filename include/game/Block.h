#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"
#include "Shape.h"
#include "jsonLoader.h"
#include "Collision2D.h"

class Block
{

private:

	Shape2D::RectAngle m_rect;

	// 3D—p
	WorldTransform m_world;
	class Model* m_model;

	
	Collider2D::OBB m_collider;

public:
	Block();
	~Block();
	

	void Initalize(const BlockJsonData& data, float z_width, WorldTransform* parent);
	void Update();

	void Draw(class CameraTransform* camera);
	
	void SetCollider();
	const Collider2D::OBB& GetCollider() const { return m_collider; }

	operator BlockJsonData() const;
};

