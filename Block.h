#pragma once
#include "Object3D.h"

class Block
{
private:

	static class Camera3D* camera3D;
	static class Camera2D* camera2D;

public:
	static void SetCamera(class Camera3D* camera3D, class Camera2D* camera2D);

private:
	// 3D�p
	Object3D m_obj;
	// �f�o�b�O�p
	std::unique_ptr<class Sprite> m_sprite;

public:
	Block();

};

