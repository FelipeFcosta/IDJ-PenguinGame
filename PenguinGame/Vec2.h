#pragma once

// vector in R2
class Vec2
{
public:
	float x, y;

	Vec2(float x, float y);
	Vec2 GetRotated(float angle);

	static Vec2 Sum(Vec2& v1, Vec2& v2);
};