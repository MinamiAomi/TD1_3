#pragma once
#include <memory>
#include <stack>

class BaseScene;
class SceneManager
{

private:
	std::unique_ptr<BaseScene> m_scene;

public:

	static SceneManager* GetInstance();


	void Init();
	void Update();
	void Draw();
	

	template<class NextScene>
	void Transition();

private:
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	const SceneManager(const SceneManager&) = delete;
};

template<class NextScene>
inline void SceneManager::Transition()
{
	m_scene.reset(new NextScene);
}
