#pragma once
#include "MathUtility.h"
#include "ConstBuffer.h"


class WorldTransform
{
public:
	struct ConstBudderDataTransform
	{
		Matrix44 world;
	};

private:
	ConstBuffer<ConstBudderDataTransform> constBuffer;
	
public:
	
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Quaternion rotate = Quaternion::Identity;
	Vector3 position = { 0.0f,0.0f,0.0f };
	Matrix44 worldMatrix;
	WorldTransform* parent = nullptr;

	/// <summary>
	/// 初期化（定数バッファの生成を行う）
	/// </summary>
	/// <param name="dev"></param>
	void Initalize();
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

