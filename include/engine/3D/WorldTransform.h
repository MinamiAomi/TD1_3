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
	/// 初期化（定数バッファの生成を行う）
	/// </summary>
	/// <param name="dev"></param>
	void Initalize(ID3D12Device* dev);
	/// <summary>
	/// 行列の更新
	/// </summary>
	void UpdateMatrix();
	/// <summary>
	/// 行列を転送
	/// </summary>
	/// <param name="rootParameterIndexWorldTransform"></param>
	void Transfer(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndexWorldTransform);
};

