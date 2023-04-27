#pragma once
#ifndef RECT_H
#define RECT_H
#include "Vec2.h"

// represents position and dimensions
class Rect
{
public:
	float x, y, w, h;

	Rect();
	Rect(float x, float y, float w, float h);

	bool Contains(const Vec2& pos);	// checks if represented box has this vec2 point
};

#endif // RECT_H
