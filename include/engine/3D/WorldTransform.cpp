#include "WorldTransform.h"
#include "DirectXCommon.h"

void WorldTransform::Initalize()
{
	auto dixcom = DirectXCommon::GetInstance();
	assert(dixcom->IsInit());
	constBuffer.Create(dixcom->GetDevice());
	constBuffer.Map();
}

void WorldTransform::UpdateMatrix() 
{
	
	worldMatrix = Matrix44::Identity;
	worldMatrix *= Matrix44::CreateScaling(scale);
	worldMatrix *= Matrix44::CreateRotationFromQuaternion(rotate);
	worldMatrix *= Matrix44::CreateTranslation(position);

	if (parent != nullptr) {
		worldMatrix *= parent->worldMatrix;
	}
}

void WorldTransform::Transfer(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndexWorldTransform)
{
	constBuffer.MapPtr()->world = worldMatrix;
	constBuffer.SetGraphicsRootConstantBufferView(cmdList, rootParameterIndexWorldTransform);
}
