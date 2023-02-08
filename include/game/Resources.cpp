#include "Resources.h"
#include <cassert>
#include "TextureManager.h"
#include "Model.h"

Resource* Resource::GetInstance()
{
	static Resource instance;
	return &instance;
}

void Resource::Initalize(TextureManager* tex)
{
	assert(tex != nullptr);
	m_texMana = tex;

	LoadImages();
	LoadModels();
	LoadSounds();
}

void Resource::LoadImages()
{
	std::string imageDir = "resources/images/";

	m_images.whiteImage = m_texMana->LoadTexture(imageDir + "white.png");
	m_images.debugImage = m_texMana->LoadTexture(imageDir + "Debug.png");
	m_images.TitleImage = m_texMana->LoadTexture(imageDir + "Title.png");
	m_images.NumberImage = m_texMana->LoadTexture(imageDir + "number.png");
	m_images.ClearImage = m_texMana->LoadTexture(imageDir + "clear_haikei.png");
	m_images.HeadImage = m_texMana->LoadTexture(imageDir + "head.png");
	m_images.wallImage = m_texMana->LoadTexture(imageDir + "wall.png");
	m_images.groundImage = m_texMana->LoadTexture(imageDir + "ground.png");
	m_images.pushAImage = m_texMana->LoadTexture(imageDir + "puthA.png");
	m_images.stickImage = m_texMana->LoadTexture(imageDir + "stick.png");
}

void Resource::LoadModels()
{
	m_models.carrot = Model::CreateFromObj("carrot/Carrot.obj");
	m_models.sphere = Model::CreateFromObj("sphere/UVSphere.obj");
	m_models.cube = Model::CreateFromObj("cube/Cube.obj");
	m_models.axis = Model::CreateFromObj("axis/axis.obj");
	m_models.bucket = Model::CreateFromObj("bucket/bucket.obj");
}

void Resource::LoadSounds()
{
}
