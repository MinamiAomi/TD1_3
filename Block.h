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
	// 3D用
	Object3D m_obj;
	// デバッグ用
	std::unique_ptr<class Sprite> m_sprite;

public:
	Block();

};

