#pragma once
#include "GameObject.h"

class SceneManager : public GameObject
{
public:
	enum SceneId 
	{
		kTitleScene
	};

private:
	class Scene* m_scene;

public:
	SceneManager(class Game* game);
	~SceneManager();


	void Update();
	void Draw();
	void ChangeScene();
};

