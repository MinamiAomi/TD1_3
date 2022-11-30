#include "PipelineFunc.h"
#include <string>
#include <cassert>


void SetBlendState(D3D12_RENDER_TARGET_BLEND_DESC& blendDesc, BlendMode blendmode)
{
	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RGBA���ׂẴ`�����l����`��
	blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;			// ���Z
	blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;				// �\�[�X�̒l�� 100% �g��
	blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;			// �f�X�g�̒l��   0% �g��

	switch (blendmode)
	{
		//case kBlendModeNone:
		//	blendDesc.BlendEnable = false;						// �u�����h���Ȃ�
		//	return;
		//default:
	case kBlendModeNormal:
		blendDesc.BlendEnable = true;						// �u�����h��L���ɂ���
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;				// ���Z
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;			// �\�[�X�̃A���t�@�l
		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;	// 1.0f-�\�[�X�̃A���t�@�l
		return;
		//case kBlendModeAdd:
		//	blendDesc.BlendEnable = true;						// �u�����h��L���ɂ���
		//	blendDesc.BlendOp = D3D12_BLEND_OP_ADD;				// ���Z
		//	blendDesc.SrcBlend = D3D12_BLEND_ONE;				// �\�[�X�̒l�� 100% �g��
		//	blendDesc.DestBlend = D3D12_BLEND_ONE;				// �f�X�g�̒l�� 100% �g��
		//	return;
		//case kBlendModeSubtract:
		//	blendDesc.BlendEnable = true;						// �u�����h��L���ɂ���
		//	blendDesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;	// �f�X�g����\�[�X�����Z
		//	blendDesc.SrcBlend = D3D12_BLEND_ONE;				// �\�[�X�̒l�� 100% �g��
		//	blendDesc.DestBlend = D3D12_BLEND_ONE;				// �f�X�g�̒l�� 100% �g��
		//	return;
		//case kBlendModeMultiply:
		//	blendDesc.BlendEnable = true;						// �u�����h��L���ɂ���
		//	blendDesc.BlendOp = D3D12_BLEND_OP_ADD;				// ���Z
		//	blendDesc.SrcBlend = D3D12_BLEND_ZERO;				// �g��Ȃ�
		//	blendDesc.DestBlend = D3D12_BLEND_SRC_COLOR;		// �f�X�g�̒l �~ �\�[�X�̒l
		//	return;
		//case kBlendModeInversion:
		//	blendDesc.BlendEnable = true;						// �u�����h��L���ɂ���
		//	blendDesc.BlendOp = D3D12_BLEND_OP_ADD;				// ���Z
		//	blendDesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;	// 1.0f-�f�X�g�J���[�̒l
		//	blendDesc.DestBlend = D3D12_BLEND_ZERO;				// �g��Ȃ�
		//	return;
	}
}


#ifdef _DEBUG
void ShalderFileLoadCheak(const HRESULT& result, ID3DBlob* errorBlob)
{
	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}
}
#endif // _DEBUG
