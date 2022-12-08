#pragma once
#include "GameObject.h"

struct SceneCommonData 
{

};

class BaseScene :
	public GameObject
{
private:
	std::shared_ptr<SceneCommonData> m_commonData;

public:
	BaseScene(class Game* game, SceneCommonData* commonData) : GameObject(game) {
		m_commonData = std::shared_ptr<SceneCommonData>(commonData);
	}
	virtual ~BaseScene() {}
	
	virtual void Update() = 0;
	virtual void Draw() = 0;
};