#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include <math.h>

#define MATRIX_OPTIMIZE true

class Matrix44
{

public:
	static const Matrix44 Identity;

private:
	float m[4][4];

public:
	Matrix44(
		float _00 = 1.0f, float _01 = 0.0f, float _02 = 0.0f, float _03 = 0.0f,
		float _10 = 0.0f, float _11 = 1.0f, float _12 = 0.0f, float _13 = 0.0f,
		float _20 = 0.0f, float _21 = 0.0f, float _22 = 1.0f, float _23 = 0.0f,
		float _30 = 0.0f, float _31 = 0.0f, float _32 = 0.0f, float _33 = 1.0f) {
		m[0][0] = _00, m[0][1] = _01, m[0][2] = _02, m[0][3] = _03;
		m[1][0] = _10, m[1][1] = _11, m[1][2] = _12, m[1][3] = _13;
		m[2][0] = _20, m[2][1] = _21, m[2][2] = _22, m[2][3] = _23;
		m[3][0] = _30, m[3][1] = _31, m[3][2] = _32, m[3][3] = _33;
	}

	friend inline Matrix44 operator*(float s, const Matrix44& m) {
		return {
			s * m.m[0][0],s * m.m[0][1],s * m.m[0][2],s * m.m[0][3],
			s * m.m[1][0],s * m.m[1][1],s * m.m[1][2],s * m.m[1][3],
			s * m.m[2][0],s * m.m[2][1],s * m.m[2][2],s * m.m[2][3],
			s * m.m[3][0],s * m.m[3][1],s * m.m[3][2],s * m.m[3][3] };
	}


	friend inline Matrix44 operator*(const Matrix44& m, float s) {
		return {
			m.m[0][0] * s, m.m[0][1] * s, m.m[0][2] * s, m.m[0][3] * s,
			m.m[1][0] * s, m.m[1][1] * s, m.m[1][2] * s, m.m[1][3] * s,
			m.m[2][0] * s, m.m[2][1] * s, m.m[2][2] * s, m.m[2][3] * s,
			m.m[3][0] * s, m.m[3][1] * s, m.m[3][2] * s, m.m[3][3] * s };
	}

	inline const float* operator[](size_t i) const {
		return m[i];
	}
	inline float* operator[](size_t i) {
		return m[i];
	}


	inline float Determinant() const {
		float result = 0.0f;

		result += m[0][0] * m[1][1] * m[2][2] * m[3][3]; // +11,22,33,44
		result += m[0][0] * m[1][2] * m[2][3] * m[3][1]; // +11,23,34,42
		result += m[0][0] * m[1][3] * m[2][1] * m[3][2]; // +11,24,32,43

		result -= m[0][0] * m[1][3] * m[2][2] * m[3][1]; // -11,24,33,42
		result -= m[0][0] * m[1][2] * m[2][1] * m[3][3]; // -11,23,32,44
		result -= m[0][0] * m[1][1] * m[2][3] * m[3][2]; // -11,22,34,43

		result -= m[0][1] * m[1][0] * m[2][2] * m[3][3]; // -12,21,33,44
		result -= m[0][2] * m[1][0] * m[2][3] * m[3][1]; // -13,21,34,42
		result -= m[0][3] * m[1][0] * m[2][1] * m[3][2]; // -14,21,32,43

		result += m[0][3] * m[1][0] * m[2][2] * m[3][1]; // +14,21,33,42
		result += m[0][2] * m[1][0] * m[2][1] * m[3][3]; // +13,21,32,44
		result += m[0][1] * m[1][0] * m[2][3] * m[3][2]; // +12,21,34,43

		result += m[0][1] * m[1][2] * m[2][0] * m[3][3]; // +12,23,31,44
		result += m[0][2] * m[1][3] * m[2][0] * m[3][1]; // +13,24,31,42
		result += m[0][3] * m[1][1] * m[2][0] * m[3][2]; // +14,22,31,43

		result -= m[0][3] * m[1][2] * m[2][0] * m[3][1]; // -14,23,31,42
		result -= m[0][2] * m[1][1] * m[2][0] * m[3][3]; // -13,22,31,44
		result -= m[0][1] * m[1][3] * m[2][0] * m[3][2]; // -12,24,31,43

		result -= m[0][1] * m[1][2] * m[2][3] * m[3][0]; // -12,23,34,41
		result -= m[0][2] * m[1][3] * m[2][1] * m[3][0]; // -13,24,32,41
		result -= m[0][3] * m[1][1] * m[2][2] * m[3][0]; // -14,22,33,41

		result += m[0][3] * m[1][2] * m[2][1] * m[3][0]; // +14,23,32,41
		result += m[0][2] * m[1][1] * m[2][3] * m[3][0]; // +13,22,34,41
		result += m[0][1] * m[1][3] * m[2][2] * m[3][0]; // +12,24,33,41

		return result;
	}


