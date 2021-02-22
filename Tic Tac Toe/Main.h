#pragma once

#include <iostream>
#include <Windows.h>

#include "ConsoleDrawer.h"
#include "BoardManager.h"

//BOARD:
// (0,0) (1,0) (2,0)
// (0,1) (1,1) (2,1)
// (0,2) (1,2) (2,2)

// 0 1 2
// 3 4 5
// 6 7 8

constexpr int width = 48;
constexpr int height = 24;

constexpr int XSize = 2;
constexpr int OMaxSize = 9;
constexpr int OMinSize = 6;

constexpr int lineCount = 2;

static_assert(width % 3 == 0, "width isn't divisible by 3");
static_assert(height % 3 == 0, "height isn't divisible by 3");

//Used to draw the board
//Checks if point lies on Horizontal line 
bool isXPosOnLine(const int x) {
	for (int i = 1; i <= lineCount; i++) {
		if (x == i * width / (lineCount + 1)) {
			return true;
		}
	}
	return false;
}

//Used to draw the board
//Checks if point lies on vertical line 
bool isYPosOnLine(const int y) {
	for (int i = 1; i <= lineCount; i++) {
		if (y == i * height / (lineCount + 1)) {
			return true;
		}
	}
	return false;
}

//Drawing the board
void DrawBoard() {

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			const char value = '0' + x + (y * 3);
			DrawAtPoint((x + 1) + (width / 3 * x), (y + 1) + (height / 3 * y), value);
		}
	}

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (x == width - 1 || x == 0 || y == height - 1 || y == 0) {
				//Draw # at point
				DrawAtPoint(x, y, "#");
			}
			else if (isYPosOnLine(y)) {
				//Draw horizontal lines at point
				DrawAtPoint(x, y, "-");
			}
			else if (isXPosOnLine(x)) {
				//Draw vertical lines at point
				DrawAtPoint(x, y, "|");
			}
		}
	}
}

//Draws an X on the board
void DrawX(const int square) {
	int x = (square % 3);
	int y = floor(square / 3);

	float xOrigin = (x * width / 3) + (width / 2);
	float yOrigin = (y * height / 3) + (height / 2);
	for (int i = -XSize; i <= XSize; i++) {
		DrawAtPoint(xOrigin + i - width / 3, yOrigin + i - height / 3, "o");
		DrawAtPoint(xOrigin - i - width / 3, yOrigin + i - height / 3, "o");
	}
}

//Used to draw the O
//Gets Distance Between Points w/XY weights
float Distance(float Xa, float Ya, float Xb, float Yb, float xWeight, float yWeight) {
	return 	xWeight * pow((Xb - Xa), 2) + yWeight * pow((Yb - Ya), 2);
}
//Draws an O on the board
void DrawO(const int square) {
	int x = (square % 3);
	int y = floor(square / 3);

	float xOrigin = x + (width / 2 / 3);
	float yOrigin = y + (height / 2 / 3);
	for (int i = 0; i < width / 3; i++) {
		for (int j = 0; j < height / 3; j++) {
			float dis = Distance(i + x, j + y, xOrigin, yOrigin, 0.75f, 2.0f);
			if (OMaxSize >= dis && OMinSize <= dis) {
				DrawAtPoint(i + (x * width / 3), j + (y * height / 3), "o");
			}
		}
	}
}

//Checks if someone has won
bool ScanBoard(const int square, const BoardData data) {
	const int currX = (square % 3);
	const int currY = floor(square / 3);

	for (int i = currX - 1; i <= currX + 1; i++) {
		for (int j = currY - 1; j <= currY + 1; j++) {
			if (contains(i, j, data)) {
				//if selected block is the origin block
				if (i == currX && j == currY) {
					continue;
				}

				//gets the delta movement from origin to new point
				//continues on that line, if the line is complete, X won
				int xDelta = i - currX;
				int yDelta = j - currY;

				if (contains(i + xDelta, j + yDelta, data) || 
					contains(currX - xDelta, currY - yDelta, data)) {

					return true;
				}
			}
		}
	}

	return false;
}