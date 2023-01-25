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
#include <array>

#include "Vector2.h"
#include "Matrix44.h"

#define MOOUSE_ON_VALUE 0x80

enum MouseButton 
{
	kMouseButtonLeft,
	kMouseButtonRight,
	kMouseButtonMid,
};

// �R���g���[���[�{�^��
enum PadButton {
	kPadButtonUp = 0x0001,			// ��
	kPadButtonDown = 0x0002,			// ��
	kPadButtonLeft = 0x0004,			// ��
	kPadButtonRight = 0x0008,		// �E
	kPadButtonStart = 0x0010,		// ���j���[
	kPadButtonBack = 0x0020,			// �r���[
	kPadButtonLeftThumb = 0x0040,			// L3
	kPadButtonRightThumb = 0x0080,			// R3
	kPadButtonLeftShoulder = 0x0100,		// L1
	kPadButtonRightShoulder = 0x0200,		// R1
	kPadButtonA = 0x1000,			// A
	kPadButtonB = 0x2000,			// B
	kPadButtonX = 0x4000,			// X
	kPadButtonY = 0x8000,			// Y
	kPadLeftTrigger = 0x000F0000,	// L2 (�K���Ȑ��������蓖��)
	kPadRightTrigger = 0x00FF0000,	// R2 (�K���Ȑ��������蓖��)
};

// �X�e�B�b�N�̌���
enum StickDirection {
	kStickDirectionUp,			// LEFT STICK DIRECTION UP
	kStickDirectionDown,		// LEFT STICK DIRECTION DOWN
	kStickDirectionRight,		// LEFT STICK DIRECTION RIGHT
	kStickDirectionLeft,		// LEFT STICK DIRECTION LEFT
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
	static constexpr int kXInputConnectMaxCount = 4;

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
	
	std::array<GamePad, kXInputConnectMaxCount> m_gamePads;


public: // �ÓI�����o�֐�
	static Input* GetInstance();

public: // �����o�֐�
	void Initialize(WinApp* winApp);
	void Update();

#pragma region �L�[�{�[�h�֌W

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
	
#pragma endregion

#pragma region �}�E�X�֌W
	
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
	
#pragma endregion

#pragma region �R���g���[���[�֌W
	
	/// <summary>
	/// �g���K�[�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="deadzone">�f�b�h�]�[���@�F�@0�`255(0 ~ 0xFF)</param>
	inline void SetTriggerDeadZone(int index, int deadzone);
	/// <summary>
	/// �E�X�e�B�b�N�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="deadzone">�f�b�h�]�[���@�F�@0�`32768(0 ~ 0x8000)</param>
	inline void SetRightStickDeadZone(int index, int deadzone);
	/// <summary>
	/// ���X�e�B�b�N�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="deadzone">�f�b�h�]�[���@�F�@0�`32768(0 ~ 0x8000)</param>
	inline void SetLeftStickDeadZone(int index, int deadzone);

	/// <summary>
	/// �g���K�[�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	inline int GetTriggerDeadZone(int index);
	/// <summary>
	/// �E�X�e�B�b�N�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	inline int GetRightStickDeadZone(int index);
	/// <summary>
	/// ���X�e�B�b�N�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	inline int GetLeftStickDeadZone(int index);

