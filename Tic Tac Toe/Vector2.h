#pragma once

struct Vector2 {
	Vector2(const int x, const int y)
		: x(x), y(y) {}

	const int ReturnPosAsInt() const {
		return x + (y * 3);
	}

	bool operator== (const Vector2& a) const {
		return a.x == x && a.y == y;
	}
	bool operator!= (const Vector2& a) const {
		return a.x != x || a.y != y;
	}

	int x, y;
};

