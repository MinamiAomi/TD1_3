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
	m_images.debugImage = m_texMana->LoadTexture(imageDir + "Debug.png");
	m_images.TitleImage = m_texMana->LoadTexture(imageDir + "Title.png");
}

void Resource::LoadModels()
{
	m_models.carrot = Model::CreateFromObj("carrot/Carrot.obj");
	m_models.sphere = Model::CreateFromObj("sphere/UVSphere.obj");
	m_models.cube = Model::CreateFromObj("cube/Cube.obj");
	m_models.axis = Model::CreateFromObj("axis/axis.obj");
}

void Resource::LoadSounds()
{
}
