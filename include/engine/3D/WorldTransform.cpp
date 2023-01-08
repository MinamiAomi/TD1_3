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
	Matrix44 scaMat, rotMat, traMat;

	scaMat = Matrix44::CreateScaling(scale);

	//rotMat = Matrix44::CreateRotationFromEuler(rotation);

	//rotMat *= Matrix44::CreateRotationZ(rotate.z);
	//rotMat *= Matrix44::CreateRotationX(rotate.x);
	//rotMat *= Matrix44::CreateRotationY(rotate.y);

	rotMat = Matrix44::CreateRotationFromQuaternion(rotate);

	traMat = Matrix44::CreateTranslation(position);

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
