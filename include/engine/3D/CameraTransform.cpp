#include "CameraTransform.h"

void CameraTransform::Initalize(ID3D12Device* dev)
{
	constBuffer.Create(dev);
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


