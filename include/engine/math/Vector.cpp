#include "Vector2.h"
#include "Vector3.h"

// �[���x�N�g��
const Vector2 Vector2::Zero = { 0.0f, 0.0f };
// X�������̒P�ʃx�N�g��(1,0)
const Vector2 Vector2::UnitX = { 1.0f, 0.0f };
// Y�������̒P�ʃx�N�g��(0,1)
const Vector2 Vector2::UnitY = { 0.0f, 1.0f };

// �[���x�N�g��
const Vector3 Vector3::Zero = { 0.0f, 0.0f, 0.0f };
// X�������̒P�ʃx�N�g��(1,0,0)
const Vector3 Vector3::UnitX = { 1.0f, 0.0f, 0.0f };
// Y�������̒P�ʃx�N�g��(0,1,0)
const Vector3 Vector3::UnitY = { 0.0f, 1.0f, 0.0f };
// Z�������̒P�ʃx�N�g��(0,0,1)
const Vector3 Vector3::UnitZ = { 0.0f, 0.0f, 1.0f };