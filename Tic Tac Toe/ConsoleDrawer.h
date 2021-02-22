#pragma once

#include <iostream>
#include <windows.h>

void SetCursor(const int x, const int y) {
	COORD point{ x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
void ResetCursor() {
	SetCursor(0, 0);
}
void DrawAtPoint(const int x, const int y, const char* symbol) {
	SetCursor(x, y);
	std::cout << symbol;
}
void DrawAtPoint(const int x, const int y, const char symbol) {
	SetCursor(x, y);
	std::cout << symbol;
}
void ClearAtPoint(const int x, const int y) {
	DrawAtPoint(x, y, " ");
}
void ClearAll() {
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 50; y++) {
			ClearAtPoint(x, y);
		}
	}
}
void ClearAll(const size_t width, const size_t height) {
	for (int x = 0; x < width + 100; x++) {
		for (int y = 0; y < height + 20; y++) {
			ClearAtPoint(x, y);
		}
	}
}