	Matrix44 Adjugate() const {
		Matrix44 result;


		// 1行目
		result.m[0][0] = 0.0f;							// 11
		result.m[0][0] += m[1][1] * m[2][2] * m[3][3];	// +22,33,44
		result.m[0][0] += m[1][2] * m[2][3] * m[3][1];	// +23,34,42
		result.m[0][0] += m[1][3] * m[2][1] * m[3][2];	// +24,32,43
		result.m[0][0] -= m[1][3] * m[2][2] * m[3][1];	// -24,33,42
		result.m[0][0] -= m[1][2] * m[2][1] * m[3][3];	// -23,32,44
		result.m[0][0] -= m[1][1] * m[2][3] * m[3][2];	// -22,34,43

		result.m[0][1] = 0.0f;							// 12
		result.m[0][1] -= m[0][1] * m[2][2] * m[3][3];	// -12,33,44
		result.m[0][1] -= m[0][2] * m[2][3] * m[3][1];	// -13,34,42
		result.m[0][1] -= m[0][3] * m[2][1] * m[3][2];	// -14,32,43
		result.m[0][1] += m[0][3] * m[2][2] * m[3][1];	// +14,33,42
		result.m[0][1] += m[0][2] * m[2][1] * m[3][3];	// +13,32,44
		result.m[0][1] += m[0][1] * m[2][3] * m[3][2];	// +12,34,43

		result.m[0][2] = 0.0f;							// 13
		result.m[0][2] += m[0][1] * m[1][2] * m[3][3];	// +12,23,44
		result.m[0][2] += m[0][2] * m[1][3] * m[3][1];	// +13,24,42
		result.m[0][2] += m[0][3] * m[1][1] * m[3][2];	// +14,22,43
		result.m[0][2] -= m[0][3] * m[1][2] * m[3][1];	// -14,23,42
		result.m[0][2] -= m[0][2] * m[1][1] * m[3][3];	// -13,22,44
		result.m[0][2] -= m[0][1] * m[1][3] * m[3][2];	// -12,24,43

		result.m[0][3] = 0.0f;							// 14
		result.m[0][3] -= m[0][1] * m[1][2] * m[2][3];	// -12,23,34
		result.m[0][3] -= m[0][2] * m[1][3] * m[2][1];	// -13,24,32
		result.m[0][3] -= m[0][3] * m[1][1] * m[2][2];	// -14,22,33
		result.m[0][3] += m[0][3] * m[1][2] * m[2][1];	// +14,23,32
		result.m[0][3] += m[0][2] * m[1][1] * m[2][3];	// +13,22,34
		result.m[0][3] += m[0][1] * m[1][3] * m[2][2];	// +12,24,33


		// 2行目
		result.m[1][0] = 0.0f;							// 21
		result.m[1][0] -= m[1][0] * m[2][2] * m[3][3];	// -21,33,44
		result.m[1][0] -= m[1][2] * m[2][3] * m[3][0];	// -23,34,41
		result.m[1][0] -= m[1][3] * m[2][0] * m[3][2];	// -24,31,43
		result.m[1][0] += m[1][3] * m[2][2] * m[3][0];	// +24,33,41
		result.m[1][0] += m[1][2] * m[2][0] * m[3][3];	// +23,31,44
		result.m[1][0] += m[1][0] * m[2][3] * m[3][2];	// +21,34,43

		result.m[1][1] = 0.0f;							// 22
		result.m[1][1] += m[0][0] * m[2][2] * m[3][3];	// +11,33,44
		result.m[1][1] += m[0][2] * m[2][3] * m[3][0];	// +13,34,41
		result.m[1][1] += m[0][3] * m[2][0] * m[3][2];	// +14,31,43
		result.m[1][1] -= m[0][3] * m[2][2] * m[3][0];	// -14,33,41
		result.m[1][1] -= m[0][2] * m[2][0] * m[3][3];	// -13,31,44
		result.m[1][1] -= m[0][0] * m[2][3] * m[3][2];	// -11,34,43

		result.m[1][2] = 0.0f;							// 23
		result.m[1][2] -= m[0][0] * m[1][2] * m[3][3];	// -11,23,44
		result.m[1][2] -= m[0][2] * m[1][3] * m[3][0];	// -13,24,41
		result.m[1][2] -= m[0][3] * m[1][0] * m[3][2];	// -14,21,43
		result.m[1][2] += m[0][3] * m[1][2] * m[3][0];	// +14,23,41
		result.m[1][2] += m[0][2] * m[1][0] * m[3][3];	// +13,21,44
		result.m[1][2] += m[0][0] * m[1][3] * m[3][2];	// +11,24,43

		result.m[1][3] = 0.0f;							// 24
		result.m[1][3] += m[0][0] * m[1][2] * m[2][3];	// +11,23,34
		result.m[1][3] += m[0][2] * m[1][3] * m[2][0];	// +13,24,31
		result.m[1][3] += m[0][3] * m[1][0] * m[2][2];	// +14,21,33
		result.m[1][3] -= m[0][3] * m[1][2] * m[2][0];	// -14,23,31
		result.m[1][3] -= m[0][2] * m[1][0] * m[2][3];	// -13,21,34
		result.m[1][3] -= m[0][0] * m[1][3] * m[2][2];	// -11,24,33


		// 3行目
		result.m[2][0] = 0.0f;							// 31
		result.m[2][0] += m[1][0] * m[2][1] * m[3][3];	// +21,32,44
		result.m[2][0] += m[1][1] * m[2][3] * m[3][0];	// +22,34,41
		result.m[2][0] += m[1][3] * m[2][0] * m[3][1];	// +24,31,42
		result.m[2][0] -= m[1][3] * m[2][1] * m[3][0];	// -24,32,41
		result.m[2][0] -= m[1][1] * m[2][0] * m[3][3];	// -22,31,44
		result.m[2][0] -= m[1][0] * m[2][3] * m[3][1];	// -21,34,42

		result.m[2][1] = 0.0f;							// 32
		result.m[2][1] -= m[0][0] * m[2][1] * m[3][3];	// -11,32,44
		result.m[2][1] -= m[0][1] * m[2][3] * m[3][0];	// -12,34,41
		result.m[2][1] -= m[0][3] * m[2][0] * m[3][1];	// -14,31,42
		result.m[2][1] += m[0][3] * m[2][1] * m[3][0];	// +14,32,41
		result.m[2][1] += m[0][1] * m[2][0] * m[3][3];	// +12,31,44
		result.m[2][1] += m[0][0] * m[2][3] * m[3][1];	// +11,34,42

		result.m[2][2] = 0.0f;							// 33
		result.m[2][2] += m[0][0] * m[1][1] * m[3][3];	// +11,22,44
		result.m[2][2] += m[0][1] * m[1][3] * m[3][0];	// +12,24,41
		result.m[2][2] += m[0][3] * m[1][0] * m[3][1];	// +14,21,42
		result.m[2][2] -= m[0][3] * m[1][1] * m[3][0];	// -14,22,41
		result.m[2][2] -= m[0][1] * m[1][0] * m[3][3];	// -12,21,44
		result.m[2][2] -= m[0][0] * m[1][3] * m[3][1];	// -11,24,42

		result.m[2][3] = 0.0f;							// 34
		result.m[2][3] -= m[0][0] * m[1][1] * m[2][3];	// -11,22,34
		result.m[2][3] -= m[0][1] * m[1][3] * m[2][0];	// -12,24,31
		result.m[2][3] -= m[0][3] * m[1][0] * m[2][1];	// -14,21,32
		result.m[2][3] += m[0][3] * m[1][1] * m[2][0];	// +14,22,31
		result.m[2][3] += m[0][1] * m[1][0] * m[2][3];	// +12,21,34
		result.m[2][3] += m[0][0] * m[1][3] * m[2][1];	// +11,24,32


		// 4行目
		result.m[3][0] = 0.0f;							// 41
		result.m[3][0] -= m[1][0] * m[2][1] * m[3][2];	// -21,32,43
		result.m[3][0] -= m[1][1] * m[2][2] * m[3][0];	// -22,33,41
		result.m[3][0] -= m[1][2] * m[2][0] * m[3][1];	// -23,31,42
		result.m[3][0] += m[1][2] * m[2][1] * m[3][0];	// +23,32,41
		result.m[3][0] += m[1][1] * m[2][0] * m[3][2];	// +22,31,43
		result.m[3][0] += m[1][0] * m[2][2] * m[3][1];	// +21,33,42

		result.m[3][1] = 0.0f;							// 42
		result.m[3][1] += m[0][0] * m[2][1] * m[3][2];	// +11,32,43
		result.m[3][1] += m[0][1] * m[2][2] * m[3][0];	// +12,33,41
		result.m[3][1] += m[0][2] * m[2][0] * m[3][1];	// +13,31,42
		result.m[3][1] -= m[0][2] * m[2][1] * m[3][0];	// -13,32,41
		result.m[3][1] -= m[0][1] * m[2][0] * m[3][2];	// -12,31,43
		result.m[3][1] -= m[0][0] * m[2][2] * m[3][1];	// -11,33,42

		result.m[3][2] = 0.0f;							// 43
		result.m[3][2] -= m[0][0] * m[1][1] * m[3][2];	// -11,22,43
		result.m[3][2] -= m[0][1] * m[1][2] * m[3][0];	// -12,23,41
		result.m[3][2] -= m[0][2] * m[1][0] * m[3][1];	// -13,21,42
		result.m[3][2] += m[0][2] * m[1][1] * m[3][0];	// +13,22,41
		result.m[3][2] += m[0][1] * m[1][0] * m[3][2];	// +12,21,43
		result.m[3][2] += m[0][0] * m[1][2] * m[3][1];	// +11,23,42

		result.m[3][3] = 0.0f;							// 44
		result.m[3][3] += m[0][0] * m[1][1] * m[2][2];	// +11,22,33
		result.m[3][3] += m[0][1] * m[1][2] * m[2][0];	// +12,23,31
		result.m[3][3] += m[0][2] * m[1][0] * m[2][1];	// +13,21,32
		result.m[3][3] -= m[0][2] * m[1][1] * m[2][0];	// -13,22,31
		result.m[3][3] -= m[0][1] * m[1][0] * m[2][2];	// -12,21,33
		result.m[3][3] -= m[0][0] * m[1][2] * m[2][1];	// -11,23,32


		return result;
	}

