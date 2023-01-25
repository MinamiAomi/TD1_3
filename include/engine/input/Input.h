#pragma once
#ifndef INPUT_H_
#define INPUT_H_

#include "WinApp.h"
#include <wrl.h>
#include <stdint.h>
#include <Xinput.h>
#define DIRECTINPUT_VERSION 0x0800 // DirectIputのバージョン指定
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

// コントローラーボタン
enum PadButton {
	kPadButtonUp = 0x0001,			// 上
	kPadButtonDown = 0x0002,			// 下
	kPadButtonLeft = 0x0004,			// 左
	kPadButtonRight = 0x0008,		// 右
	kPadButtonStart = 0x0010,		// メニュー
	kPadButtonBack = 0x0020,			// ビュー
	kPadButtonLeftThumb = 0x0040,			// L3
	kPadButtonRightThumb = 0x0080,			// R3
	kPadButtonLeftShoulder = 0x0100,		// L1
	kPadButtonRightShoulder = 0x0200,		// R1
	kPadButtonA = 0x1000,			// A
	kPadButtonB = 0x2000,			// B
	kPadButtonX = 0x4000,			// X
	kPadButtonY = 0x8000,			// Y
	kPadLeftTrigger = 0x000F0000,	// L2 (適当な数字を割り当て)
	kPadRightTrigger = 0x00FF0000,	// R2 (適当な数字を割り当て)
};

// スティックの向き
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
		BYTE triggerDeadZone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD; // トリガーのデッドゾーン
		SHORT leftStickDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; // 左スティックのデッドゾーン
		SHORT rightStickDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;	// 右スティックのデッドゾーン
	};

private:
	static constexpr int kKeyDataNum = 256;
	static constexpr int kXInputConnectMaxCount = 4;

private:
	WinApp* m_winApp = nullptr;

	ComPtr<IDirectInput8> m_directInput;
	ComPtr<IDirectInputDevice8> m_keyboard;
	ComPtr<IDirectInputDevice8> m_mouse;

	BYTE m_curkeys[kKeyDataNum] = {}; // 現在のキーの入力状態
	BYTE m_preKeys[kKeyDataNum] = {}; // 前回のキーの入力状態

	DIMOUSESTATE2 m_curMouseState = {}; // 現在のマウスの入力状態
	DIMOUSESTATE2 m_preMouseState = {}; // 前回のマウスの入力状態
	Vector2 m_mousePos;					// マウスのスクリーン座標
	
	std::array<GamePad, kXInputConnectMaxCount> m_gamePads;


public: // 静的メンバ関数
	static Input* GetInstance();

public: // メンバ関数
	void Initialize(WinApp* winApp);
	void Update();

#pragma region キーボード関係

	/// <summary>
	/// 押されている
	/// </summary>
	/// <param name="keycode">キーコード</param>
	/// <returns></returns>
	inline bool IsKeyPressed(uint8_t keycode) const;
	/// <summary>
	/// 押されていない
	/// </summary>
	/// <param name="keycode">キーコード</param>
	/// <returns></returns>
	inline bool IsKeyEmpty(uint8_t keycode) const;
	/// <summary>
	/// 押した瞬間
	/// </summary>
	/// <param name="keycode">キーコード</param>
	/// <returns></returns>
	inline bool IsKeyTrigger(uint8_t keycode) const;
	/// <summary>
	/// 離した瞬間
	/// </summary>
	/// <param name="keycode">キーコード</param>
	/// <returns></returns>
	inline bool IsKeyRelease(uint8_t keycode) const;
	
#pragma endregion

#pragma region マウス関係
	
	/// <summary>
	/// マウスボタンが押されている
	/// </summary>
	/// <param name="buttontype">ボタンコード</param>
	/// <returns></returns>
	inline bool IsMousePressed(MouseButton buttontype) const;
	/// <summary>
	/// マウスボタンが押されていない
	/// </summary>
	/// <param name="buttontype">ボタンコード</param>
	/// <returns></returns>
	inline bool IsMouseEmpty(MouseButton buttontype) const;
	/// <summary>
	/// マウスボタンが押された瞬間
	/// </summary>
	/// <param name="buttontype">ボタンコード</param>
	/// <returns></returns>
	inline bool IsMouseTrigger(MouseButton buttontype) const;
	/// <summary>
	/// マウスボタンを離した瞬間
	/// </summary>
	/// <param name="buttontype">ボタンコード</param>
	/// <returns></returns>
	inline bool IsMouseRelease(MouseButton buttontype) const;
	/// <summary>
	/// マウスのスクリーン座標
	/// </summary>
	/// <returns></returns>
	inline const Vector2& GetMousePosition() const;
	/// <summary>
	/// マウスの移動量
	/// </summary>
	/// <returns></returns>
	inline const Vector2 GetMouseMove() const;
	/// <summary>
	/// マウスホイール
	/// </summary>
	/// <returns></returns>
	inline float GetWheel() const;
	
