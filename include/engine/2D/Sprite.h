#pragma once
#include "MathUtility.h"
#include <wrl.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstBuffer.h"
#include "PipelineFunc.h"
#include <memory>

class Sprite
{

private:
	template<class TYPE>
	using ComPtr = Microsoft::WRL::ComPtr<TYPE>;

public:
	// ���_�\����
	struct Vertex
	{
		Vector3 pos; // ���W
		Vector2 uv;  // uv
	};
	// �萔
	struct ConstBufferData
	{
		Vector4 color;	// �F
		Matrix44 matrix;	// �ϊ��s��
	};
private:
	static const int kVertexCount = 4; // ���_��
	static const int kIndexCount = 6;
	static DirectXCommon* diXCom;
	static class TextureManager* texManager;

	static ComPtr<ID3D12RootSignature> rootSignature; // ���[�g�V�O�l�`��
	static ComPtr<ID3D12PipelineState> pipelineState[kBlendModeCount]; // �p�C�v���C���X�e�[�g
	
	static IndexBuffer indexBuffer; // �C���f�b�N�X

public: // �ÓI�����o�֐�
	// �ÓI�����o�̏�����
	static void StaticInitalize(DirectXCommon* dixCom, TextureManager* texMan, UINT winWidth, UINT winHeight);

	static std::unique_ptr<Sprite> Create(
		UINT  textureHandle, Vector2 position, Vector2 size = { 0,0 }, Vector4 color = { 1,1,1,1 },
		Vector2 anchorPoint = { 0,0 }, bool isFlipX = false, bool isFlipY = false);

	static void Draw(Sprite& sprite, const class Camera2D* camera, BlendMode blend);

private:
	VertexBuffer<Vertex> vertexBuffer; // ���_�o�b�t�@
	ConstBuffer<ConstBufferData> constBuffer; // �萔�o�b�t�@
	UINT  textureHandle = 0; // �e�N�X�`���n���h��
	float rotation = 0.0f; // Z�����̉�]�p�i2D��]�j
	Vector2 position = { 0.0f,0.0f }; // ���W
	Vector2 size = { 100.0f,100.0f }; // �T�C�Y
	Vector2 anchorPoint = { 0.0f,0.0f }; // ��]�ړ����s����_
	Matrix44 worldMat; // ���[���h�s��
	Vector4 color = { 1.0f,1.0f,1.0f,1.0f }; // �F
	bool isFlipX = false; // ���E���]���s����
	bool isFlipY = false; // �㉺���]���s����

	Vector2 texBase = { 0.0f,0.0f }; // �摜�̍�����W
	Vector2 texSize = { 16.0f,16.0f };;// �摜�̕��A����

public:
	Sprite();
	Sprite(UINT  textureHandle, Vector2 position, Vector2 size, Vector4 color = { 1,1,1,1 },
		Vector2 anchorPoint = { 0,0 }, bool isFlipX = false, bool isFlipY = false);

	void SetTextureHandle(UINT handle) { textureHandle = handle; }
	UINT GetTextureHandle() const { return textureHandle; }
	void SetRotation(float theta) { rotation = theta; }
	float GetRotation() const { return rotation; }
	void SetPosition(const Vector2& pos) { position = pos; }
	const Vector2& GetPosition() const { return position; }
	void SetSize(const Vector2& size) {this->size = size; }
	const Vector2& GetSize() const { return size; }
	void SetAnchorPoint(const Vector2& point) { anchorPoint = point; }
	const Vector2& GetAnchorPoint() const { return anchorPoint; }
	void SetColor(const Vector4& color) { this->color = color; }
	const Vector4& GetColor() const { return color; }
	void SetIsFlipX(bool isFlipX) { this->isFlipX = isFlipX; }
	bool GetIsFlipX() const { return isFlipX; }
	void SetIsFlipY(bool isFlipY) { this->isFlipY = isFlipY; }
	bool GetIsFlipY() const { return isFlipY; }
	void SetTextureRect(const Vector2& texBase, const Vector2& texSize);

private:
	void TransferVertex(ID3D12GraphicsCommandList* cmdList, TextureManager* texMana);
	void TransferConstData(ID3D12GraphicsCommandList* cmdList, const class Camera2D* camera);
};

