#pragma once
#include <vector>
#include <memory>
#include <string>
#include <wrl.h>
#include <array>
#include <unordered_map>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "MathUtility.h"
#include "PipelineFunc.h"
#include "Meth.h"
#include "Material.h"

class Model 
{
private:
	template<class TYPE>
	using ComPtr = Microsoft::WRL::ComPtr<TYPE>;

public:
	struct Vertex
	{
		Vector3 position;	// ���W
		Vector3 normal;		// �@��
		Vector2 uv;			// uv���W
	};


	enum RootParameter 
	{
		kWorldTransform,			// ���[���h�s��
		kCamera,		// �J�����f�[�^�i�s����܂ށj
		kMaterial,		// �}�e���A��
		kTexture,       // �e�N�X�`��

		kRootParameterCount
	};

private:

	static class DirectXCommon* diXCom;
	static class TextureManager* texMana;
	static std::string directory;
	static ComPtr<ID3D12RootSignature> rootSignature; // ���[�g�V�O�l�`��
	static ComPtr<ID3D12PipelineState> pipelineState; // �p�C�v���C���X�e�[�g
	static std::unique_ptr<Material> defaultMaterial;

public:

	/// <summary>
	/// �ÓI�����o�̏�����
	/// </summary>
	/// <param name="dixcom">DirectXCommon�̃|�C���^</param>
	/// <param name="dir">���f���̃f�B���N�g��</param>
	static void StaticInitalize(DirectXCommon* dixcom, TextureManager* texmana, const std::string& dir = "resources/model/");

	/// <summary>
	/// obj�t�@�C�����琶��
	/// </summary>
	/// <param name="path">�t�@�C���p�X</param>
	/// <returns>Model�̃X�}�[�g�|�C���^</returns>
	static std::unique_ptr<Model> CreateFromObj(const std::string& path);

private:
	
	std::string m_name;
	std::vector<std::unique_ptr<Meth>> m_meths;
	std::unordered_map<std::string, std::unique_ptr<Material>> m_materials;

public:
	~Model() {}

	void Draw(ID3D12GraphicsCommandList* cmdList, class Object3D* object);
private:
	Model() {}
};
