#pragma once
#include <string>
#include "MathUtility.h"
#include "ConstBuffer.h"
#include <memory>

class Material
{

	friend class Model;

private:
	struct ConstBufferDataMaterial 
	{
		Vector3 ambient;	// �����i�A���r�G���g�j
		float padding_1;	// �p�f�B���O
		Vector3 deffuse;	// �g�U���i�f�B�t���[�Y�j
		float shininess;	// ����x
		Vector3 specular;	// ���ʔ��ˌ��i�X�y�L�����[�j
		float alpha;		// �����x�i�A���t�@�j
	};

public:
	static std::unique_ptr<Material> Create();

private:
	std::string m_name;				// �}�e���A���̖��O
	std::string m_texFileName;		// �e�N�X�`���̖��O
	Vector3 m_ambient = { 0.3f,0.3f,0.3f };				// �A���r�G���g
	Vector3 m_diffuse = { 0.0f,0.0f,0.0f };				// �f�B�t���[�Y
	Vector3 m_specular = { 0.0f,0.0f,0.0f };			// �X�y�L�����[
	float m_shininess = 5.0f;
	float m_alpha = 1.0f;			// �����x

	ConstBuffer<ConstBufferDataMaterial> m_constBuff;
	UINT m_textureHandle = 0;

public:
	void SetName(const std::string& name) { m_name = name; }
	const std::string& GetName() const { return m_name; }
	void SetTexFileName(const std::string& name) { m_texFileName = name; }
	const std::string& GetTexFileName() const { return m_texFileName; }
	void SetAmbient(const Vector3& ambient) { m_ambient = ambient; }
	const Vector3& GetAmbient() const { return m_ambient; }
	void SetDiffuse(const Vector3& diffuse) { m_diffuse = diffuse; }
	const Vector3& GetDiffuse() const { return m_diffuse; }
	void SetSpecular(const Vector3& specular) { m_specular = specular; }
	const Vector3& GetSpecular() const { return m_specular; }
	void SetShininess(float shininess) { m_shininess = shininess; }
	float GetShininess() const { return m_shininess; }
	void SetAlpha(float alpha) { m_alpha = alpha; }
	float GetAlpha() const { return m_alpha; }
	void SetTextureHandle(UINT tex) { m_textureHandle = tex; }
	UINT GetTextureHandle() const { return m_textureHandle; }

	void CreateBuffer(ID3D12Device* dev);
	void SetGraphicsCommand(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndexMaterial, UINT rootParameterIndexTexture);

private:
	Material() {}

};

