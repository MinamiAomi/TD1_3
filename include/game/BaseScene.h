#pragma once
#include "GameObject.h"
#include <memory>
struct SceneCommonData 
{

};

class BaseScene :
	public GameObject
{
private:
	std::shared_ptr<SceneCommonData> m_commonData;

public:
	BaseScene(class Game* game, std::shared_ptr<SceneCommonData> commonData) : GameObject(game) {
		m_commonData = commonData;
	}
	virtual ~BaseScene() {}
	
	virtual void Update() = 0;
	virtual void Draw() = 0;
};