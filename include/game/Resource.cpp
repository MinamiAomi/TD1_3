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
}

void Resource::LoadModels()
{
	m_models.carrot = Model::CreateFromObj("carrot/Carrot.obj");
	m_models.sphere = Model::CreateFromObj("sphere/UVSphere.obj");
}

void Resource::LoadSounds()
{
}
