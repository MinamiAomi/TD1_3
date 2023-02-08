#pragma once
#include "Vector3.h"

class Quaternion 
{

public:
	// 単位クォータニオン
	static const Quaternion Identity;

public:
	float x;
	float y;
	float z;
	float w;

private:
	// ベクトル部
	inline Vector3 vector() const;

public:
	inline Quaternion();
	inline Quaternion(float x, float y, float z, float w);
	inline explicit Quaternion(float angle, const Vector3& axis);
	/// <summary>
	/// 軸と角度を取得
	/// </summary>
	/// <param name="outAngle">角度</param>
	/// <param name="outAxis">軸</param>
	inline void ToAngleAxis(float& outAngle, Vector3& outAxis) const;
	/// <summary>
	/// オイラー角を取得（ロールピッチヨー順 ZXY）
	/// </summary>
	/// <param name="outEuler">オイラー角</param>
	inline void ToEuler(Vector3& outEuler) const;
	/// <summary>
	/// 個別に設定する（基本使わない）
	/// </summary>
	/// <param name="ix"></param>
	/// <param name="iy"></param>
	/// <param name="iz"></param>
	/// <param name="iw"></param>
	inline void Set(float inx, float iny, float inz, float inw);
	/// <summary>
	/// 軸と軸周りの角度からクォータニオンを生成
	/// </summary>
	/// <param name="angle">角度</param>
	/// <param name="axis">軸（正規化）</param>
	/// <returns>クォータニオン</returns>
	static inline Quaternion CreateFromAngleAxis(float angle, const Vector3& axis);
	/// <summary>
	/// オイラー角からクォータニオンを生成（ロールピッチヨー順 ZXY）
	/// </summary>
	/// <param name="euler">オイラー角（ピッチ― ヨー ロール）</param>
	/// <returns>クォータニオン</returns>
	static inline Quaternion CreateFromEuler(const Vector3& euler);
	static inline Quaternion CreateFromPitch(float angle);
	static inline Quaternion CreateFromYaw(float angle);
	static inline Quaternion CreateFromRoll(float angle);
	/// <summary>
	/// 正規化された二つのベクトルからクォータニオンを生成
	/// </summary>
	/// <param name="v1">正規化ベクトル</param>
	/// <param name="v2">正規化ベクトル</param>
	/// <returns></returns>
	static inline Quaternion CreateFromTwoVector(const Vector3& v1, const Vector3& v2);

	friend inline Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
	friend inline Quaternion operator*(float s, const Quaternion& q);
	friend inline Quaternion operator*(const Quaternion& q, float s);
	friend inline Quaternion operator/(const Quaternion& q, float s);
	friend inline Quaternion operator*(const Quaternion& q, const Quaternion& p);
	friend inline Vector3 operator*(const Quaternion& q, const Vector3& v);
	// 内積
	friend inline float Dot(const Quaternion& q, const Quaternion& p);
	// ベクトルを変換する
	friend inline Vector3 TransForm(const Quaternion& q, const Vector3& v);
	// 長さの二乗
	inline float LengthSquare() const;
	// 長さ
	inline float Length() const;
	// 正規化
	inline Quaternion Normalized() const;
	// 軸周りの角度
	inline float Angle() const;
	// 回転軸
	inline Vector3 Axis() const;

	/// <summary>
	/// 共役
	/// </summary>
	/// <returns></returns>
	inline Quaternion Conjugate() const;
	/// <summary>
	/// 逆
	/// </summary>
	/// <returns></returns>
	inline Quaternion Inverse() const;
	/// <summary>
	/// 球面線形補間
	/// </summary>
	/// <param name="t"></param>
	/// <param name="start"></param>
	/// <param name="end"></param>
	/// <returns></returns>
	static inline Quaternion Slerp(float param, const Quaternion& start, const Quaternion& end);

	bool operator==(const Quaternion& q) {
		return x == q.x && y == q.y && z == q.z && w == q.w;
	}
};


inline Vector3 Quaternion::vector() const {
	return { x,y,z };
}
inline Quaternion::Quaternion() {
	*this = Identity;
}
inline Quaternion::Quaternion(float x, float y, float z, float w) :
	x(x), y(y), z(z), w(w) {}
