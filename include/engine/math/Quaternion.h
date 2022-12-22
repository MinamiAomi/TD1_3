#pragma once
#include "Vector3.h"
#include "Matrix44.h"

class Quaternion 
{

private:
	float x;
	float y;
	float z;
	float w;

private:
	inline Vector3 xyz() const {
		return { x,y,z };
	}

public:
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) :
		x(x), y(y), z(z), w(w) {}
	Quaternion(float angle, const Vector3& axis) {
		float sin2 = sinf(angle / 2.0f);
		x = axis.x * sin2;
		y = axis.y * sin2;
		z = axis.z * sin2;
		w = cosf(angle / 2.0f);
	}
	/// <summary>
	/// 軸と軸周りの角度からクォータニオンを生成
	/// </summary>
	/// <param name="angle">角度</param>
	/// <param name="axis">軸</param>
	/// <returns>クォータニオン</returns>
	static Quaternion CreateFromAngleAxis(float angle, const Vector3& axis) {
		return { angle,axis };
	}
	/// <summary>
	/// オイラー角からクォータニオンを生成（ロールピッチヨー順 ZXY）
	/// </summary>
	/// <param name="euler">オイラー角（ピッチ― ヨー ロール）</param>
	/// <returns>クォータニオン</returns>
	static Quaternion CreateFromEuler(const Vector3& euler) {
		Vector3 s = { sinf(euler.x / 2.0f), sinf(euler.y / 2.0f), sinf(euler.z / 2.0f) };
		Vector3 c = { cosf(euler.x / 2.0f), cosf(euler.y / 2.0f), cosf(euler.z / 2.0f) };
		Quaternion result;
		result.x = -c.x * s.y * s.z + s.x * c.y * c.z;
		result.y = c.x * s.y * c.z + s.x * c.y * s.z;
		result.x = s.x * s.y * c.z + c.x * c.y * s.z;
		result.x = -s.x * s.y * s.z + c.x * c.y * c.z;
		return result;
	}

	static Quaternion CreateFromFixed(const Vector3& fixed) {

	}

	friend inline Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
		return { q1.x + q2.x,q1.y + q2.y,q1.z + q2.z,q1.w + q2.w };
	}
	friend inline Quaternion operator*(float s, const Quaternion& q) {
		return { s * q.x,s * q.y,s * q.z,s * q.w };
	}
	friend inline Quaternion operator*(const Quaternion& q, float s) {
		return { q.x * s, q.y * s, q.z * s, q.w * s };
	}
	friend inline Quaternion operator/(const Quaternion& q, float s) {
		return { q.x / s, q.y / s, q.z / s, q.w / s };
	}
	friend inline Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
		Vector3 v1 = q1.xyz();
		Vector3 v2 = q2.xyz();
		Vector3 v = q1.w * v2 + q2.w * v1 + Cross(v1, v2);
		float w = q1.w * q2.w - Vector3::Dot(v1, v2);
		return { v.x, v.y, v.z, w };
	}
	static inline Vector3 TransForm(const Vector3& r, const Quaternion& q) {
		Vector3 v(q.x, q.y, q.z);
		return r + 2.0f * Cross(v, Cross(v, r) + q.w * r);
	}
	inline float Dot(const Quaternion& q) const {
		return x * q.x + y * q.y + z * q.z + w * q.w;
	}
	inline float LengthSquare() const {
		return Dot(*this);
	}
	inline float Length() const {
		return sqrtf(LengthSquare());
	}
	inline Quaternion Normalized() const {
		float len = Length();
		return *this / len;
	}
	inline void Set(float ix, float iy, float iz, float iw) {
		x = ix, y = iy, z = iz, w = iw;
	}
	inline void ToAngleAxis(float& outAngle, Vector3& outAxis) const {
		float acw = acosf(w);
		outAngle = acw * 2;
		outAxis = xyz() / sinf(acw);
	}

	inline float Angle() const {
		return acosf(w) * 2.0f;
	}
	inline Vector3 Axis() const { 
		return xyz() / sinf(acosf(w));
	}

	inline Quaternion Conjugate() const {
		return { -x, -y, -z, w };
	}
	inline Quaternion Inverse() const {
		return Conjugate() / LengthSquare();
	}


	static Quaternion Slerp(float t, const Quaternion& start, const Quaternion& end) {
		Quaternion s = start;
		float dot_val = start.Dot(end);
		// q1, q2が反対向きの場合
		if (dot_val < 0) {
			s.w = -s.w;
			s.x = -s.x;
			s.y = -s.y;
			s.z = -s.z;
			dot_val = -dot_val;
		}
		// 球面線形補間の計算
		float theta = std::acos(dot_val);
		return (std::sin((1 - t) * theta) * s + std::sin(t * theta) * end) / std::sin(theta);
	}
};