#include "Input.h"
#include <cassert>
#include <Windows.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment (lib, "xinput.lib")

Input* Input::GetInstance() 
{
	static Input instance;
	return &instance;
}

void Input::Initialize(WinApp* winApp)
{
	m_winApp = winApp;

	HRESULT result = S_FALSE;
	// DirectInputの初期化
	result = DirectInput8Create(
		m_winApp->GetHInstance(), DIRECTINPUT_HEADER_VERSION,
		IID_IDirectInput8, (void**)&m_directInput, nullptr);
	assert(SUCCEEDED(result));

	// キーボードデバイスの生成
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	assert(SUCCEEDED(result));
	// 入力データー形式のセット
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));
	// 排他制御レベルのセット
	result = m_keyboard->SetCooperativeLevel(
		m_winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

	// マウスデバイスの生成
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	assert(SUCCEEDED(result));
	// 入力データー形式のセット
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	assert(SUCCEEDED(result));
	// 排他制御レベルのセット
	result = m_mouse->SetCooperativeLevel(
		m_winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update() {
	memcpy(m_preKeys, m_curkeys, kKeyDataNum);
	// キーボード情報の取得開始
	m_keyboard->Acquire();
	// 全キーの入力状態を取得する
	m_keyboard->GetDeviceState(sizeof(m_curkeys), m_curkeys);
	
	m_preMouseState = m_curMouseState;
	// マウス情報の取得開始
	m_mouse->Acquire();
	// マウスの状態を取得する
	m_mouse->GetDeviceState(sizeof(DIMOUSESTATE),&m_curMouseState);

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(m_winApp->GetHwnd(), &p);
	m_mousePos = { (float)p.x,(float)p.y };

	// xinputの最大接続数
	static constexpr size_t kXInputConnectMaxCount = 4;
	// 現在の状態を前回の状態に保存
	for (auto& it : m_gamePads) {
		it.preState = it.curState;
	}
	XINPUT_STATE tmpState = {};
	for (size_t i = 0; i < kXInputConnectMaxCount; i++) {
		auto success = XInputGetState((DWORD)i, &tmpState);
		if (success == ERROR_SUCCESS) {
			if (m_gamePads.size() <= i) {
				m_gamePads.emplace_back();
			}
			m_gamePads.at(i).curState = tmpState;
		}
	}
}