#pragma endregion

#pragma region コントローラー関係
	
	/// <summary>
	/// トリガーのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～255(0 ~ 0xFF)</param>
	inline void SetTriggerDeadZone(int index, int deadzone);
	/// <summary>
	/// 右スティックのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～32768(0 ~ 0x8000)</param>
	inline void SetRightStickDeadZone(int index, int deadzone);
	/// <summary>
	/// 左スティックのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～32768(0 ~ 0x8000)</param>
	inline void SetLeftStickDeadZone(int index, int deadzone);

	/// <summary>
	/// トリガーのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	inline int GetTriggerDeadZone(int index);
	/// <summary>
	/// 右スティックのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	inline int GetRightStickDeadZone(int index);
	/// <summary>
	/// 左スティックのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	inline int GetLeftStickDeadZone(int index);

	/// <summary>
	/// ボタンが押された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	bool IsPadButtonTrigger(int index, PadButton button) const;
	/// <summary>
	/// ボタンが押されている時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	bool IsPadButtonPressed(int index, PadButton button) const;
	/// <summary>
	/// ボタンが離された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	bool IsPadButtonRelease(int index, PadButton button) const;
	/// <summary>
	/// 右スティックが指定の向きに倒された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="direction">スティック向き</param>
	/// <returns></returns>
	bool IsRightStickDirection(int index, StickDirection direction) const;
	/// <summary>
	/// 左スティックが指定の向きに倒された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="direction">スティック向き</param>
	/// <returns></returns>
	bool IsLeftStickDirection(int index, StickDirection direction) const;
	/// <summary>
	/// 右トリガー
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="out">0～255</param>
	/// <returns>成功　or　失敗</returns>
	int GetRightTrigger(int index) const;
	/// <summary>
	/// 左トリガー
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="out">0～255</param>
	/// <returns>成功　or　失敗</returns>
	int GetLeftTrigger(int index) const;
	/// <summary>
	/// 右スティック
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="outx">X軸</param>
	/// <param name="outy">Y軸</param>
	void GetRightStick(int index, int* outx, int* outy) const;
	/// <summary>
	/// 右スティック
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	Vector2 GetRightStick(int index) const;
	/// <summary>
	/// 左スティック
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="outx">X軸</param>
	/// <param name="outy">Y軸</param>
	void GetLeftStick(int index, int* outx, int* outy) const;
	/// <summary>
	/// 左スティック
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	Vector2 GetLeftStick(int index) const;

#pragma endregion

};

#pragma region インライン定義

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
	case kPadLeftTrigger: // 左トリガー
		return (m_gamePads[index].curState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone) &&
			!(m_gamePads[index].preState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone);

	case kPadRightTrigger: // 右トリガー
		return (m_gamePads[index].curState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone) &&
			!(m_gamePads[index].preState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone);

	default: // その他ボタン
		return (m_gamePads[index].curState.Gamepad.wButtons & button) &&
			!(m_gamePads[index].preState.Gamepad.wButtons & button);

	}
	return false;
}

inline bool Input::IsPadButtonPressed(int index, PadButton button) const
{
	switch (button)
	{
	case kPadLeftTrigger: // 左トリガー
		return (m_gamePads[index].curState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone);

	case kPadRightTrigger: // 右トリガー
		return (m_gamePads[index].curState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone);

	default: // その他ボタン
		return (m_gamePads[index].curState.Gamepad.wButtons & button);

	}
	return false;
}

inline bool Input::IsPadButtonRelease(int index, PadButton button) const
{
	switch (button)
	{
	case kPadLeftTrigger: // 左トリガー
		return !(m_gamePads[index].curState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone) &&
			(m_gamePads[index].preState.Gamepad.bLeftTrigger > m_gamePads[index].triggerDeadZone);

	case kPadRightTrigger: // 右トリガー
		return !(m_gamePads[index].curState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone) &&
			(m_gamePads[index].preState.Gamepad.bRightTrigger > m_gamePads[index].triggerDeadZone);

	default: // その他ボタン
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
