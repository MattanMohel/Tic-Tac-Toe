#pragma once

enum class BoardData {
	empty,
	X,
	O
};

const char* BoardDataString(const BoardData data) {
	switch (data) {
	case BoardData::empty:
		return "none";
	case BoardData::X:
		return "X";
	case BoardData::O:
		return "O";
	}
}

BoardData boardData[3][3];

//checks if block contains X
bool contains(const int x, const int y, const BoardData data) {
	if (x > 2 || x < 0 || y > 2 || y < 0) {
		return false;
	}
	if (boardData[x][y] == data) {
		return true;
	}
	return false;
} 

//checks if block is empty
bool isEmpty(const int square) {

	int x = (square % 3);
	int y = floor(square / 3);

	if (boardData[x][y] == BoardData::empty) {
		return true;
	}
	return false;
}

void ResetBoard() {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			boardData[x][y] = BoardData::empty;
		}
	}
}



