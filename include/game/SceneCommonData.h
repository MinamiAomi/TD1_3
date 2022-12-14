#pragma once
#include <memory>

struct SceneCommonData 
{
	unsigned int frame;
	std::unique_ptr<class Model> carrotModel;
	std::unique_ptr<class Model> sphereModel;
	
	void LoadModel();
};