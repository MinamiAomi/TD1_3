#include "DebugText.h"
#include "TextureManager.h"

const std::string DebugText::kTexturePath = "resources/images/debugfont.png";
const Vector2 DebugText::kDefultSize = { 10.0f,20.0f };

DebugText* DebugText::GetInstance()
{
	static DebugText instance;
	return &instance;
}

void DebugText::Initalize(float windowWidth, float windowHeight)
{
	
	m_textureHandle = TextureManager::LoadTexture(kTexturePath);
	projMat = Matrix44::CreateOrthoProjection(windowWidth, windowHeight);
	for (auto sprite : m_sprites) {
		sprite = new Sprite();
		sprite->SetTextureHandle(m_textureHandle);
	}

}


DebugText::DebugText() {

}
DebugText::~DebugText() {
	for (auto sprite : m_sprites) {
		delete sprite;
	}
}

void DebugText::SetSprite(const std::string& str)
{
	
	for (auto it : str) {

		m_sprites[m_spriteIndex];
		m_spriteIndex++;
	}
}
