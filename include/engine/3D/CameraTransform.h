#pragma once
#include "MathUtility.h"
#include "ConstBuffer.h"

class CameraTransform
{
public:
	struct ConstBufferDataCamera
	{
		Matrix44 view;
		Matrix44 proj;
		Vector3 cameraPos;
	};

private:
	ConstBuffer<ConstBufferDataCamera> constBuffer;

public:

	Vector3 position = { 0.0f,0.0f,-50.0f }; // 視点座標
	Vector3 target = { 0.0f,0.0f,0.0f }; // 注視点座標
	Vector3 up = { 0.0f,1.0f,0.0f }; // 上ベクトル

	Matrix44 viewMat; // ビュー行列

	float fovAngleY = Math::ToRadians(45.0f);	// 上下画角
	float aspectRatio = 1280.0f / 720.0f;  // アスペクト比
	float nearZ = 0.1f;			// 前端
	float farZ = 1000.0f;		// 奥端

	Matrix44 projMat; // 射影行列

	void SetRay(const Vector3& ray) { target = position + ray; }
	const Vector3& GetRay() const { return target - position; }

	void MoveVector(const Vector3& vec) { 
		position += vec; 
		target += vec;
	}

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
	void Transfer(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndexCameraData);
};