inline Quaternion::Quaternion(float angle, const Vector3& axis) {
	float sin2 = sinf(angle / 2.0f);
	x = axis.x * sin2;
	y = axis.y * sin2;
	z = axis.z * sin2;
	w = cosf(angle / 2.0f);
}
inline Quaternion Quaternion::CreateFromAngleAxis(float angle, const Vector3& axis) {
	return Quaternion(angle, axis);
}
inline Quaternion Quaternion::CreateFromEuler(const Vector3& euler) {
	// ピッチ ヨー ロールの順
	Vector3 s = { sinf(euler.x / 2.0f), sinf(euler.y / 2.0f), sinf(euler.z / 2.0f) };
	Vector3 c = { cosf(euler.x / 2.0f), cosf(euler.y / 2.0f), cosf(euler.z / 2.0f) };
	Quaternion result;
	result.x = -c.x * s.y * s.z + s.x * c.y * c.z;
	result.y = c.x * s.y * c.z + s.x * c.y * s.z;
	result.z = s.x * s.y * c.z + c.x * c.y * s.z;
	result.w = -s.x * s.y * s.z + c.x * c.y * c.z;
	return result;
}
inline Quaternion Quaternion::CreateFromPitch(float angle) {
	return { sinf(angle / 2.0f),0.0f,0.0f,cosf(angle / 2.0f) };
}
inline Quaternion Quaternion::CreateFromYaw(float angle) {
	return { 0.0f,sinf(angle / 2.0f),0.0f,cosf(angle / 2.0f) };
}
inline Quaternion Quaternion::CreateFromRoll(float angle) {
	return { 0.0f,0.0f,sinf(angle / 2.0f),cosf(angle / 2.0f) };
}
inline Quaternion Quaternion::CreateFromTwoVector(const Vector3& v1, const Vector3& v2) {
	Vector3 axis = Cross(v1, v2);
	float angle = acosf(Dot(v1, v2));
	return Quaternion(angle, Normalize(axis));
}
inline Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
	return { q1.x + q2.x,q1.y + q2.y,q1.z + q2.z,q1.w + q2.w };
}
inline void Quaternion::ToAngleAxis(float& outAngle, Vector3& outAxis) const {
	float acw = acosf(w);
	outAngle = acw * 2.0f;
	outAxis = vector() / sinf(acw);
}
inline void Quaternion::ToEuler(Vector3& outEuler) const {
	outEuler.x = asinf(2.0f * y * z + 2.0f * x * w);
	if (outEuler.x != 0.0f) {
		outEuler.y = atanf(-((2.0f * x * z + -2.0f * y * w) / (2.0f * w * w + 2.0f * z * z - 1)));
		outEuler.z = atanf(-((2.0f * x * y + -2.0f * z * w) / (2.0f * w * w + 2.0f * y * y - 1)));
		return;
	}
	outEuler.y = 0.0f;
	outEuler.z = atanf((2.0f * x * y + 2.0f * z * w) / (2.0f * w * w + 2.0f * x * x - 1));
}
inline Quaternion operator*(float s, const Quaternion& q) {
	return { s * q.x,s * q.y,s * q.z,s * q.w };
}
inline Quaternion operator*(const Quaternion& q, float s) {
	return { q.x * s, q.y * s, q.z * s, q.w * s };
}
inline Quaternion operator/(const Quaternion& q, float s) {
	return { q.x / s, q.y / s, q.z / s, q.w / s };
}
inline Quaternion operator*(const Quaternion& q, const Quaternion& p) {
	Vector3 qv = q.vector();
	Vector3 pv = p.vector();
	Vector3 v = q.w * pv + p.w * qv + Cross(qv, pv);
	float w = q.w * p.w - Dot(qv, pv);
	return { v.x, v.y, v.z, w };
}
inline Vector3 operator*(const Quaternion& q, const Vector3& v) {
	Vector3 qv(q.x, q.y, q.z);
	return v + 2.0f * Cross(qv, Cross(qv, v) + q.w * v);
}
inline Vector3 TransForm(const Quaternion& q, const Vector3& v) {
	Vector3 qv(q.x, q.y, q.z);
	return v + 2.0f * Cross(qv, Cross(qv, v) + q.w * v);
}
inline float Dot(const Quaternion& q, const Quaternion& p) {
	return q.x * p.x + q.y * p.y + q.z * p.z + q.w * p.w;
}
inline float Quaternion::LengthSquare() const {
	return Dot(*this, *this);
}
inline float Quaternion::Length() const {
	return sqrtf(LengthSquare());
}
inline Quaternion Quaternion::Normalized() const {
	float len = Length();
	return *this / len;
}
inline void Quaternion::Set(float ix, float iy, float iz, float iw) {
	x = ix, y = iy, z = iz, w = iw;
}
inline float Quaternion::Angle() const {
	return acosf(w) * 2.0f;
}
inline Vector3 Quaternion::Axis() const {
	return vector() / sinf(acosf(w));
}

inline Quaternion Quaternion::Conjugate() const {
	return { -x, -y, -z, w };
}
inline Quaternion Quaternion::Inverse() const {
	return Conjugate() / LengthSquare();
}
inline Quaternion Quaternion::Slerp(float param, const Quaternion& start, const Quaternion& end) {
	Quaternion s = start;
	float dot_val = Dot(start,end);
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
	return (std::sin((1 - param) * theta) * s + std::sin(param * theta) * end) / std::sin(theta);
	
	//float dot = Dot(start, end);
	//float theta = acosf(dot);
	//return sinf((1 - param) * theta) * start + sinf(param * theta) * end / sinf(theta);


}