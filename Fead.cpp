#include "Fead.h"
#include "SceneManager.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"


Fead::Fead()
{
}

Fead::~Fead()
{
}

void Fead::StartFeadOut(SceneId scene)
{
	m_nextScene = scene;
	m_isFeadOut = true;
	m_time = 0;
}

bool Fead::isActive() const
{
	return m_isFeadOut || m_isFeadIn;
}

void Fead::Initalize()
{
	m_sprite = Sprite::Create(0, {}, { 1280.0f,720.0f });
}

void Fead::Update()
{
	m_time++;
	float t = (float)m_time / (float)m_feadTime;

	if (m_isFeadOut == true) {
		m_sprite->SetColor({ 0.0f,0.0f,0.0f,t });
		if (m_time >= m_feadTime) {
			m_isFeadOut = false;
			m_isFeadIn = true;
			m_time = 0;
			t = 0.0f;
			switch (m_nextScene)
			{
			case kSceneIdTitle:
				SceneManager::GetInstance()->Transition<TitleScene>();
				break;
			case kSceneIdMain:
				SceneManager::GetInstance()->Transition<GameScene>();
				break;
			case kSceneIdClear:
				SceneManager::GetInstance()->Transition<ClearScene>();
				break;
			}
			m_sprite->SetColor({ 0.0f,0.0f,0.0f,1.0f });
		}
	}
	if (m_isFeadIn == true) {
		m_sprite->SetColor({ 0.0f,0.0f,0.0f,1.0f - t });
		if (m_time >= m_feadTime) {
			m_isFeadIn = false;
			m_time = 0;
		}
	}
}

void Fead::Draw()
{
	Sprite::Draw(m_sprite.get(), SceneManager::GetInstance()->commonData().camera2D.get());
}
