#pragma once
#ifndef INPUT_H_
#define INPUT_H_

#include "WinApp.h"
#include <wrl.h>
#include <stdint.h>
#include <Xinput.h>
#define DIRECTINPUT_VERSION 0x0800 // DirectIputのバージョン指定
#include <dinput.h>

#include "Vector2.h"

#define MOOUSE_ON_VALUE 0x80

enum MouseButton 
{
	kMouseButtonLeft,
	kMouseButtonRight,
	kMouseButtonMid,
};

class Input 
{

private:
	template<class TYPE>
	using ComPtr = Microsoft::WRL::ComPtr<TYPE>;
	static constexpr int kKeyDataNum = 256;

private:
	WinApp* m_winApp = nullptr;

	ComPtr<IDirectInput8> m_directInput;
	ComPtr<IDirectInputDevice8> m_keyboard;
	ComPtr<IDirectInputDevice8> m_mouse;

	BYTE m_keys[kKeyDataNum] = {};
	BYTE m_preKeys[kKeyDataNum] = {};

	DIMOUSESTATE2 m_curMouseState = {};
	DIMOUSESTATE2 m_preMouseState = {};
	Vector2 m_mousePos;
	

public: // 静的メンバ関数
	static Input* GetInstance();

public: // メンバ関数
	void Initialize(WinApp* winApp);
	void Update();

	inline bool IsKeyPressed(uint8_t keycode) const { return m_keys[keycode] != 0; }
	inline bool IsKeyEmpty(uint8_t keycode) const { return m_keys[keycode] == 0; }
	inline bool IsKeyTrigger(uint8_t keycode) const { return m_preKeys[keycode] == 0 && m_keys[keycode] != 0; }
	inline bool IsKeyRelease(uint8_t keycode) const { return m_preKeys[keycode] != 0 && m_keys[keycode] == 0; }

	inline bool IsMousePressed(MouseButton buttontype) const {
		return m_curMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE;
	}
	inline bool IsMouseEmpty(MouseButton buttontype) const {
		return !(m_curMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE);
	}
	inline bool IsMouseTrigger(MouseButton buttontype) const {
		return !(m_preMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE) &&
			m_curMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE;
	}
	inline bool IsMouseRelease(MouseButton buttontype) const {
		return m_preMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE &&
			!(m_curMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE);
	}

};

#endif // INPUT_H_
