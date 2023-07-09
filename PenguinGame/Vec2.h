#pragma once

// vector in R2
class Vec2
{
public:
	float x, y;

	Vec2(float x, float y);

	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator*(const float rhs) const;
	bool operator==(const Vec2& rhs) const;
	bool operator!=(const Vec2& rhs) const;
	static float Angle(Vec2 v1, Vec2 v2);
	static float Magnitude(Vec2 v);
	static float Dot(Vec2 v1, Vec2 v2);
	static float Det(Vec2 v1, Vec2 v2);
	static Vec2 Norm(Vec2 v);
	static Vec2 Rotate(Vec2 v, float angle);
};