#pragma once
#include "Vector2.h"

namespace Shape2D 
{
	// 回転無し矩形
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
	// 回転あり矩形
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
	// 円
	struct Circle
	{
		Vector2 center;
		float radius = 1.0f;
	};
	// 線分
	struct Segment
	{
		Vector2 start;
		Vector2 end;

		Vector2 Vector() const {
			return end - start;
		}
	};
	// レイ
	struct Ray
	{
		Vector2 start;
		Vector2 direction;
	};
	// カプセル
	struct Capsule : Segment
	{
		float radius;
	};

};