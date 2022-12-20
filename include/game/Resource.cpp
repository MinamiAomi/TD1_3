#include "Resource.h"
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

}

void Resource::LoadModels()
{
	m_models.carrot = Model::CreateFromObj("carrot/Carrot.obj");
	m_models.sphere = Model::CreateFromObj("sphere/UVSphere.obj");
	m_models.cube = Model::CreateFromObj("cube/Cube.obj");
}

void Resource::LoadSounds()
{
}
