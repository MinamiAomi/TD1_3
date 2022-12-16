#include "Input.h"
#include <cassert>
#include <Windows.h>

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

	// �}�E�X�f�o�C�X�̐���
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	assert(SUCCEEDED(result));
	// ���̓f�[�^�[�`���̃Z�b�g
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	assert(SUCCEEDED(result));
	// �r�����䃌�x���̃Z�b�g
	result = m_mouse->SetCooperativeLevel(
		winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update() {
	memcpy(m_preKeys, m_keys, kKeyDataNum);
	// �L�[�{�[�h���̎擾�J�n
	m_keyboard->Acquire();
	// �S�L�[�̓��͏�Ԃ��擾����
	m_keyboard->GetDeviceState(sizeof(m_keys), m_keys);
	
	m_preMouseState = m_curMouseState;
	// �}�E�X���̎擾�J�n
	m_mouse->Acquire();
	// �}�E�X�̏�Ԃ��擾����
	m_mouse->GetDeviceState(sizeof(DIMOUSESTATE),&m_curMouseState);

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(m_winApp->GetHwnd(), &p);
	m_mousePos = { (float)p.x,(float)p.y };
}