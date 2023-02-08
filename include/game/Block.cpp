#include "Block.h"
#include "CameraTransform.h"
#include "Model.h"
#include "Resources.h"
#include "SceneManager.h"
#include "SceneCommonData.h"
#include "DirectXCommon.h"


#include <d3dcompiler.h>
#include <cassert>

#pragma comment(lib,"d3dcompiler.lib")

float Block::s_zWidth = 5;
CameraTransform* Block::s_camera = nullptr;

Block::ComPtr<ID3D12RootSignature> Block::rootSignature; // ルートシグネチャ
Block::ComPtr<ID3D12PipelineState> Block::pipelineState; // パイプラインステート
VertexBuffer<Block::Vertex> Block::m_vertBuff;
IndexBuffer Block::m_indexBuff;
std::vector<Block::Vertex> Block::m_vertcies;
std::vector<uint16_t> Block::m_indcies;

void Block::StaticInitalize()
{
	auto dev = DirectXCommon::GetInstance()->GetDevice();

	HRESULT result = S_FALSE;

	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob; // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"./resources/shaders/BlockVS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0, &vsBlob, &errorBlob);

#ifdef _DEBUG
	ShalderFileLoadCheak(result, errorBlob.Get());
#endif // _DEBUG

	result = D3DCompileFromFile(
		L"./resources/shaders/BlockPS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
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
		}
	};


	// ルートシグネチャ

	// ディスクリプタレンジ
	D3D12_DESCRIPTOR_RANGE descriptorRange =
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	// ルートパラメータ
	CD3DX12_ROOT_PARAMETER rootParams[kRootParameterIndexCount] = {};
	rootParams[kRootParameterIndexWorldTransform].InitAsConstantBufferView(0);
	rootParams[kRootParameterIndexCameraTransform].InitAsConstantBufferView(1);
	rootParams[kRootParameterIndexColor].InitAsConstantBufferView(2);


	// テクスチャサンプラーの設定
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

	// ルートシグネチャ設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams; // ルートパラメータの先頭アドレス
	rootSignatureDesc.NumParameters = _countof(rootParams);		// ルートパラメータの数
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;

	// ルートシグネチャのシリアライズ
	ComPtr<ID3DBlob> rootSigBlob;
	result = D3D12SerializeRootSignature(&rootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));

	result = dev->CreateRootSignature(0,
		rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(result));


	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};
	// シェーダの設定
	pipelineDesc.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	pipelineDesc.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	// サンプルマスク設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	// ラスタライザの設定
	pipelineDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // カリングしない
	//pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME; // ワイヤーフレーム

	pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RGBAすべてのチャンネルを描画
	pipelineDesc.BlendState.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;			// 加算
	pipelineDesc.BlendState.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;				// ソースの値を 100% 使う
	pipelineDesc.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;			// デストの値を   0% 使う
	pipelineDesc.BlendState.RenderTarget[0].BlendEnable = true;						// ブレンドを有効にする
	pipelineDesc.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;				// 加算
	pipelineDesc.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;			// ソースのアルファ値
	pipelineDesc.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;	// 1.0f-ソースのアルファ値

	// 頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

	// 図形の形状設定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	pipelineDesc.NumRenderTargets = 1; // 描画対象は１つ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0 ~ 255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1; // １ピクセルに着き１回サンプリング

	pipelineDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	// パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = rootSignature.Get();

	// パイプラインステートの生成
	result = dev->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));

	

	m_vertcies = {	// 前
			{ {	-1.0f, -1.0f,  -1.0f }, { 0.0f, 0.0f, 1.0f } },	// 左下
			{ { -1.0f,  1.0f,  -1.0f }, { 0.0f, 0.0f, 1.0f } },	// 左上
			{ {  1.0f, -1.0f,  -1.0f }, { 0.0f, 0.0f, 1.0f } },	// 右下
			{ {  1.0f,  1.0f,  -1.0f }, { 0.0f, 0.0f, 1.0f } },	// 右上
			// 後
			{ {	-1.0f, -1.0f,   1.0f }, { 0.0f, 0.0f, -1.0f } },	// 左下
			{ { -1.0f,  1.0f,   1.0f }, { 0.0f, 0.0f, -1.0f } },	// 左上
			{ {  1.0f, -1.0f,   1.0f }, { 0.0f, 0.0f, -1.0f } },	// 右下
			{ {  1.0f,  1.0f,   1.0f }, { 0.0f, 0.0f, -1.0f } },	// 右上
			// 左
			{ {	-1.0f, -1.0f,  -1.0f }, { -1.0f, 0.0f, 0.0f } },	// 左下
			{ { -1.0f, -1.0f,   1.0f }, { -1.0f, 0.0f, 0.0f } },	// 左上
			{ { -1.0f,  1.0f,  -1.0f }, { -1.0f, 0.0f, 0.0f } },	// 右下
			{ { -1.0f,  1.0f,   1.0f }, { -1.0f, 0.0f, 0.0f } },	// 右上
			// 右
			{ {	 1.0f, -1.0f,  -1.0f }, { 1.0f, 0.0f, 0.0f } },	// 左下
			{ {  1.0f, -1.0f,   1.0f }, { 1.0f, 0.0f, 0.0f } },	// 左上
			{ {  1.0f,  1.0f,  -1.0f }, { 1.0f, 0.0f, 0.0f } },	// 右下
			{ {  1.0f,  1.0f,   1.0f }, { 1.0f, 0.0f, 0.0f } },	// 右上
			// 上
			{ {	-1.0f,  1.0f,  -1.0f }, { 0.0f, 1.0f, 0.0f } },	// 左下
			{ {  1.0f,  1.0f,  -1.0f }, { 0.0f, 1.0f, 0.0f } },	// 左上
			{ { -1.0f,  1.0f,   1.0f }, { 0.0f, 1.0f, 0.0f } },	// 右下
			{ {  1.0f,  1.0f,   1.0f }, { 0.0f, 1.0f, 0.0f } },	// 右上
			// 下
			{ {	-1.0f, -1.0f,  -1.0f }, { 0.0f, -1.0f, 0.0f } },	// 左下
			{ {  1.0f, -1.0f,  -1.0f }, { 0.0f, -1.0f, 0.0f } },	// 左上
			{ { -1.0f, -1.0f,   1.0f }, { 0.0f, -1.0f, 0.0f } },	// 右下
			{ {  1.0f, -1.0f,   1.0f }, { 0.0f, -1.0f, 0.0f } },	// 右上
	};

	m_indcies =
	{ 0, 1, 2,
		2, 1, 3,

		5, 4, 6,
		5, 6, 7,

		8, 9,10,
	   10, 9,11,

	   13,12,14,
	   13,14,15,

	   17,16,18,
	   17,18,19,

	   21,22,20,
	   22,21,23
	};

	// 頂点バッファを生成
	m_vertBuff.Create(dev, (UINT)m_vertcies.size());
	m_vertBuff.Map();
	std::copy(m_vertcies.begin(), m_vertcies.end(), m_vertBuff.GetMapPtr());
	m_vertBuff.Unmap();
	// インデックスバッファを生成
	m_indexBuff.Create(dev, (UINT)m_indcies.size());
	m_indexBuff.Map();
	std::copy(m_indcies.begin(), m_indcies.end(), m_indexBuff.GetMapPtr());
	m_indexBuff.Unmap();

}

