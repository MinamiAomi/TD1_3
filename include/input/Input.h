#pragma once
#ifndef INPUT_H_
#define INPUT_H_

#include "WinApp.h"
#include <wrl.h>
#include <stdint.h>

#include <Xinput.h>
#define DIRECTINPUT_VERSION 0x0800 // DirectIput�̃o�[�W�����w��
#include <dinput.h>

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

	BYTE mKeys[kKeyDataNum] = {};
	BYTE mPreKeys[kKeyDataNum] = {};

public: // �ÓI�����o�֐�
	static Input* GetInstance();

public: // �����o�֐�
	void Initialize(WinApp* winApp);
	void Update();

	inline bool IsKeyPressed(uint8_t keycode) const { return mKeys[keycode] != 0; }
	inline bool IsKeyEmpty(uint8_t keycode) const { return mKeys[keycode] == 0; }
	inline bool IsKeyTrigger(uint8_t keycode) const { return mPreKeys[keycode] == 0 && mKeys[keycode] != 0; }
	inline bool IsKeyRelease(uint8_t keycode) const { return mPreKeys[keycode] != 0 && mKeys[keycode] == 0; }

};

#endif // INPUT_H_
