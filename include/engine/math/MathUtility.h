#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix33.h"
#include "Matrix44.h"
#include "Quaternion.h"

namespace Math
{

	constexpr float Pi = 3.14159265359f;
	constexpr float TwoPi = 2.0f * Pi;
	constexpr float PiDiv2 = Pi / 2.0f;


	/// <summary>
	/// �ʓx�@�ϊ�
	/// </summary>
	/// <param name="degrees">�x���@</param>
	/// <returns>�ʓx�@</returns>
	constexpr inline float ToRadians(float degrees) {
		return degrees * Pi / 180.0f;
	}
	/// <summary>
	/// �x���@�ϊ�
	/// </summary>
	/// <param name="radians">�ʓx�@</param>
	/// <returns>�x���@</returns>
	constexpr inline float ToDegrees(float radians) {
		return radians * 180.0f / Pi;
	}
	/// <summary>
	/// �قڃ[��
	/// </summary>
	/// <param name="value">�l</param>
	/// <param name="epsilon">�덷</param>
	/// <returns>true : false</returns>
	inline bool NearZero(float value, float epsilon = 0.001f) {
		return fabs(value) <= epsilon;
	}
	/// <summary>
	/// �����𔻒f
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="v">�l</param>
	/// <returns> 0��0 </returns>
	template <typename TYPE>
	int GetSign(TYPE v) {
		return (v > 0) - (v < 0);
	}
	/// <summary>
	/// �傫���ق������߂�
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="v1">�l�P</param>
	/// <param name="v2">�l�Q</param>
	/// <returns>�l�P�@or�@�l�Q</returns>
	template <typename TYPE>
	TYPE Max(const TYPE& v1, const TYPE& v2) {
		return v1 < v2 ? v2 : v1;
	}
	/// <summary>
	/// �������ق������߂�
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="v1">�l�P</param>
	/// <param name="v2">�l�Q</param>
	/// <returns>�l�P�@or�@�l�Q</returns>
	template <typename TYPE>
	TYPE Min(const TYPE& v1, const TYPE& v2) {
		return v1 < v2 ? v1 : v2;
	}
	// �l�����ւ���
	template <typename TYPE>
	void Swap(TYPE& v1, TYPE& v2) {
		TYPE tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
	/// <summary>
	/// �l�����߂�
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="value">�l</param>
	/// <param name="lower">����</param>
	/// <param name="upper">���</param>
	/// <returns></returns>
	template <typename TYPE>
	TYPE Clamp(const TYPE& value, const TYPE& lower, const TYPE& upper) {
		return Min(upper, Max(lower, value));
	}
	/// <summary>
	/// �l�����[�v������
	/// </summary>
	/// <param name="value">�l</param>
	/// <param name="range">�͈�</param>
	/// <param name="min">�ŏ�</param>
	/// <returns></returns>
	inline float Loop(float value, float range, float min = 0.0f) {
		float a = fmodf(value, range);
		if (a == 0) return a;
		return a > 0 ? a + min : a + min + range;
	}
	/// <summary>
	/// ��Βl
	/// </summary>
	/// <param name="value">�l</param>
	/// <returns></returns>
	inline float Abs(float value) {
		return fabsf(value);
	}
	/// <summary>
	///	�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Sin(float angle) {
		return sinf(angle);
	}
	/// <summary>
	/// �R�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Cos(float angle) {
		return cosf(angle);
	}
	/// <summary>
	/// �^���W�F���g
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Tan(float angle) {
		return tanf(angle);
	}
	/// <summary>
	/// �A�[�N�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Asin(float angle) {
		return asinf(angle);
	}
	/// <summary>
	/// �A�[�N�R�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Acos(float angle) {
		return acosf(angle);
	}
	/// <summary>
	/// �A�[�N�^���W�F���g
	/// </summary>
	/// <param name="y">y����</param>
	/// <param name="x">x����</param>
	/// <returns>���W�A��</returns>
	inline float Atan2(float y, float x) {
		return atan2f(y, x);
	}
	/// <summary>
	/// ���`���
	/// </summary>
	/// <param name="t">�ω���</param>
	/// <param name="start">�X�^�[�g</param>
	/// <param name="end">�G���h</param>
	/// <returns></returns>
	inline float Lerp(float t, float start, float end) {
		return start + t * (end - start);
	}
	/// <summary>
	/// ���ݔ͈͂���ʂ͈̔͂ɕϊ�
	/// </summary>
	/// <param name="value">�l</param>
	/// <param name="start1">���ݔ͈͂̍ŏ�</param>
	/// <param name="end1">���ݔ͈͂̍ő�</param>
	/// <param name="start2">�ϊ��͈͂̍ŏ�</param>
	/// <param name="end2">�ϊ��͈͂̍ő�</param>
	/// <returns></returns>
	inline float Map(float value, float start1, float end1, float start2, float end2) {
		return start2 + (end1 - start2) * ((value - start1) / (end2 - start1));
	}
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="value">�l</param>
	/// <returns></returns>
	inline float Sqrt(float value) {
		return sqrtf(value);
	}
	/// <summary>
	/// float��]���Z
	/// </summary>
	/// <param name="number">�����鐔</param>
	/// <param name="denom">���鐔</param>
	/// <returns>�]��</returns>
	inline float Fmod(float number, float denom) {
		return fmodf(number, denom);
	}
	/// <summary>
	/// �p��
	/// </summary>
	/// <param name="base">��</param>
	/// <param name="exponent">�w��</param>
	/// <returns></returns>
	inline float Pow(float base, float exponent) {
		return powf(base, exponent);
	}

}

namespace Color {

	static const unsigned int kByteMax = 0xFF;

	static const Vector4 Black = { 0.0f,0.0f,0.0f,1.0f };
	static const Vector4 White = { 1.0f,1.0f,1.0f,1.0f };
	static const Vector4 Red = { 1.0f,0.0f,0.0f,1.0f };
	static const Vector4 Green = { 0.0f,1.0f,0.0f,1.0f };
	static const Vector4 Blue = { 0.0f,0.0f,1.0f,1.0f };

	
	unsigned int Create(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	/// <summary>
	/// �F�x�N�g���ɕϊ�
	/// </summary>
	/// <param name="color">�J���[�R�[�h</param>
	/// <returns></returns>
	Vector4 ToVector4(unsigned int color);
	
	/// <summary>
	/// HSV����RGB�ɕϊ�
	/// </summary>
	/// <param name="h">�F�� : 0 ~ 360</param>
	/// <param name="s">�ʓx : 0 ~ 1</param>
	/// <param name="v">���x : 0 ~ 1</param>
	/// <param name="a">�����x 0 ~ 255 �����Ȃ������^</param>
	/// <returns></returns>
	unsigned int HsvaToRgba(float h, float s, float v, unsigned int a);
}