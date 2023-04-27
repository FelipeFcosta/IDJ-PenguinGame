#include "Vec2.h"
#include <cmath>

Vec2::Vec2(float x, float y) : x(x), y(y) {}

// rotates clockwise, since y grows downward
Vec2 Vec2::GetRotated(float angle) {
	return { x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle) };
}

Vec2 Vec2::Sum(Vec2& v1, Vec2& v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}
