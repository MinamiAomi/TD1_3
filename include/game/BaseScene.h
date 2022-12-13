#pragma once
#include "SceneCommonData.h"
#include <memory>

class BaseScene
{
private:
	std::shared_ptr<SceneCommonData> m_commonData;

public:
	BaseScene(std::shared_ptr<SceneCommonData> commonData) {
		m_commonData = commonData;
	}
	virtual ~BaseScene() {}
	
	virtual void Initalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};