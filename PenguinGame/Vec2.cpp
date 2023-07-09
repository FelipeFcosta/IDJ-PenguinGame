#include "Vec2.h"
#include <cmath>

Vec2::Vec2(float x, float y) : x(x), y(y) {
};

Vec2 Vec2::Norm(Vec2 v) {
	float magnitude = Magnitude(v);
	return { v.x/magnitude, v.y/magnitude};
}

// rotates clockwise, since y grows downward
Vec2 Vec2::Rotate(Vec2 v, float angle) {
	return { v.x * cos(angle) - v.y * sin(angle), v.x * sin(angle) + v.y * cos(angle) };
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float rhs) const {
	return Vec2(x * rhs, y * rhs);
}

bool Vec2::operator==(const Vec2& rhs) const {
	return x == rhs.x && y == rhs.y;
}

bool Vec2::operator!=(const Vec2& rhs) const {
	return x != rhs.x || y != rhs.y;
}

float Vec2::Dot(Vec2 v1, Vec2 v2) {
	return  v1.x * v2.x + v1.y * v2.y;
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
