#pragma once
#include <memory>

struct SceneCommonData 
{
	class Engine* engine = nullptr;
	class Resource* resource = nullptr;
	unsigned int frame = 0;
};