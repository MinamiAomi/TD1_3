#pragma once
#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "Vector2.h"
#include <cassert>

// 同じ型を３つ保持するクラス
template<class TYPE>
class Triplet {

public:
	TYPE x = {};	// x成分
	TYPE y = {};    // y成分
	TYPE z = {};	// z成分

public:
	Triplet() {}
	Triplet(const TYPE& x, const TYPE& y, const TYPE& z) : x(x), y(y), z(z) {}
	Triplet(const Triplet<TYPE>& t) : x(t.x), y(t.y), z(t.z) {}
	Triplet(const Twins<TYPE>& t, const TYPE& z) : x(t.x), y(t.y), z(z) {}
	virtual ~Triplet() {}
	// オーバーロード

	inline void Set(const TYPE& sx, const TYPE& sy, const TYPE& sz) { x = sx, y = sy, z = sz; }
	inline void Set(const Triplet& t) { x = t.x, y = t.y, z = t.z; }
	inline void Set(const Twins<TYPE>& t, const TYPE& iz) { x = t.x, y = t.y, z = iz; }
	inline TYPE& operator[](size_t i) { return *(&x + i); }

	inline Triplet operator+() const { return { x, y, z }; }
	inline Triplet operator-() const { return { -x,-y, -z }; }
	inline Triplet& operator+=(const Triplet& t) {
		x += t.x;
		y += t.y;
		z += t.z;
		return *this;
	}
	inline Triplet& operator-=(const Triplet& t) {
		x -= t.x;
		y -= t.y;
		z -= t.z;
		return *this;
	}
	inline Triplet& operator*=(const TYPE& s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	inline Triplet& operator/=(const TYPE& s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
};

// 3Dベクトル
class Vector3
{
public:
	static const Vector3 Zero;
	static const Vector3 UnitX;	
	static const Vector3 UnitY;
	static const Vector3 UnitZ;

public:
	float x = 0.0f;	// x成分
	float y = 0.0f; // y成分
	float z = 0.0f; // z成分

public:
	inline Vector3() {}
	inline Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	inline Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
	inline Vector3(const Vector2& v2, float z) : x(v2.x), y(v2.y), z(z) {}
	inline Vector3(float xyz) : x(xyz), y(xyz), z(xyz) {}

	inline void Set(float x, float y, float z) { *this = { x, y, z }; }
	inline void Set(const Vector3& v) { *this = v; }
	inline void Set(const Vector2& v, float z) { *this = { v, z }; }
	inline float& operator[](size_t i) { return *(&x + i); }

	inline void xy(const Vector2& xy) { x = xy.x, y = xy.y; }
	inline void yz(const Vector2& yz) { y = yz.x, z = yz.y; }
	inline void xz(const Vector2& xz) { x = xz.x, z = xz.y; }

	inline Vector2 xy() const { return { x, y }; }
	inline Vector2 yz() const { return { y, z }; }
	inline Vector2 xz() const { return { x, z }; }

	inline Vector3 operator+() const { return { x, y, z }; }
	inline Vector3 operator-() const { return { -x,-y, -z }; }
	inline Vector3& operator+=(const Vector3& t) {
		x += t.x;
		y += t.y;
		z += t.z;
		return *this;
	}
	inline Vector3& operator-=(const Vector3& t) {
		x -= t.x;
		y -= t.y;
		z -= t.z;
		return *this;
	}
	inline Vector3& operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	inline Vector3& operator/=(float s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	friend inline Vector3 operator+(const Vector3& a, const Vector3& b) {
		return { a.x + b.x, a.y + b.y, a.z + b.z };
	}
	friend inline Vector3 operator-(const Vector3& a, const Vector3& b) {
		return { a.x - b.x, a.y - b.y, a.z - b.z };
	}
	friend inline Vector3 operator*(const Vector3& a, float s) {
		return { a.x * s, a.y * s, a.z * s };
	}
	friend inline Vector3 operator*(float s, const Vector3& a) {
		return { s * a.x, s * a.y, s * a.z };
	}
	friend inline Vector3 operator/(const Vector3& a, float s) {
		return { a.x / s, a.y / s, a.z / s };
	}
	friend inline Vector3 Multipliy(const Vector3& v1, const Vector3& v2) {
		return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
	}
	// 内積
	friend inline float Dot(const Vector3& v1, const Vector3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	// 外積
	friend inline Vector3 Cross(const Vector3& v1, const Vector3& v2) {
		return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x -v1. x * v2.z, v1.x * v2.y - v1.y * v2.x };
	}
	// 他ベクトルとの距離
	friend inline float Distance(const Vector3& v1, const Vector3& v2) {
		return (v2 - v1).Length();
	}
	// 中点
	friend inline Vector3 Mid(const Vector3& v1, const Vector3& v2) {
		return (v1 + v2) / 2.0f;
	}
	// 線形補間
	friend inline  Vector3 Lerp(float param, const  Vector3& start, const  Vector3& end) {
		return start + param * (end - start);
	}
	
	// 長さの二乗
	inline float LengthSquare() const {
		return Dot(*this, *this);
	}
	// 長さ
	inline float Length() const {
		return sqrtf(LengthSquare());
	}

	// 正規化
	inline Vector3 Normalized() const {
		return *this / Length();
	}
	inline Vector3 RotatedX(float angle) const {
		float s = sinf(angle);
		float c = cosf(angle);
		return { x, y * c - z * s, y * s + z * c };
	}

	inline Vector3 RotatedY(float angle) const {
		float s = sinf(angle);
		float c = cosf(angle);
		return { x * c + z * s, y, -x * s + z * c };
	}

	inline Vector3 RotatedZ(float angle) const {
		float s = sinf(angle);
		float c = cosf(angle);
		return { x * c - y * s, x * s + y * c, z };
	}

	friend Vector3 Normalize(const Vector3& v) {
		return v.Normalized();
	}
	
	friend inline Vector3 Reflected(const Vector3& v, const Vector3& normal) {
		return Dot(normal, -v) * 2.0f * normal + v;
	}
	friend inline Vector3 AlongWall(const Vector3& v, const Vector3& normal) {
		return Dot(normal, -v) * normal + v;
	}
	inline bool IsZero() const {
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	friend inline bool operator==(const Vector3& v1, const Vector3& v2) {
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}
	friend inline bool operator!=(const Vector3& v1, const Vector3& v2) {
		return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
	}
}; 


#endif