	inline Matrix44 Transpose() const {
		return {
			m[0][0],m[1][0],m[2][0],m[3][0],
			m[0][1],m[1][1],m[2][1],m[3][1],
			m[0][2],m[1][2],m[2][2],m[3][2],
			m[0][3],m[1][3],m[2][3],m[3][3] };
	}

	inline Matrix44 Inverse() const {
		float det = Determinant();
		assert(det != 0.0f); // 0の場合逆行列がない
		return 1.0f / det * Adjugate();
	}

	Vector3 GetPosition() const {
		return { m[3][0], m[3][1], m[3][2] };
	}

	friend inline Matrix44 operator*(const Matrix44& a, const Matrix44& b) {
		return {
			a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0] + a.m[0][3] * b.m[3][0],
			a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1] + a.m[0][3] * b.m[3][1],
			a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2] + a.m[0][3] * b.m[3][2],
			a.m[0][0] * b.m[0][3] + a.m[0][1] * b.m[1][3] + a.m[0][2] * b.m[2][3] + a.m[0][3] * b.m[3][3],

			a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0] + a.m[1][3] * b.m[3][0],
			a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1] + a.m[1][3] * b.m[3][1],
			a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2] + a.m[1][3] * b.m[3][2],
			a.m[1][0] * b.m[0][3] + a.m[1][1] * b.m[1][3] + a.m[1][2] * b.m[2][3] + a.m[1][3] * b.m[3][3],

			a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0] + a.m[2][3] * b.m[3][0],
			a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1] + a.m[2][3] * b.m[3][1],
			a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2] + a.m[2][3] * b.m[3][2],
			a.m[2][0] * b.m[0][3] + a.m[2][1] * b.m[1][3] + a.m[2][2] * b.m[2][3] + a.m[2][3] * b.m[3][3],

			a.m[3][0] * b.m[0][0] + a.m[3][1] * b.m[1][0] + a.m[3][2] * b.m[2][0] + a.m[3][3] * b.m[3][0],
			a.m[3][0] * b.m[0][1] + a.m[3][1] * b.m[1][1] + a.m[3][2] * b.m[2][1] + a.m[3][3] * b.m[3][1],
			a.m[3][0] * b.m[0][2] + a.m[3][1] * b.m[1][2] + a.m[3][2] * b.m[2][2] + a.m[3][3] * b.m[3][2],
			a.m[3][0] * b.m[0][3] + a.m[3][1] * b.m[1][3] + a.m[3][2] * b.m[2][3] + a.m[3][3] * b.m[3][3] };
	}

	inline Matrix44& operator*=(const Matrix44& mat) {
		*this = *this * mat;
		return *this;
	}

	friend inline Vector3 operator*(const Vector3& vec, const Matrix44& mat) {
		return{
			vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0],
			vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1],
			vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2] };
	}

	friend inline Vector4 operator* (const Vector4& v, const Matrix44& m) {
		return {
			v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + v.w * m.m[3][0],
			v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + v.w * m.m[3][1],
			v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + v.w * m.m[3][2],
			v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3] };
	}

	static inline Matrix44 CreateIdentity() {
		return{ 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f };
	}

	static inline Matrix44 CreateScaling(float scaleX, float scaleY, float scaleZ) {
		return{ scaleX,		0.0f,		0.0f,		0.0f,
				0.0f,		scaleY,		0.0f,		0.0f,
				0.0f,		0.0f,		scaleZ,		0.0f,
				0.0f,		0.0f,		0.0f,		1.0f };
	}
	static inline Matrix44 CreateScaling(float scale) {
		return CreateScaling(scale, scale, scale);
	};
	static inline Matrix44 CreateScaling(const Vector3& scale) {
		return CreateScaling(scale.x, scale.y, scale.z);
	}

	static inline Matrix44 CreateRotationX(float theta) {
		float c = cosf(theta);
		float s = sinf(theta);
		return{ 1.0f,		0.0f,		0.0f,		0.0f,
				0.0f,		c,			s,			0.0f,
				0.0f,		-s,			c,			0.0f,
				0.0f,		0.0f,		0.0f,		1.0f };
	}
	static inline Matrix44 CreateRotationY(float theta) {
		float c = cosf(theta);
		float s = sinf(theta);
		return{ c,			0.0f,		-s,			0.0f,
				0.0f,		1.0f,		0.0f,		0.0f,
				s,			0.0f,		c,			0.0f,
				0.0f,		0.0f,		0.0f,		1.0f };
	}
	static inline Matrix44 CreateRotationZ(float theta) {
		float c = cosf(theta);
		float s = sinf(theta);
		return{ c,			s,			0.0f,		0.0f,
				-s,			c,			0.0f,		0.0f,
				0.0f,		0.0f,		1.0f,		0.0f,
				0.0f,		0.0f,		0.0f,		1.0f };
	}
	static inline Matrix44 CreateRotationFromEuler(const Vector3& euler) {
		Vector3 s = { sinf(euler.x), sinf(euler.y), sinf(euler.z) };
		Vector3 c = { cosf(euler.x), cosf(euler.y), cosf(euler.z) };

		return {
			-s.x * s.y * s.z + c.y * c.z,	s.x * s.y * c.z + c.y * s.z,	-c.x * s.y,		0.0f,
			-c.x * s.z,						c.x * c.z,						s.x,			0.0f,
			s.x * c.y * s.z + s.y * c.z,	-s.x * c.y * c.z + s.y * s.z,	c.x * c.y,		0.0f,
			0.0f,							0.0f,							0.0f,			1.0f
		};
	}

	static Matrix44 CreateRotationFromQuaternion(const Quaternion& q) {
		// どちらが良いかわからない
#ifdef MATRIX_OPTIMIZE
		float w2 = q.w * q.w, x2 = q.x * q.x, y2 = q.y * q.y, z2 = q.z * q.z;
		float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;
		float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;

		return {
			w2 + x2 - y2 - z2,	2.0f * (wz + xy),	2.0f * (xz - wy),	0.0f,
			2.0f * (xy - wz),	w2 - x2 + y2 - z2,	2.0f * (yz + wx),	0.0f,
			2.0f * (wy + xz),	2.0f * (-wx + yz),	w2 - x2 - y2 + z2,	0.0f,
			0.0f,				0.0f,				0.0f,				1.0f
	};
#else
		return {
			q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z,	2.0f * (q.w * q.z + q.x * q.y),					2.0f * (q.x * q.z - q.w * q.y),					0.0f,
			2.0f * (q.x * q.y - q.w * q.z),					q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z,	2.0f * (q.y * q.z + q.w * q.x),					0.0f,
			2.0f * (q.w * q.y + q.x * q.z),					2.0f * (-q.w * q.x + q.y * q.z),				q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z,	0.0f,
			0.0f,											0.0f,											0.0f,											1.0f };
#endif // MATRIX_OPTIMIZE
	}

	static inline Matrix44 CreateTranslation(float x, float y, float z) {
		return{ 1.0f,	0.0f,	0.0f,	0.0f,
				0.0f,	1.0f,	0.0f,	0.0f,
				0.0f,	0.0f,	1.0f,	0.0f,
				x,		y,		z,		1.0f };
	}
	static inline Matrix44 CreateTranslation(const Vector3& trans) {
		return CreateTranslation(trans.x, trans.y, trans.z);
	}

	/// 向かせる行列 （向きベクトルと上ベクトルで作成）
	static inline Matrix44 CreateLookAt(const Vector3& pos, const Vector3& target, const Vector3& up) {
		Vector3 z = Normalize(target - pos);
		Vector3 x = Normalize(Cross(up, z));
		Vector3 y = Cross(z, x);
		return{
			x.x,	x.y,	x.z,	0.0f,
			y.x,	y.y,	y.z,	0.0f,
			z.x,	z.y,	z.z,	0.0f,
			0.0f,	0.0f,	0.0f,	1.0f };
	}
	

	static inline Matrix44 CreateView(const Vector3& eye, const Vector3& target, const Vector3& up) {
		Vector3 z = Normalize(target - eye);
		Vector3 x = Normalize(Cross(up, z));
		Vector3 y = Cross(z, x);
		Vector3 w = { -Dot(x,eye),-Dot(y,eye),-Dot(z,eye) };
		return{
			x.x,y.x,z.x,0.0f,
			x.y,y.y,z.y,0.0f,
			x.z,y.z,z.z,0.0f,
			w.x,w.y,w.z,1.0f };
	}

	static inline Matrix44 CreateProjection(float fovY, float aspect, float nearZ, float farZ) {
		float s = 1.0f / tanf(fovY / 2.0f);
		float a = farZ / (farZ - nearZ);
		return {
			 s / aspect,	0.0f,		0.0f,			0.0f ,
			 0.0f,			s,			0.0f,			0.0f ,
			 0.0f,			0.0f,		a,				1.0f ,
			 0.0f,			0.0f,		a * -nearZ,		0.0f };
	}

	static inline Matrix44 CreateProjection2(float fovY, float width, float height, float nearZ, float farZ) {
		float aspect = height / width;
		float cotd2 = 1.0f / tanf(fovY / 2.0f);
		float scaleZ = 1.0f / (farZ - nearZ);
		float transZ = -nearZ / (farZ - nearZ);
		return {
			aspect * cotd2, 0.0f,0.0f,0.0f,
			0.0f,cotd2,0.0f,0.0f,
			0.0f,0.0f,scaleZ,0.0f,
			0.0f,0.0f,transZ,1.0f };
	}

	static inline Matrix44 Create2DView(const Vector2& anchorPoint, const Vector2& scroll, const Vector2& scale, float theta) {
		Matrix44 result = CreateTranslation({ -anchorPoint, 0.0f });
		result *= CreateScaling({ scale, 0.0f });
		result *= CreateRotationZ(-theta);
		result *= CreateTranslation({ -scroll,0.0f });
		result *= CreateTranslation({ anchorPoint, 0.0f });
		return result;
	}

	static inline Matrix44 CreateOrthoProjection(float width, float height, float nearZ = 0.0f, float farZ = 1.0f) {
		return {
			 2.0f / width,	0.0f,				0.0f,					0.0f,
			 0.0f,			-2.0f / height,		0.0f,					0.0f,
			 0.0f,			0.0f,				1.0f / (farZ - nearZ),	0.0f,
			 -1.0f,			1.0f,				nearZ / (nearZ - farZ),	1.0f };
	}

	static inline Matrix44 CreateViewport(float left, float top, float width, float height, float nearZ = 0.0f, float farZ = 1.0f) {
		float halfW = width / 2.0f;
		float halfh = height / 2.0f;
		return {
			halfW,			0.0f,			0.0f,			0.0f,
			0.0f,			-halfh,			0.0f,			0.0f,
			0.0f,			0.0f,			farZ - nearZ,	0.0f,
			left + halfW,	top + halfh,	nearZ,			1.0f };
	}
};