void Block::StaticDraw(WorldTransform* trans, ConstBuffer<ColorConstData>& constData)
{
	auto cmdList = DirectXCommon::GetInstance()->GetCommandList();
		cmdList->SetGraphicsRootSignature(rootSignature.Get());
		cmdList->SetPipelineState(pipelineState.Get());
		cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		trans->Transfer(cmdList, kRootParameterIndexWorldTransform);
		s_camera->Transfer(cmdList, kRootParameterIndexCameraTransform);
		m_vertBuff.IASet(cmdList);
		m_indexBuff.IASet(cmdList);
		constData.SetGraphicsRootConstantBufferView(cmdList, kRootParameterIndexColor);
		cmdList->DrawIndexedInstanced(m_indexBuff.GetIndexCount(), 1, 0, 0, 0);
}

Block::Block()
{
	m_model = nullptr;
	m_world.Initalize();

	m_constData.Create(DirectXCommon::GetInstance()->GetDevice());
	m_constData.Map();
	coll.Initalize();
}

Block::~Block()
{
	m_model = nullptr;
}


void Block::Initalize(const BlockJsonData& data, float z_width, WorldTransform* parent)
{
	m_model = Resource::GetInstance()->GetModel().cube.get();

	m_rect.center = data.position;
	m_rect.rotate = data.rotation;
	m_rect.width = data.width;
	m_rect.height = data.height;


	m_world.position = { m_rect.center,0.0f };
	m_world.scale = { m_rect.width,m_rect.height,z_width };
	m_world.rotate = Quaternion(m_rect.rotate, Vector3::UnitZ);

	m_world.parent = parent;

	m_collider.center = m_world.position.xy();
	Matrix33 rotMat = Matrix33::CreateRotation(m_rect.rotate);
	m_collider.direction[0] = rotMat.GetX();
	m_collider.direction[1] = rotMat.GetY();

	m_collider.size[0] = m_world.scale.x;
	m_collider.size[1] = m_world.scale.y;

	switch (m_type)
	{
	case Block::kBlockTypeNone:
		m_constData.MapPtr()->color = Color::Black;
		break;
	case Block::kBlockTypeSnow:
	default:
		m_constData.MapPtr()->color = Color::White;
		break;
	}
}

