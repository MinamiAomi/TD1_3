#pragma once

#include <memory>
#include <string>


class Resource
{
private:
	using ModelPtr = std::unique_ptr<class Model>;
public:
	struct Images {

	};

	struct Models {
		ModelPtr carrot;
		ModelPtr sphere;
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
	
	static const Images& GetImage() { return GetInstance()->m_images; }
	static const Models& GetModel() { return GetInstance()->m_models; }
	static const Sounds& GetSound() { return GetInstance()->m_sounds; }

private:
	Resource() = default;
    ~Resource() = default;
	Resource(const Resource&) = delete;
	const Resource& operator&(const Resource&) = delete;

	void LoadImages();
	void LoadModels();
	void LoadSounds();
};

