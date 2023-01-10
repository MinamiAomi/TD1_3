#include "CameraTransform.h"
#include "DirectXCommon.h"
#include "WorldTransform.h"

void CameraTransform::Initalize()
{
	auto dixcom = DirectXCommon::GetInstance();
	assert(dixcom->IsInit());
	constBuffer.Create(dixcom->GetDevice());
	constBuffer.Map();

}

void CameraTransform::UpdateMatrix()
{
	viewMat = Matrix44::CreateView(position, target, up);
	projMat = Matrix44::CreateProjection(fovAngleY, aspectRatio, nearZ, farZ);
}

void CameraTransform::UpdateWithTransform(const WorldTransform& transform, bool upRotate)
{
	position = transform.position;
	Vector3 baseForward = Vector3::UnitZ;
	ray(transform.rotate * baseForward);
	if (upRotate == true) {
		up = transform.rotate * Vector3::UnitY;
	}
	UpdateMatrix();
	
}

void CameraTransform::Transfer(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndexCameraData)
{
	constBuffer.MapPtr()->view = viewMat;
	constBuffer.MapPtr()->proj = projMat;
	constBuffer.MapPtr()->cameraPos = position;
	constBuffer.SetGraphicsRootConstantBufferView(cmdList, rootParameterIndexCameraData);
}