	/// <summary>
	/// �{�^���������ꂽ��
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="button">�{�^���ԍ�</param>
	/// <returns></returns>
	bool IsPadButtonTrigger(int index, PadButton button) const;
	/// <summary>
	/// �{�^����������Ă��鎞
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="button">�{�^���ԍ�</param>
	/// <returns></returns>
	bool IsPadButtonPressed(int index, PadButton button) const;
	/// <summary>
	/// �{�^���������ꂽ��
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="button">�{�^���ԍ�</param>
	/// <returns></returns>
	bool IsPadButtonRelease(int index, PadButton button) const;
	/// <summary>
	/// �E�X�e�B�b�N���w��̌����ɓ|���ꂽ��
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="direction">�X�e�B�b�N����</param>
	/// <returns></returns>
	bool IsRightStickDirection(int index, StickDirection direction) const;
	/// <summary>
	/// ���X�e�B�b�N���w��̌����ɓ|���ꂽ��
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="direction">�X�e�B�b�N����</param>
	/// <returns></returns>
	bool IsLeftStickDirection(int index, StickDirection direction) const;
	/// <summary>
	/// �E�g���K�[
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="out">0�`255</param>
	/// <returns>�����@or�@���s</returns>
	int GetRightTrigger(int index) const;
	/// <summary>
	/// ���g���K�[
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="out">0�`255</param>
	/// <returns>�����@or�@���s</returns>
	int GetLeftTrigger(int index) const;
	/// <summary>
	/// �E�X�e�B�b�N
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="outx">X��</param>
	/// <param name="outy">Y��</param>
	void GetRightStick(int index, int* outx, int* outy) const;
	/// <summary>
	/// �E�X�e�B�b�N
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	Vector2 GetRightStick(int index) const;
	/// <summary>
	/// ���X�e�B�b�N
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="outx">X��</param>
	/// <param name="outy">Y��</param>
	void GetLeftStick(int index, int* outx, int* outy) const;
	/// <summary>
	/// ���X�e�B�b�N
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	Vector2 GetLeftStick(int index) const;

#pragma endregion

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

inline void Input::SetTriggerDeadZone(int index, int deadzone)
{
	m_gamePads[index].triggerDeadZone = deadzone;
}

inline void Input::SetRightStickDeadZone(int index, int deadzone)
{
	m_gamePads[index].rightStickDeadZone = deadzone;
}

inline void Input::SetLeftStickDeadZone(int index, int deadzone)
{
	m_gamePads[index].leftStickDeadZone = deadzone;
}

inline int Input::GetTriggerDeadZone(int index)
{
	return m_gamePads[index].triggerDeadZone;
}

inline int Input::GetRightStickDeadZone(int index)
{
	return m_gamePads[index].rightStickDeadZone;
}

inline int Input::GetLeftStickDeadZone(int index)
{
	return m_gamePads[index].leftStickDeadZone;
}

inline bool Input::IsPadButtonTrigger(int index, PadButton button) const
{
	switch (button)
	{
	case kPadLeftTrigger: // ���g���K�[
		return (m_gamePads[index].curState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone) &&
			!(m_gamePads[index].preState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone);

	case kPadRightTrigger: // �E�g���K�[
		return (m_gamePads[index].curState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone) &&
			!(m_gamePads[index].preState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone);

	default: // ���̑��{�^��
		return (m_gamePads[index].curState.Gamepad.wButtons & button) &&
			!(m_gamePads[index].preState.Gamepad.wButtons & button);

	}
	return false;
}

inline bool Input::IsPadButtonPressed(int index, PadButton button) const
{
	switch (button)
	{
	case kPadLeftTrigger: // ���g���K�[
		return (m_gamePads[index].curState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone);

	case kPadRightTrigger: // �E�g���K�[
		return (m_gamePads[index].curState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone);

	default: // ���̑��{�^��
		return (m_gamePads[index].curState.Gamepad.wButtons & button);

	}
	return false;
}

inline bool Input::IsPadButtonRelease(int index, PadButton button) const
{
	switch (button)
	{
	case kPadLeftTrigger: // ���g���K�[
		return !(m_gamePads[index].curState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone) &&
			(m_gamePads[index].preState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone);

	case kPadRightTrigger: // �E�g���K�[
		return !(m_gamePads[index].curState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone) &&
			(m_gamePads[index].preState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone);

	default: // ���̑��{�^��
		return !(m_gamePads[index].curState.Gamepad.wButtons & button) &&
			(m_gamePads[index].preState.Gamepad.wButtons & button);

	}
	return false;
}

inline bool Input::IsRightStickDirection(int index, StickDirection direction) const
{
	switch (direction)
	{
	case kStickDirectionUp:
		return m_gamePads[index].curState.Gamepad.sThumbRY >= m_gamePads[index].rightStickDeadZone;

	case kStickDirectionDown:
		return m_gamePads[index].curState.Gamepad.sThumbRY <= -m_gamePads[index].rightStickDeadZone;

	case kStickDirectionRight:
		return m_gamePads[index].curState.Gamepad.sThumbRX >= m_gamePads[index].rightStickDeadZone;

	case kStickDirectionLeft:
		return m_gamePads[index].curState.Gamepad.sThumbRX <= -m_gamePads[index].rightStickDeadZone;
	}
	return false;
}

inline bool Input::IsLeftStickDirection(int index, StickDirection direction) const
{
	switch (direction)
	{
	case kStickDirectionUp:
		return m_gamePads[index].curState.Gamepad.sThumbLY >= m_gamePads[index].leftStickDeadZone;

	case kStickDirectionDown:
		return m_gamePads[index].curState.Gamepad.sThumbLY <= -m_gamePads[index].leftStickDeadZone;

	case kStickDirectionRight:
		return m_gamePads[index].curState.Gamepad.sThumbLX >= m_gamePads[index].leftStickDeadZone;

	case kStickDirectionLeft:
		return m_gamePads[index].curState.Gamepad.sThumbLX <= -m_gamePads[index].leftStickDeadZone;
	}
	return false;
}

inline int Input::GetRightTrigger(int index) const
{
	if (m_gamePads[index].curState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone) {
		return m_gamePads[index].curState.Gamepad.bRightTrigger;
	}
	return 0;
}

inline int Input::GetLeftTrigger(int index) const
{
	if (m_gamePads[index].curState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone) {
		return m_gamePads[index].curState.Gamepad.bLeftTrigger;
	}
	return 0;
}

inline void Input::GetRightStick(int index, int* outx, int* outy) const
{
	Vector2 tmp = Vector2(static_cast<float>(m_gamePads[index].curState.Gamepad.sThumbRX), static_cast<float>(m_gamePads[index].curState.Gamepad.sThumbRY));
	if (tmp.Length() > m_gamePads[index].rightStickDeadZone) {
		*outx = m_gamePads[index].curState.Gamepad.sThumbRX;
		*outy = m_gamePads[index].curState.Gamepad.sThumbRY;
		return;
	}
	*outx = 0;
	*outy = 0;
	return;
}

inline Vector2 Input::GetRightStick(int index) const
{
	Vector2 tmp = Vector2(static_cast<float>(m_gamePads[index].curState.Gamepad.sThumbRX), static_cast<float>(m_gamePads[index].curState.Gamepad.sThumbRY));
	if (tmp.Length() > m_gamePads[index].rightStickDeadZone) {
		return tmp;
	}
	return Vector2::Zero;
}

inline void Input::GetLeftStick(int index, int* outx, int* outy) const
{
	Vector2 tmp = Vector2(static_cast<float>(m_gamePads[index].curState.Gamepad.sThumbLX), static_cast<float>(m_gamePads[index].curState.Gamepad.sThumbLY));
	if (tmp.Length() > m_gamePads[index].leftStickDeadZone) {
		*outx = m_gamePads[index].curState.Gamepad.sThumbLX;
		*outy = m_gamePads[index].curState.Gamepad.sThumbLY;
		return;
	}
	*outx = 0;
	*outy = 0;
	return;
}

inline Vector2 Input::GetLeftStick(int index) const
{
	Vector2 tmp = Vector2(static_cast<float>(m_gamePads[index].curState.Gamepad.sThumbLX), static_cast<float>(m_gamePads[index].curState.Gamepad.sThumbLY));
	if (tmp.Length() > m_gamePads[index].leftStickDeadZone) {
		return tmp;
	}
	return Vector2::Zero;
}

#pragma endregion

#endif // INPUT_H_
