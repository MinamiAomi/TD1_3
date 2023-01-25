#pragma once
#include "SceneCommonData.h"
#include <memory>

class BaseScene
{
protected:
	std::shared_ptr<SceneCommonData> m_commonData;
	class SceneManager* m_sceneMana = nullptr;

public:
	BaseScene(std::shared_ptr<SceneCommonData> commonData, SceneManager* sceneMana) {
		m_commonData = commonData;
		m_sceneMana = sceneMana;
	}
	virtual ~BaseScene() {}
	
	virtual void Initalize() = 0;
	virtual void Update() = 0;
	virtual void Draw3D() = 0;
	virtual void Draw2D() = 0;
	virtual void ChangeScene() = 0;
};