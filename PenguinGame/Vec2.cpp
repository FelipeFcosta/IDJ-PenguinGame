#include "Vec2.h"
#include <cmath>

Vec2::Vec2(float x, float y) : x(x), y(y) {
};


// rotates clockwise, since y grows downward
Vec2 Vec2::GetRotated(float angle) {
	return { x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle) };
}

Vec2 Vec2::Normalize(Vec2 v) {
	float magnitude = Magnitude(v);
	return { v.x/magnitude, v.y/magnitude};
}

Vec2 Vec2::Sum(Vec2 v1, Vec2 v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}

Vec2 Vec2::Subtract(Vec2 v1, Vec2 v2) {
	return { v1.x - v2.x, v1.y - v2.y };
}

float Vec2::Dot(Vec2 v1, Vec2 v2) {
	return  v1.x * v2.x + v1.y * v2. y;
}

float Vec2::Det(Vec2 v1, Vec2 v2) {
	return  v1.x * v2.y - v1.y * v2.x;
}

float Vec2::Angle(Vec2 v1, Vec2 v2) {
	return atan2(Det(v1, v2), Dot(v1, v2));;
}

float Vec2::Magnitude(Vec2 v) {
	return sqrt(powf(v.x, 2) + powf(v.y, 2));
}
