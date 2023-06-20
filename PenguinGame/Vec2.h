#pragma once

// vector in R2
class Vec2
{
public:
	float x, y;

	Vec2(float x, float y);
	Vec2 GetRotated(float angle);

	static Vec2 Sum(Vec2 v1, Vec2 v2);
	static Vec2 Subtract(Vec2 v1, Vec2 v2);
	static float Angle(Vec2 v1, Vec2 v2);
	static float Magnitude(Vec2 v);
	static float Dot(Vec2 v1, Vec2 v2);
	static float Det(Vec2 v1, Vec2 v2);
	static Vec2 Normalize(Vec2 v);
};