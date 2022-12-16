#include "WorldTransform.h"


void WorldTransform::Initalize(ID3D12Device* dev)
{
	constBuffer.Create(dev);
	constBuffer.Map();
}

void WorldTransform::UpdateMatrix() 
{
	Matrix44 scaMat, rotMat, traMat;

	scaMat = Matrix44::CreateScaling(scale);

	rotMat *= Matrix44::CreateRotationZ(rotation.z);
	rotMat *= Matrix44::CreateRotationX(rotation.x);
	rotMat *= Matrix44::CreateRotationY(rotation.y);

	traMat *= Matrix44::CreateTranslation(position);

	worldMatrix = Matrix44::Identity;
	worldMatrix *= scaMat;
	worldMatrix *= rotMat;
	worldMatrix *= traMat;

	if (parent != nullptr) {
		worldMatrix *= parent->worldMatrix;
	}
}

void WorldTransform::Transfer(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndexWorldTransform)
{
	constBuffer.MapPtr()->world = worldMatrix;
	constBuffer.SetGraphicsRootConstantBufferView(cmdList, rootParameterIndexWorldTransform);
}
