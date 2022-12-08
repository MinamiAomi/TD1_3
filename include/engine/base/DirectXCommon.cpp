#include "DirectXCommon.h"
#include <cassert>
#include <d3dx12.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")



DirectXCommon* DirectXCommon::GetInstance() 
{
	static DirectXCommon instance;
	return &instance;
}

void DirectXCommon::Initialize(WinApp* winApp) 
{
	m_winApp = winApp;

#ifdef _DEBUG
	DebugLayer();
#endif // _DEBUG

	CreateFactory();
	CreateDevice();

#ifdef _DEBUG
	DebugSuppressError();
#endif // _DEBUG

	CreateCommand();
	CreateSwapChain();
	CreateRenderTargetView();
	CreateDepthBuffer();
	CreateFence();

	m_isInit = true;
}

void DirectXCommon::PreDraw() 
{
	// �o�b�N�o�b�t�@�̔ԍ����擾�i�Q�Ȃ̂łO�Ԃ��P�ԁj
	UINT bbIndex = m_swapChain->GetCurrentBackBufferIndex();

	D3D12_RESOURCE_BARRIER barrierDesc = CD3DX12_RESOURCE_BARRIER::Transition(
		m_backBuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_cmdList->ResourceBarrier(1, &barrierDesc);

	// �����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	// �[�x�X�e���V���r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
	m_cmdList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);
	
	// ��ʃN���A
	FLOAT clearcolor[] = { m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w };
	m_cmdList->ClearRenderTargetView(rtvHandle, clearcolor, 0, nullptr);
	m_cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// �r���[�|�[�g
	SetViewport(0.0f, 0.0f, static_cast<float>(m_winApp->GetWindowWidth()), static_cast<float>(m_winApp->GetWindowHeight()));
	// �V�U�[��`
	SetScissorRect(0, 0, m_winApp->GetWindowWidth(), m_winApp->GetWindowHeight());

}

void DirectXCommon::SetViewport(float left, float top, float width, float height) {
	// �r���[�|�[�g
	D3D12_VIEWPORT viewport =
		CD3DX12_VIEWPORT(left, top, width, height);
	m_cmdList->RSSetViewports(1, &viewport);
}
void DirectXCommon::SetScissorRect(int left, int top, int right, int bottom) {
	// �V�U�[��`
	D3D12_RECT scissorRect = CD3DX12_RECT(left, top, right, bottom);
	m_cmdList->RSSetScissorRects(1, &scissorRect);
}

void DirectXCommon::PostDraw() 
{
	HRESULT result = S_FALSE;
	// �o�b�N�o�b�t�@�̔ԍ����擾�i�Q�Ȃ̂łO�Ԃ��P�ԁj
	UINT bbIndex = m_swapChain->GetCurrentBackBufferIndex();
	
	D3D12_RESOURCE_BARRIER barrierDesc = CD3DX12_RESOURCE_BARRIER::Transition(
		m_backBuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT);
	// ���\�[�X�o���A��߂�
	m_cmdList->ResourceBarrier(1, &barrierDesc);

	// ���߂̃N���[�Y
	result = m_cmdList->Close();
	assert(SUCCEEDED(result));

	// �R�}���h���X�g�̎��s
	ID3D12CommandList* cmdLists[] = { m_cmdList.Get() };
	m_cmdQueue->ExecuteCommandLists(1, cmdLists);

	// ��ʂɕ\������o�b�t�@���t���b�v�i���\�̓���ւ��j
	result = m_swapChain->Present(1, 0);
	assert(SUCCEEDED(result));

	// �R�}���h�̎��s������҂�
	m_cmdQueue->Signal(m_fence.Get(), ++m_fenceVal);
	if (m_fence->GetCompletedValue() != m_fenceVal) {
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		m_fence->SetEventOnCompletion(m_fenceVal, event);
		if (event != 0) {
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
	}
	// �L���[���N���A
	result = m_cmdAllocator->Reset();
	assert(SUCCEEDED(result));
	// �ĂуR�}���h���X�g�����߂鏀��
	result = m_cmdList->Reset(m_cmdAllocator.Get(), nullptr);
	assert(SUCCEEDED(result));
}

DirectXCommon::ComPtr<ID3D12Resource> DirectXCommon::CreateResourceBuffer(UINT64 size) {
	HRESULT result = S_FALSE;
	ComPtr<ID3D12Resource> tmpBuffer;

	D3D12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(size);
	// �o�b�t�@�̐���
	result = m_device->CreateCommittedResource(
		&heapProp, D3D12_HEAP_FLAG_NONE,
		&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&tmpBuffer));
	assert(SUCCEEDED(result));

	return tmpBuffer;
}

void DirectXCommon::CreateFactory()
{
	HRESULT result = S_FALSE;
	// DXGI�t�@�N�g���[�̐���
	result = CreateDXGIFactory(IID_PPV_ARGS(&m_dxgiFactory));
	assert(SUCCEEDED(result));
}

void DirectXCommon::CreateDevice()
{
	HRESULT result = S_FALSE;
	// �A�_�v�^�[�̗񋓗p
	std::vector<ComPtr<IDXGIAdapter4>> adapters;
	// �����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	ComPtr<IDXGIAdapter4> tmpAdapter = nullptr;

	// �p�t�H�[�}���X���������̂��珇�ɁA���ׂẴA�_�v�^�[��񋓂���
	for (UINT i = 0;
		m_dxgiFactory->EnumAdapterByGpuPreference(
			i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++) {
		adapters.push_back(tmpAdapter); // �z��ɒǉ�����
	}

	// �Ó��ȃA�_�v�^��I�ʂ���
	for (auto& it : adapters) {
		DXGI_ADAPTER_DESC3 adapterDesc;
		// �A�_�v�^�[�̏����擾����
		it->GetDesc3(&adapterDesc);
		// �\�t�g�E�F�A�f�o�C�X�����
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			tmpAdapter = it;
			break;
		}
	}

	// �Ή����x���z��
	D3D_FEATURE_LEVEL levels[] =
	{ D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0, };

	D3D_FEATURE_LEVEL featureLevel;
	for (auto& it : levels) {
		result = D3D12CreateDevice(tmpAdapter.Get(), it, IID_PPV_ARGS(&m_device));
		if (result == S_OK) {
			featureLevel = it;
			break;
		}
	}

}