void Block::Initalize()
{
	m_model = Resource::GetInstance()->GetModel().cube.get();

	m_world.position = { m_rect.center,0.0f };
	m_world.scale = { m_rect.width,m_rect.height,s_zWidth };
	m_world.rotate = Quaternion(m_rect.rotate, Vector3::UnitZ);

	m_collider.center = m_world.position.xy();
	Matrix33 rotMat = Matrix33::CreateRotation(m_rect.rotate);
	m_collider.direction[0] = rotMat.GetX();
	m_collider.direction[1] = rotMat.GetY();

	m_collider.size[0] = m_world.scale.x;
	m_collider.size[1] = m_world.scale.y;

	switch (m_type)
	{
	case Block::kBlockTypeNone:
		m_constData.MapPtr()->color = Color::ToVector4(0x666666FF);
		break;
	case Block::kBlockTypeSnow:
	default:
		m_constData.MapPtr()->color = Color::White;
		break;
	}
}

void Block::Update()
{


}

void Block::PreCollision()
{
	m_world.UpdateMatrix();

	m_collider.center = m_world.worldMatrix.GetTranslation().xy();

	Matrix33 rotMat;
	if (m_world.parent != nullptr) {
		a = m_rect.rotate + m_world.parent->rotate.Angle();
		rotMat = Matrix33::CreateRotation(a);
	}
	else {
		a = m_rect.rotate;
		rotMat = Matrix33::CreateRotation(a);
	}

	m_collider.direction[0] = rotMat.GetX();
	m_collider.direction[1] = rotMat.GetY();

	m_collider.size[0] = m_rect.width ;
	m_collider.size[1] = m_rect.height;
}

void Block::PreCollision1(float a)
{
	m_world.UpdateMatrix();

	m_collider.center = m_world.worldMatrix.GetTranslation().xy();

	Matrix33 rotMat;
	this->a = a + m_rect.rotate;
	rotMat = Matrix33::CreateRotation(this->a);

	m_collider.direction[0] = rotMat.GetX();
	m_collider.direction[1] = rotMat.GetY();

	m_collider.size[0] = m_rect.width;
	m_collider.size[1] = m_rect.height;
}

void Block::PreCollision2()
{
	m_world.UpdateMatrix();

	m_collider.center = m_world.worldMatrix.GetTranslation().xy();

	m_collider.size[0] = m_rect.width * m_world.parent->scale.x;
	m_collider.size[1] = m_rect.height * m_world.parent->scale.y;
}

void Block::Draw()
{
	coll.position = Vector3(m_collider.center ,-1.0f);
	coll.scale = Vector3{ m_collider.size[0], m_collider.size[1],1.0f};
	coll.rotate = Quaternion::CreateFromAngleAxis(a, Vector3::UnitZ);
	
	coll.UpdateMatrix();
		

	m_world.UpdateMatrix();
	StaticDraw(&m_world,m_constData);
	//m_model->Draw(&m_world, s_camera);
	//Resource::GetInstance()->GetModel().axis->Draw(&coll, s_camera);
	//m_model->Draw(&coll, s_camera);
}

Block::operator BlockJsonData() const
{
	return { 0,m_rect.center,m_rect.rotate,m_rect.width,m_rect.height };
}
