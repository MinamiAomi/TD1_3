#include "CameraTransform.h"
#include "DirectXCommon.h"

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

void CameraTransform::Transfer(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndexCameraData)
{
	constBuffer.MapPtr()->view = viewMat;
	constBuffer.MapPtr()->proj = projMat;
	constBuffer.MapPtr()->cameraPos = position;
	constBuffer.SetGraphicsRootConstantBufferView(cmdList, rootParameterIndexCameraData);
}


