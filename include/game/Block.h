#pragma once
#include "WorldTransform.h"
#include "MathUtility.h"

class Block
{

private:

	Vector2 m_position;
	float m_width, m_height;
	float m_theta;

	// 3D�p
	WorldTransform m_world;
	class Model* m_model;

#ifdef _DEBUG
	// �f�o�b�O�p
	std::unique_ptr<class Sprite> m_sprite;
#endif // _DEBUG


public:
	Block();
	~Block();
	


	void Update();

	void Draw();

#ifdef _DEBUG
	void Draw2D();
#endif // _DEBUG



};

