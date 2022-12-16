#pragma once
#include "MathUtility.h"
#include "ConstBuffer.h"


struct WorldTransform
{
	struct ConstBudderDataTransform
	{
		Matrix44 world;
	};

	ConstBuffer<ConstBudderDataTransform> constBuffer;
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotation = { 0.0f,0.0f,0.0f };
	Vector3 position = { 0.0f,0.0f,0.0f };
	Matrix44 worldMatrix;
	WorldTransform* parent = nullptr;

	/// <summary>
	/// �������i�萔�o�b�t�@�̐������s���j
	/// </summary>
	/// <param name="dev"></param>
	void Initalize(ID3D12Device* dev);
	/// <summary>
	/// �s��̍X�V
	/// </summary>
	void UpdateMatrix();
	/// <summary>
	/// �s���]��
	/// </summary>
	/// <param name="rootParameterIndexWorldTransform"></param>
	void Transfer(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndexWorldTransform);
};

