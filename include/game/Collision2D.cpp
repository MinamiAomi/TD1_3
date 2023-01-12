#include "Collision2D.h"

void Collision2D::ClosestPoint_Point_OBB(const Vector2& point, const Collider2D::OBB& obb, Vector2& outPt)
{
	Vector2 d = point - obb.center;
	outPt = obb.center;
	float dist;
	for (int i = 0; i < 2; i++) {
		dist = Dot(d, obb.direction[i]);
		if (dist > obb.size[i]) {
			dist = obb.size[i];
		}
		if (dist < -obb.size[i])
		{
			dist = -obb.size[i];
		}
		outPt += dist * obb.direction[i];
	}
}

bool Collision2D::Hit_Circle_OBB(const Collider2D::Circle& circle, const Collider2D::OBB& obb, Vector2& closestPt)
{
	ClosestPoint_Point_OBB(circle.center, obb, closestPt);
	Vector2 v = closestPt - circle.center;
	return v.LengthSquare() <= circle.radius * circle.radius;
}
