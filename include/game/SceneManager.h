#pragma once
#include "GameObject.h"
#include <memory>
#include <stack>

class BaseScene;
class SceneManager : 
	public GameObject
{

private:
	std::unique_ptr<BaseScene> m_scene;
	std::shared_ptr<struct SceneCommonData> m_commonData;

public:
	SceneManager(class Game* game);
	~SceneManager();


	void Init();
	void Update();
	void Draw();
	

	template<class NextScene>
	void Transition();

private:
	SceneManager(const SceneManager&) = delete;
	const SceneManager& operator=(const SceneManager&) = delete;
};

template<class NextScene>
inline void SceneManager::Transition()
{
	m_scene.reset(new NextScene(GetGame(), m_commonData);
}
