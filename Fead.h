#pragma once
#include "Sprite.h"
#include "SceneManager.h"


class Fead {
private:
	bool m_isFeadOut = false;
	bool m_isFeadIn = false;
	
	std::unique_ptr<Sprite> m_sprite;
	int m_time;
	int m_feadTime = 30;
	SceneId m_nextScene = {};

public:	
	Fead();
	~Fead();

	void StartFeadOut(SceneId scene);

	bool isActive() const;

	void Initalize();
	void Update();
	void Draw();
};