void DirectXCommon::CreateCommand()
{
	HRESULT result = S_FALSE;
	// �R�}���h�A���P�[�^�𐶐�
	result = m_device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_cmdAllocator));
	assert(SUCCEEDED(result));

	// �R�}���h���X�g�𐶐�
	result = m_device->CreateCommandList(
		0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cmdAllocator.Get(), nullptr, IID_PPV_ARGS(&m_cmdList));
	assert(SUCCEEDED(result));

	// �R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	// �R�}���h�L���[�𐶐�
	result = m_device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&m_cmdQueue));
	assert(SUCCEEDED(result));

}

void DirectXCommon::CreateSwapChain()
{
	HRESULT result = S_FALSE;
	// �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};

	swapChainDesc.Width = m_winApp->GetWindowWidth();
	swapChainDesc.Height = m_winApp->GetWindowHeight();
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �F���̏���
	swapChainDesc.SampleDesc.Count = 1; // �}���`�T���v�����Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER; // �o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2; // �o�b�t�@�����Q�ݒ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ComPtr<IDXGISwapChain1> swapChain1;

	result = m_dxgiFactory->CreateSwapChainForHwnd(
		m_cmdQueue.Get(), m_winApp->GetHwnd(), &swapChainDesc, 
		nullptr, nullptr, &swapChain1);
	assert(SUCCEEDED(result));

	// ��������IDXGISwapChain1�̃I�u�W�F�N�g��IDXGISwapChain4�ɕϊ�����
	result = swapChain1.As(&m_swapChain);
	assert(SUCCEEDED(result));
}

void DirectXCommon::CreateRenderTargetView()
{
	HRESULT result = S_FALSE;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	result = m_swapChain->GetDesc(&swapChainDesc);
	assert(SUCCEEDED(result));

	// �f�X�N���v�^�q�[�v�̐���
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // �����_�[�^�[�Q�b�g�r���[�Ȃ̂� RTV
	rtvHeapDesc.NodeMask = 0;
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount; // �\���̂Q��
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE; // ���Ɏw��Ȃ�

	result = m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap));
	assert(SUCCEEDED(result));


	m_backBuffers.resize(swapChainDesc.BufferCount);
	// �X���b�v�`�F�[���̂��ׂẴo�b�t�@�ɂ��ď�������
	for (size_t i = 0; i < m_backBuffers.size(); i++) {
		// �X���b�v�`�F�[������o�b�t�@���擾
		result = m_swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&m_backBuffers[i]));
		assert(SUCCEEDED(result));
		// �f�X�N���v�^�q�[�v�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
		// �����\���ŃA�h���X�������
		rtvHandle.ptr += i * m_device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		// �����_�[�^�[�Q�b�g�r���[�̐ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		// �V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		// �����_�[�^�[�Q�b�g�r���[�̐���
		m_device->CreateRenderTargetView(m_backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}

void DirectXCommon::CreateDepthBuffer() {
	HRESULT result = S_FALSE;

	CD3DX12_RESOURCE_DESC depthResourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_D32_FLOAT, m_winApp->GetWindowWidth(), m_winApp->GetWindowHeight(), 1, 0, 1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

	CD3DX12_HEAP_PROPERTIES depthHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	CD3DX12_CLEAR_VALUE depthClearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);

	result = m_device->CreateCommittedResource(
		&depthHeapProp,	D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,	D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue, IID_PPV_ARGS(&m_depthBuff));
	assert(SUCCEEDED(result));

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	result = m_device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&m_dsvHeap));
	assert(SUCCEEDED(result));

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	m_device->CreateDepthStencilView(
		m_depthBuff.Get(), &dsvDesc, m_dsvHeap->GetCPUDescriptorHandleForHeapStart());


}

void DirectXCommon::CreateFence()
{
	HRESULT result = S_FALSE;
	result = m_device->CreateFence(m_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
	assert(SUCCEEDED(result));
}


#ifdef _DEBUG
void DirectXCommon::DebugLayer() 
{
	ComPtr<ID3D12Debug1> _debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&_debugController)))) {
		_debugController->EnableDebugLayer();
		_debugController->SetEnableGPUBasedValidation(TRUE);
	}
}

void DirectXCommon::DebugSuppressError() 
{
	ComPtr<ID3D12InfoQueue> _infoQueue;
	if (SUCCEEDED(m_device->QueryInterface(IID_PPV_ARGS(&_infoQueue)))) {
		D3D12_MESSAGE_ID denyIds[] = {
			/*
			 * Windows11�ł�DXGI�f�o�b�O���C���[��DX12�f�o�b�O���C���[�̑��ݍ�p�o�O�ɂ��G���[���b�Z�[�W
			 * https://stackoverflow.com/questions/69805245/directx-12-application-is-crashing-in-windows-11
			 */
			 D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};
		// �}������\�����x��
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter = {};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		// �w�肵���G���[�̕\����}������
		_infoQueue->PushStorageFilter(&filter);
		// �G���[���Ƀu���[�N�𔭐�������
		_infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
		_infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
	}
}
#endif // _DEBUG