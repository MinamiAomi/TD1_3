#pragma once

#include <memory>
#include <string>


class Resource
{
private:
	using ModelPtr = std::unique_ptr<class Model>;
public:
	struct Images {
		unsigned int whiteImage;

	};

	struct Models {
		ModelPtr carrot;
		ModelPtr sphere;
		ModelPtr cube;
		ModelPtr axis;
	};

	struct Sounds {

	};

private:

	class TextureManager* m_texMana = nullptr;


	Images m_images;
	Models m_models;
	Sounds m_sounds;

public:
	static Resource* GetInstance();
	
	void Initalize(class TextureManager* tex);
	
	const Images& GetImage() { return m_images; }
	const Models& GetModel() { return m_models; }
	const Sounds&  GetSound() { return m_sounds; }

private:
	Resource() = default;
    ~Resource() = default;
	Resource(const Resource&) = delete;
	const Resource& operator&(const Resource&) = delete;

	void LoadImages();
	void LoadModels();
	void LoadSounds();
};

