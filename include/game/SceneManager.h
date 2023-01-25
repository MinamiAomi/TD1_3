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
	static SceneManager* GetInstance();

	const SceneCommonData& commonData() const { return *m_commonData.get(); }

	void Initalize();
	void Update();
	void Draw();
	void ChangeScene();

	template<class NextScene>
	void Transition();

private:
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	const SceneManager& operator=(const SceneManager&) = delete;
};

template<class NextScene>
inline void SceneManager::Transition()
{
	m_scene.reset(new NextScene(m_commonData, this));
	m_scene->Initalize();
}
