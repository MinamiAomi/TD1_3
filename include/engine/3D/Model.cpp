#include "Model.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Object3D.h"
#include <d3dcompiler.h>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <iomanip>

#pragma comment(lib,"d3dcompiler.lib")

DirectXCommon* Model::diXCom = nullptr;
TextureManager* Model::texMana = nullptr;
std::string Model::directory;
Model::ComPtr<ID3D12RootSignature> Model::rootSignature; // ���[�g�V�O�l�`��
Model::ComPtr<ID3D12PipelineState> Model::pipelineState; // �p�C�v���C���X�e�[�g
std::unique_ptr<Material> Model::defaultMaterial;

std::vector<std::string> Split(const std::string& instr, const char* delim) {
	std::vector<std::string> result;
	std::string str = instr;
	char* context = nullptr;
	char* token = strtok_s(const_cast<char*>(str.c_str()), delim, &context);
	while (token != nullptr)
	{
		result.push_back(std::string(token));
		token = strtok_s(nullptr, delim, &context);
	}
	return result;
}

void Model::StaticInitalize(DirectXCommon* dixcom, TextureManager* texmana, const std::string& dir)
{
	assert(dixcom != nullptr);
	assert(texmana != nullptr);

	diXCom = dixcom;
	texMana = texmana;
	directory = dir;

	HRESULT result = S_FALSE;

	ComPtr<ID3DBlob> vsBlob; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob; // �G���[�I�u�W�F�N�g

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"ModelVS.hlsl", // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0, &vsBlob, &errorBlob);

#ifdef _DEBUG
	ShalderFileLoadCheak(result, errorBlob.Get());
#endif // _DEBUG

	result = D3DCompileFromFile(
		L"ModelPS.hlsl", // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0, &psBlob, &errorBlob);

#ifdef _DEBUG
	ShalderFileLoadCheak(result, errorBlob.Get());
#endif // _DEBUG


	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};


	// ���[�g�V�O�l�`��

	// �f�B�X�N���v�^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange =
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	// ���[�g�p�����[�^
	CD3DX12_ROOT_PARAMETER rootParams[kRootParameterCount] = {};
	rootParams[kWorldTransform].InitAsConstantBufferView(0);
	rootParams[kCamera].InitAsConstantBufferView(1);
	rootParams[kMaterial].InitAsConstantBufferView(2);
	rootParams[kTexture].InitAsDescriptorTable(1, &descriptorRange);


	// �e�N�X�`���T���v���[�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	// ���[�g�V�O�l�`���ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams; // ���[�g�p�����[�^�̐擪�A�h���X
	rootSignatureDesc.NumParameters = _countof(rootParams);		// ���[�g�p�����[�^�̐�
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;

	// ���[�g�V�O�l�`���̃V���A���C�Y
	ComPtr<ID3DBlob> rootSigBlob;
	result = D3D12SerializeRootSignature(&rootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));

	result = diXCom->GetDevice()->CreateRootSignature(0,
		rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(result));


	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};
	// �V�F�[�_�̐ݒ�
	pipelineDesc.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	pipelineDesc.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	// �T���v���}�X�N�ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // �J�����O���Ȃ�
	//pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME; // ���C���[�t���[��

	pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RGBA���ׂẴ`�����l����`��
	pipelineDesc.BlendState.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;			// ���Z
	pipelineDesc.BlendState.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;				// �\�[�X�̒l�� 100% �g��
	pipelineDesc.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;			// �f�X�g�̒l��   0% �g��
	pipelineDesc.BlendState.RenderTarget[0].BlendEnable = true;						// �u�����h��L���ɂ���
	pipelineDesc.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;				// ���Z
	pipelineDesc.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;			// �\�[�X�̃A���t�@�l
	pipelineDesc.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;	// 1.0f-�\�[�X�̃A���t�@�l

	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ͂P��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0 ~ 255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // �P�s�N�Z���ɒ����P��T���v�����O

	pipelineDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = rootSignature.Get();

	// �p�C�v���C���X�e�[�g�̐���
	result = diXCom->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));

#pragma endregion

	defaultMaterial = std::move(Material::Create());
	defaultMaterial->CreateBuffer(dixcom->GetDevice());
	defaultMaterial->SetTextureHandle(0); // �^�����摜

}

