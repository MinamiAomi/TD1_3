#pragma once
#include "Vector2.h"

namespace Shape2D 
{
	// ��]������`
	struct Rect
	{
		Vector2 center;
		float width;
		float height;

		Vector2 LeftTop() const {
			return { center.x - width / 2.0f, center.y + height / 2.0f };
		}
		Vector2 RightTop() const {
			return { center.x + width / 2.0f, center.y + height / 2.0f };
		}
		Vector2 LeftBottom() const {
			return { center.x - width / 2.0f, center.y - height / 2.0f };
		}
		Vector2 RightBottom() const {
			return { center.x + width / 2.0f, center.y - height / 2.0f };
		}
	};
	// ��]�����`
	struct RectAngle : public Rect
	{
		float rotate;

		Vector2 LeftTop() const {
			Vector2 tmp = { -width / 2.0f, height / 2.0f };
			return { center + tmp.Rotated(rotate) };
		}
		Vector2 RightTop() const {
			Vector2 tmp = { width / 2.0f, height / 2.0f };
			return { center + tmp.Rotated(rotate) };
		}
		Vector2 LeftBottom() const {
			Vector2 tmp = { -width / 2.0f, -height / 2.0f };
			return { center + tmp.Rotated(rotate) };

		}
		Vector2 RightBottom() const {
			Vector2 tmp = { width / 2.0f, -height / 2.0f };
			return { center + tmp.Rotated(rotate) };
		}
	};
	// �~
	struct Circle
	{
		Vector2 center;
		float radius = 1.0f;
	};
	// ����
	struct Segment
	{
		Vector2 start;
		Vector2 end;

		Vector2 Vector() const {
			return end - start;
		}
	};
	// ���C
	struct Ray
	{
		Vector2 start;
		Vector2 direction;
	};
	// �J�v�Z��
	struct Capsule : Segment
	{
		float radius;
	};

};