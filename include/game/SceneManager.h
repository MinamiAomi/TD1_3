#pragma once
#include "SceneCommonData.h"
#include <memory>
#include <stack>

class BaseScene;
class SceneManager
{

private:
	std::unique_ptr<BaseScene> m_scene;
	std::shared_ptr<SceneCommonData> m_commonData;

public:
	SceneManager();
	~SceneManager();


	void Initalize();
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
	m_scene->Initalize();
}
