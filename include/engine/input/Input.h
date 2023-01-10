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
		BYTE triggerDeadZone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD; // トリガーのデッドゾーン
		SHORT leftStickDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; // 左スティックのデッドゾーン
		SHORT rightStickDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;	// 右スティックのデッドゾーン
	};

private:
	static constexpr int kKeyDataNum = 256;

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
	
	std::vector<GamePad> m_gamePads;


public: // 静的メンバ関数
	static Input* GetInstance();

public: // メンバ関数
	void Initialize(WinApp* winApp);
	void Update();

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

#pragma endregion

#endif // INPUT_H_
