#pragma once
#ifndef INPUT_H_
#define INPUT_H_

#include "WinApp.h"
#include <wrl.h>
#include <stdint.h>
#include <Xinput.h>
#define DIRECTINPUT_VERSION 0x0800 // DirectIput�̃o�[�W�����w��
#include <dinput.h>
#include <vector>

#include "Vector2.h"
#include "Matrix44.h"

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

private:
	struct GamePad
	{
		XINPUT_STATE curState = {};
		XINPUT_STATE preState = {};
		BYTE triggerDeadZone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD; // �g���K�[�̃f�b�h�]�[��
		SHORT leftStickDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; // ���X�e�B�b�N�̃f�b�h�]�[��
		SHORT rightStickDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;	// �E�X�e�B�b�N�̃f�b�h�]�[��
	};

private:
	static constexpr int kKeyDataNum = 256;

private:
	WinApp* m_winApp = nullptr;

	ComPtr<IDirectInput8> m_directInput;
	ComPtr<IDirectInputDevice8> m_keyboard;
	ComPtr<IDirectInputDevice8> m_mouse;

	BYTE m_curkeys[kKeyDataNum] = {}; // ���݂̃L�[�̓��͏��
	BYTE m_preKeys[kKeyDataNum] = {}; // �O��̃L�[�̓��͏��

	DIMOUSESTATE2 m_curMouseState = {}; // ���݂̃}�E�X�̓��͏��
	DIMOUSESTATE2 m_preMouseState = {}; // �O��̃}�E�X�̓��͏��
	Vector2 m_mousePos;					// �}�E�X�̃X�N���[�����W
	
	std::vector<GamePad> m_gamePads;


public: // �ÓI�����o�֐�
	static Input* GetInstance();

public: // �����o�֐�
	void Initialize(WinApp* winApp);
	void Update();

	/// <summary>
	/// ������Ă���
	/// </summary>
	/// <param name="keycode">�L�[�R�[�h</param>
	/// <returns></returns>
	inline bool IsKeyPressed(uint8_t keycode) const;
	/// <summary>
	/// ������Ă��Ȃ�
	/// </summary>
	/// <param name="keycode">�L�[�R�[�h</param>
	/// <returns></returns>
	inline bool IsKeyEmpty(uint8_t keycode) const;
	/// <summary>
	/// �������u��
	/// </summary>
	/// <param name="keycode">�L�[�R�[�h</param>
	/// <returns></returns>
	inline bool IsKeyTrigger(uint8_t keycode) const;
	/// <summary>
	/// �������u��
	/// </summary>
	/// <param name="keycode">�L�[�R�[�h</param>
	/// <returns></returns>
	inline bool IsKeyRelease(uint8_t keycode) const;
	/// <summary>
	/// �}�E�X�{�^����������Ă���
	/// </summary>
	/// <param name="buttontype">�{�^���R�[�h</param>
	/// <returns></returns>
	inline bool IsMousePressed(MouseButton buttontype) const;
	/// <summary>
	/// �}�E�X�{�^����������Ă��Ȃ�
	/// </summary>
	/// <param name="buttontype">�{�^���R�[�h</param>
	/// <returns></returns>
	inline bool IsMouseEmpty(MouseButton buttontype) const;
	/// <summary>
	/// �}�E�X�{�^���������ꂽ�u��
	/// </summary>
	/// <param name="buttontype">�{�^���R�[�h</param>
	/// <returns></returns>
	inline bool IsMouseTrigger(MouseButton buttontype) const;
	/// <summary>
	/// �}�E�X�{�^���𗣂����u��
	/// </summary>
	/// <param name="buttontype">�{�^���R�[�h</param>
	/// <returns></returns>
	inline bool IsMouseRelease(MouseButton buttontype) const;
	/// <summary>
	/// �}�E�X�̃X�N���[�����W
	/// </summary>
	/// <returns></returns>
	inline const Vector2& GetMousePosition() const;
	/// <summary>
	/// �}�E�X�̈ړ���
	/// </summary>
	/// <returns></returns>
	inline const Vector2 GetMouseMove() const;
	/// <summary>
	/// �}�E�X�z�C�[��
	/// </summary>
	/// <returns></returns>
	inline float GetWheel() const;

};

#pragma region �C�����C����`

inline bool Input::IsKeyPressed(uint8_t keycode) const { return m_curkeys[keycode] != 0; }
inline bool Input::IsKeyEmpty(uint8_t keycode) const { return m_curkeys[keycode] == 0; }
inline bool Input::IsKeyTrigger(uint8_t keycode) const { return m_preKeys[keycode] == 0 && m_curkeys[keycode] != 0; }
inline bool Input::IsKeyRelease(uint8_t keycode) const { return m_preKeys[keycode] != 0 && m_curkeys[keycode] == 0; }
inline bool Input::IsMousePressed(MouseButton buttontype) const {
	return m_curMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE;
}
inline bool Input::IsMouseEmpty(MouseButton buttontype) const {
	return !(m_curMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE);
}
inline bool Input::IsMouseTrigger(MouseButton buttontype) const {
	return !(m_preMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE) &&
		m_curMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE;
}
inline bool Input::IsMouseRelease(MouseButton buttontype) const {
	return m_preMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE &&
		!(m_curMouseState.rgbButtons[static_cast<int>(buttontype)] & MOOUSE_ON_VALUE);
}
inline const Vector2& Input::GetMousePosition() const { return m_mousePos; }
inline const Vector2 Input::GetMouseMove() const { return { static_cast<float>(m_curMouseState.lX),static_cast<float>(m_curMouseState.lY) }; }
inline float Input::GetWheel() const { return static_cast<float>(m_curMouseState.lZ); }

#pragma endregion

#endif // INPUT_H_
