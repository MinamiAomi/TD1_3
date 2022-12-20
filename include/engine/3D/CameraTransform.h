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

	Vector3 position = { 0.0f,0.0f,-50.0f }; // ���_���W
	Vector3 target = { 0.0f,0.0f,0.0f }; // �����_���W
	Vector3 up = { 0.0f,1.0f,0.0f }; // ��x�N�g��

	Matrix44 viewMat; // �r���[�s��

	float fovAngleY = Math::ToRadians(45.0f);	// �㉺��p
	float aspectRatio = 1280.0f / 720.0f;  // �A�X�y�N�g��
	float nearZ = 0.1f;			// �O�[
	float farZ = 1000.0f;		// ���[

	Matrix44 projMat; // �ˉe�s��

	void SetRay(const Vector3& ray) { target = position + ray; }
	const Vector3& GetRay() const { return target - position; }

	void MoveVector(const Vector3& vec) { 
		position += vec; 
		target += vec;
	}

	/// <summary>
	/// �������i�萔�o�b�t�@�̐������s���j
	/// </summary>
	/// <param name="dev"></param>
	void Initalize();
	/// <summary>
	/// �s��̍X�V
	/// </summary>
	void UpdateMatrix();
	/// <summary>
	/// �s���]��
	/// </summary>
	/// <param name="rootParameterIndexWorldTransform"></param>
	void Transfer(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndexCameraData);
};

