#pragma once
#include "Vector3.h"

// 同じ型を４つ保持するクラス（Vector2の親）
template<class TYPE>
class Quadruplet {

public:
	TYPE x;	// x成分
	TYPE y; // y成分
	TYPE z; // z成分
	TYPE w; // w成分

public:
	Quadruplet() {}
	Quadruplet(const TYPE& x, const TYPE& y, const TYPE& z, const TYPE& w) : x(x), y(y), z(z), w(w) {}
	Quadruplet(const Quadruplet<TYPE>& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
	virtual ~Quadruplet() {}
	// オーバーロード

	inline void Set(const TYPE& sx, const TYPE& sy, const TYPE& sz, const TYPE& sw)
	{
		x = sx, y = sy, z = sz, w = sw;
	}
	inline void Set(const Quadruplet& q) { x = q.x, y = q.y, z = q.z, w = q.w; }

	inline Quadruplet operator+() const { return { x, y, z, w }; }
	inline Quadruplet operator-() const { return { -x,-y, -z, -w }; }
	inline Quadruplet& operator+=(const Quadruplet& q) {
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
		return *this;
	}
	inline Quadruplet& operator-=(const Quadruplet& q) {
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;
		return *this;
	}
	inline Quadruplet& operator*=(const TYPE& s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	inline Quadruplet& operator/=(const TYPE& s) {
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}
};

// 4Dベクトル
class Vector4 
{
public:
	float x;	// x成分
	float y; // y成分
	float z; // z成分
	float w; // w成分

public:
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	Vector4(const Vector3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
	Vector4(const Vector2& v1, const Vector2& v2) : x(v1.x), y(v1.y), z(v2.x), w(v2.y) {}
	~Vector4() {}

	Vector3 xyz() const { return { x,y,z }; }
	Vector2 xy() const { return { x,y }; }

	void xyz(float ix, float iy, float iz) { x = ix, y = iy, z = iz; }
	void xy(float ix, float iy) { x = ix, y = iy; }
};

