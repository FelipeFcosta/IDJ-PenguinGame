#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0) {}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

// e.g rect = {0, 0, 2, 2}, pos = {1, 1}
bool Rect::Contains(const Vec2& pos) {
    return (pos.x >= x && pos.x < (x+w)) && (pos.y >= y && pos.y < (y+h));
}

Vec2 Rect::GetCenter() {
    return {x + w/2, y + h/2};
}

