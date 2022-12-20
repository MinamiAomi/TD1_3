#pragma once
#include "SceneCommonData.h"
#include <memory>
#include <stack>
#include "BaseScene.h"

class SceneManager
{

private:
	std::unique_ptr<BaseScene> m_scene;
	std::shared_ptr<SceneCommonData> m_commonData;

public:
	SceneManager();
	~SceneManager();


	void Initalize(class Engine* engine, class Resource* resource);
	void Update();
	void Draw();
	void ChangeScene();

	template<class NextScene>
	void Transition();

private:
	SceneManager(const SceneManager&) = delete;
	const SceneManager& operator=(const SceneManager&) = delete;
};

template<class NextScene>
inline void SceneManager::Transition()
{
	m_scene.reset(new NextScene(m_commonData, this));
	m_scene->Initalize();
}
