#pragma once

#include "MathUtility.h"
#include <d3dx12.h>
#include "ConstBuffer.h"

class Camera3D
{

public:
	struct ConstBufferDataCamera
	{
		Matrix44 view;
		Matrix44 proj;
		Vector3 cameraPos;
	};

private:
	
	ConstBuffer<ConstBufferDataCamera> m_constBuffer;

	Vector3 m_eye = { 0.0f,0.0f,-50.0f }; // ���_���W
	Vector3 m_target = { 0.0f,0.0f,0.0f }; // �����_���W
	Vector3 m_up = { 0.0f,1.0f,0.0f }; // ��x�N�g��

	Matrix44 m_viewMat; // �r���[�s��

	float m_fovAngleY = Math::ToRadians(45.0f);	// �㉺��p
	float m_aspectRatio =	1280.0f / 720.0f;  // �A�X�y�N�g��
	float m_nearZ = 0.1f;			// �O�[
	float m_farZ = 1000.0f;		// ���[

	Matrix44 m_projMat; // �ˉe�s��

	Matrix44 m_viewProjMat;

public:
	Camera3D();
	~Camera3D() {}

	void SetPosition(const Vector3& pos) { m_eye = pos; }
	const Vector3& GetPosition() const { return m_eye; }
	void SetTarget(const Vector3& target) { m_target = target; }
	const Vector3& GetTarget() const { return m_target; }
	void SetRay(const Vector3& ray) { m_target = m_eye + ray; }
	const Vector3& GetRay() const { return m_target - m_eye; }
	void SetUp(const Vector3& up) { m_up = up; }
	const Vector3& GetUp() const { return m_up; }
	const Matrix44& GetViewMatrix() const { return m_viewMat; }

	void SetFovAngleY(float theta) { m_fovAngleY = theta; }
	float GetFovAngleY() const { return m_fovAngleY; }
	void SetAspectRatio(float width,float height) { m_aspectRatio = width / height; }
	void SetAspectRatio(float raito) { m_aspectRatio = raito; }
	float GetAspectRatio() const { return m_aspectRatio; }
	void SetNear(float nearZ) { m_nearZ = nearZ; }
	float GetNear() const { return m_nearZ; }
	void SetFar(float farZ) { m_farZ = farZ; }
	float GetFar() const { return m_farZ; }
	const Matrix44& GetProjectionMatrix() const { return m_projMat; }

	const Matrix44& GetViewProjMat() const { return m_viewProjMat; }

	void UpdateMatrix();

	void SetGraphicsCommand(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndexCamera);

};