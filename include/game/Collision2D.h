#pragma once
#include "MathUtility.h"

namespace Collider2D {

	struct Circle
	{
		Vector2 center;
		float radius = 0;
	};

	struct OBB
	{
		Vector2 center;
		Vector2 direction[2];
		float size[2];
	};
}

namespace Collision2D {

	void ClosestPoint_Point_OBB(const Vector2& point, const Collider2D::OBB& obb, Vector2& outPt);

	bool Hit_Circle_OBB(const Collider2D::Circle& circle, const Collider2D::OBB& obb, Vector2& closestPt);

	bool Hit_Circle_Circle(const Collider2D::Circle& circle1, const Collider2D::Circle& circle2);
}