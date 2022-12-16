#pragma once
#include <cmath>	
#include <cassert>
// 同じ型を２つ保持するクラス（Vector2の親）
template<class TYPE>
class Twins {

public:
	TYPE x;	// x成分
	TYPE y; // y成分


public:
	Twins() {}
	Twins(const TYPE& x, const TYPE& y) : x(x), y(y) {}
	Twins(const Twins& p) : x(p.x), y(p.y) {}
	virtual ~Twins() {}
	// オーバーロード

	inline void Set(const TYPE& sx, const TYPE& sy) { x = sx, y = sy; }
	inline void Set(const Twins& p) { x = p.x, y = p.y; }

	inline Twins operator+() const { return { x, y }; }
	inline Twins operator-() const { return { -x,-y }; }
	inline Twins& operator+=(const Twins& p) {
		x += p.x;
		y += p.y;
		return *this;
	}
	inline Twins& operator-=(const Twins& p) {
		x -= p.x;
		y -= p.y;
		return *this;
	}
	inline Twins& operator*=(const TYPE& s) {
		x *= s;
		y *= s;
		return *this;
	}
	inline Twins& operator/=(const TYPE& s) {
		x /= s;
		y /= s;
		return *this;
	}
};

// 2Dベクトル
class Vector2 
{
public:

	float x;	// x成分
	float y; // y成分

public:
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(const Vector2& v) : x(v.x), y(v.y) {}
	~Vector2() {}

	inline void Set(float sx, float sy) { x = sx, y = sy; }
	inline void Set(const Vector2& p) { x = p.x, y = p.y; }

	inline Vector2 operator+() const { return { x, y }; }
	inline Vector2 operator-() const { return { -x,-y }; }
	inline Vector2& operator+=(const Vector2& p) {
		x += p.x;
		y += p.y;
		return *this;
	}
	inline Vector2& operator-=(const Vector2& p) {
		x -= p.x;
		y -= p.y;
		return *this;
	}
	inline Vector2& operator*=(float s) {
		x *= s;
		y *= s;
		return *this;
	}
	inline Vector2& operator/=(float s) {
		x /= s;
		y /= s;
		return *this;
	}

	friend inline Vector2 operator+(const Vector2& a, const Vector2& b) {
		return { a.x + b.x, a.y + b.y };
	}
	friend inline Vector2 operator-(const Vector2& a, const Vector2& b) {
		return { a.x - b.x, a.y - b.y };
	}
	friend inline Vector2 operator*(const Vector2& a, float s) {
		return { a.x * s, a.y * s };
	}
	friend inline Vector2 operator*(float s, const Vector2& a) {
		return { s * a.x, s * a.y };
	}
	friend inline Vector2 operator/(const Vector2& a, float s) {
		return { a.x / s, a.y / s };
	}

	inline float Dot(const Vector2& vec) const {
		return x * vec.x + y * vec.y;
	}

	inline float Cross(const Vector2& vec) const {
		return x * vec.y - y * vec.x;
	}
	// 長さの二乗
	inline float LengthSquare() const {
		return Dot(*this);
	}

	inline float Length() const {
		return sqrtf(LengthSquare());
	}

	// 他ベクトルとの距離
	inline float Distance(const  Vector2& v) const {
		return (v - *this).Length();
	}

	inline Vector2 Normalized() const {
		float len = Length();
		assert(len != 0);
		return *this / len;
	}

	// 中点
	inline Vector2 Mid(const Vector2& v) const {
		return (*this + v) / 2.0f;
	}

	inline Vector2 Rotated(float theta) const {
		float s = sinf(theta);
		float c = cosf(theta);
		return { x * c - y * s, x * s + y * c };
	}


	// 線形補間
	static inline  Vector2 Lerp(float t, const  Vector2& start, const  Vector2& end) {
		return start + t * (end - start);
	}

	static inline float Dot(const Vector2& a, const Vector2& b) {
		return a.x * b.x + a.y * b.y;
	}

	static inline float Cross(const Vector2& a, const Vector2& b) {
		return a.x * b.y - a.y * b.x ;
	}

	static inline float LengthSquare(const Vector2& a) {
		return Dot(a, a);
	}

	static inline float Length(const Vector2& a) {
		return sqrtf(LengthSquare(a));
	}

	static inline Vector2 Normalize(const Vector2& a) {
		float len = Length(a);
		return len != 0 ? a / len : a;
	}

	// 中点
	static inline Vector2 Mid(const Vector2& a, const Vector2& b) {
		return (a + b) / 2.0f;
	}
};