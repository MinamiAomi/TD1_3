#pragma once
#include <memory>
#include "Camera2D.h"

struct SceneCommonData 
{
	std::unique_ptr<Camera2D> camera2D;
	unsigned int frame = 0;
};