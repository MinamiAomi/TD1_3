#pragma once
#include <cmath>	


// 2D�x�N�g��
class Vector2
{
public:
	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;

public:

	float x = 0.0f;	// x����
	float y = 0.0f; // y����

public:
	inline Vector2() {}
	inline Vector2(float x, float y) : x(x), y(y) {}
	inline Vector2(const Vector2& v) : x(v.x), y(v.y) {}

	inline void Set(float sx, float sy) { x = sx, y = sy; }
	inline void Set(const Vector2& p) { x = p.x, y = p.y; }
	inline float& operator[](size_t i) { return *(&x + i); }
	inline Vector2 operator+() const { return { x, y }; }
	inline Vector2 operator-() const { return { -x,-y }; }
	inline Vector2& operator+=(const Vector2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	inline Vector2& operator-=(const Vector2& v) {
		x -= v.x;
		y -= v.y;
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
	// ����
	friend inline float Dot(const Vector2& v1, const Vector2& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	// �O��
	friend inline float Cross(const Vector2& v1, const Vector2& v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	// ���x�N�g���Ƃ̋���
	friend inline float Distance(const Vector2& v1, const  Vector2& v2) {
		return (v2 - v1).Length();
	}
	// ���_
	friend inline Vector2 Mid(const Vector2& v1, const Vector2& v2) {
		return (v1 + v2) / 2.0f;
	}
	// ���`���
	friend inline  Vector2 Lerp(float param, const  Vector2& start, const  Vector2& end) {
		return start + param * (end - start);
	}
	// �����̓��
	inline float LengthSquare() const {
		return Dot(*this, *this);
	}
	//�@����
	inline float Length() const {
		return sqrtf(LengthSquare());
	}
	// ���K��
	inline Vector2 Normalized() const {
		return *this / Length();
	}
	// ��]
	inline Vector2 Rotated(float angle) const {
		float s = sinf(angle);
		float c = cosf(angle);
		return { x * c - y * s, x * s + y * c };
	}

	friend inline Vector2 Reflected(const Vector2& v, const Vector2& normal) {
		return Dot(normal, -v) * 2.0f * normal + v;
	}
	friend inline Vector2 WallSlided(const Vector2& v, const Vector2& normal) {
		return Dot(normal, -v) * normal + v;
	}
	inline bool IsZero() const {
		return x == 0.0f && y == 0.0f;
	}

	friend inline bool operator==(const Vector2& v1, const Vector2& v2) {
		return v1.x == v2.x && v1.y == v2.y;
	}
	friend inline bool operator!=(const Vector2& v1, const Vector2& v2) {
		return v1.x != v2.x || v1.y != v2.y;
	}
};

// �����^���Q�ێ�����N���X�iVector2�̐e�j
template<class TYPE>
class Twins {

public:
	TYPE x;	// x����
	TYPE y; // y����


public:
	Twins() {}
	Twins(const TYPE& x, const TYPE& y) : x(x), y(y) {}
	Twins(const Twins& p) : x(p.x), y(p.y) {}
	virtual ~Twins() {}
	// �I�[�o�[���[�h

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
	inline TYPE& operator[](size_t i) {
		return *(&x + i);
	}
};