std::unique_ptr<Model> Model::CreateFromObj(const std::string& path)
{
	// �p�X��.obj���܂܂�Ă���
	assert(strstr(path.c_str(), ".obj") !=  NULL);
	
	auto splitPath = Split(path, "/");
	std::string modelFileDirectory = directory;

	for (size_t i = 0; i < splitPath.size() - 1; i++) {
		modelFileDirectory = modelFileDirectory + splitPath[i] + "/";
	}
	
	std::string objFilePath = directory + path;

	std::ifstream objfile(objFilePath);
	// �t�@�C�� ���J���Ȃ��ꍇ
	assert(objfile);

	// ��������郂�f��
	std::unique_ptr<Model> result(new Model);

	// �o�b�t�@
	std::string mtlFilePath; // mtl�t�@�C���p�X
	std::vector<Vector3> posbuf; // ���W
	std::vector<Vector3> normalbuf; // �@��
	std::vector<Vector2> uvbuf; // uv

	std::vector<Meth::Vertex> vertcies; // ���_�C���f�b�N�X
	std::vector<std::string> indexKeys; // �C���f�b�N�X�̃L�[
	std::map<std::string, int> entryVertexIds;

	std::string currentMtlName;
	Meth* currentMeth = nullptr;

	std::string line;
	// �t�@�C���I���܂�
	while (std::getline(objfile, line)) {
		// ���ݓǂݍ���ł���}�e���A���̖��O

		if (line.empty()) { // ��̍s�͔�΂�
			continue;
		}
		std::istringstream iss(line);	// �X�y�[�X�ŋ�؂� 
		std::string token;
		iss >> token; // �擪�̗v�f���g�[�N���ɂȂ�

		if (token == "v") {	// ���_���W
			Vector3 tmp;
			iss >> tmp.x >> tmp.y >> tmp.z;
			posbuf.emplace_back(tmp);
		}
		else if (token == "vn") { // �@��
			Vector3 tmp;
			iss >> tmp.x >> tmp.y >> tmp.z;
			normalbuf.emplace_back(tmp);
		}
		else if (token == "vt") { // uv
			Vector2 tmp;
			iss >> tmp.x >> tmp.y;
			tmp.y = 1.0f - tmp.y; // obj�t�@�C����uv���W��y�������]���Ă��邽��
			uvbuf.emplace_back(tmp);
		}
		else if (token == "mtllib") { // mtl�t�@�C���̃p�X
			iss >> mtlFilePath;
			mtlFilePath = modelFileDirectory + mtlFilePath;
		}
		else if (token == "usemtl") { // �}�e���A���̐ݒ�
			iss >> currentMtlName;
			// �}�e���A���ƑΉ����郁�b�V���𐶐�
			result->m_materials[currentMtlName] = Material::Create();
			result->m_materials[currentMtlName]->SetName(currentMtlName);
			auto newMeth = Meth::Create();
			newMeth->SetMaterial(result->m_materials[currentMtlName].get());
			currentMeth = newMeth.get();
			result->m_meths.emplace_back(std::move(newMeth));
		}
		else if (token == "f") { // �C���f�b�N�X

			if (currentMeth == nullptr) {
				auto newMeth = Meth::Create();
				newMeth->SetMaterial(defaultMaterial.get());
				currentMeth = newMeth.get();
				result->m_meths.emplace_back(std::move(newMeth));
			}

			Meth::Vertex tmpV = {};
			std::string vertIndex;
			int v = 0, vn = 0, vt = 0;
			for (int i = 0; i < 3; i++) {
				std::ostringstream sout;
				iss >> vertIndex;
				sscanf_s(vertIndex.c_str(), "%d/%d/%d", &v, &vt, &vn);

				tmpV.position = posbuf[v - 1];
				tmpV.normal = normalbuf[vn - 1];
				tmpV.uv = uvbuf[vt - 1];

				sout << std::setfill('0') << std::setw(5) << v;
				sout << std::setfill('0') << std::setw(5) << vt;
				sout << std::setfill('0') << std::setw(5) << vn;
				auto key = sout.str();
				if (entryVertexIds.count(key) > 0) {
					currentMeth->AddIndex(entryVertexIds[key]);
				}
				else {
					currentMeth->AddVertex(tmpV);
					UINT index = currentMeth->GetVertexCount() - 1;
					currentMeth->AddIndex(index);
					entryVertexIds[key] = index;
				}


			}
		}
	}


	objfile.close();

	if (result->m_materials.empty() == false) {

		std::ifstream mtlfile(mtlFilePath);
		assert(mtlfile);

		Material* currentMaterial = result->m_materials.begin()->second.get();

		while (std::getline(mtlfile, line)) {
			// ���ݓǂݍ���ł���}�e���A���̖��O

			if (line.empty()) { // ��̍s�͔�΂�
				continue;
			}
			std::istringstream iss(line);	// �X�y�[�X�ŋ�؂� 
			std::string token;
			iss >> token; // �擪�̗v�f���g�[�N���ɂȂ�

			if (token == "newmtl") { // �}�e���A��
				iss >> currentMtlName;
				currentMaterial = result->m_materials[currentMtlName].get();
			}
			else if (token == "Ka") { // �A���r�G���g
				Vector3 tmp = {};
				iss >> tmp.x >> tmp.y >> tmp.z;
				currentMaterial->m_ambient = tmp;
			}
			else if (token == "Kd") { // �f�B�t���[�Y
				Vector3 tmp = {};
				iss >> tmp.x >> tmp.y >> tmp.z;
				currentMaterial->m_diffuse = tmp;
			}
			else if (token == "Ks") { // �X�y�L�����[
				Vector3 tmp = {};
				iss >> tmp.x >> tmp.y >> tmp.z;
				currentMaterial->m_specular = tmp;
			}
			else if (token == "Ni") { // ����x
				float tmp = 0.0f;
				iss >> tmp;
				currentMaterial->m_shininess = tmp;
			}
			else if (token == "d") { // �����x
				float tmp = 0.0f;
				iss >> tmp;
				currentMaterial->m_alpha = tmp;
			}
			else if (token == "map_Kd") { // �e�N�X�`���p�X
				std::string tmp;
				iss >> tmp;
				auto texPath = modelFileDirectory + tmp;
				currentMaterial->SetTexFileName(texPath);
				currentMaterial->SetTextureHandle(texMana->LoadTexture(texPath));
				
			}
		}
	}




	for (auto& it : result->m_meths) {
		
		it->CreateBuffer(diXCom->GetDevice());
	}
	for (auto& it : result->m_materials) {
		it.second->CreateBuffer(diXCom->GetDevice());
	}

	return std::move(result);

}

void Model::Draw(ID3D12GraphicsCommandList* cmdList, Object3D* object)
{
	for (auto& it : m_meths) {
		cmdList->SetGraphicsRootSignature(rootSignature.Get());
		cmdList->SetPipelineState(pipelineState.Get());
		cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		object->Transfer(cmdList);
		it->Draw(cmdList, kMaterial, kTexture);
	}
}
