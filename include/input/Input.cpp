#include "Input.h"

#include <cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

Input* Input::GetInstance() 
{
	static Input instance;
	return &instance;
}

void Input::Initialize(WinApp* winApp)
{
	HRESULT result = S_FALSE;
	// DirectInput�̏�����
	result = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_HEADER_VERSION, 
		IID_IDirectInput8, (void**)&m_directInput, nullptr);
	assert(SUCCEEDED(result));
	// �L�[�{�[�h�f�o�C�X�̐���
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	assert(SUCCEEDED(result));
	// ���̓f�[�^�[�`���̃Z�b�g
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));
	// �r�����䃌�x���̃Z�b�g
	result = m_keyboard->SetCooperativeLevel(
		winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update() {
	memcpy(mPreKeys, mKeys, kKeyDataNum);
	// �L�[�{�[�h���̎擾�J�n
	m_keyboard->Acquire();
	// �S�L�[�̓��͏�Ԃ��擾����
	m_keyboard->GetDeviceState(sizeof(mKeys), mKeys);
}