#pragma once

#include <vector>
#include <random>

#include "Main.h"
#include "Vector2.h"
#include "BoardManager.h"

#define MAX 99;

struct Branch {
public:
	static float multiplier;

	void SetVector2(const Vector2& a) {
		position = a;
	}

	const Vector2& GetVector2() const {
		return position;
	}

	void IncreaseScore(const unsigned int a) {
		score += a;
	}

	void DecreaseScore(const unsigned int a) {
		score -= a;
	}

	void IncrementBranches() {
		branches++;
	}
	void IncreaseBranches(const unsigned int a) {
		branches += a;
	}

	const double GetScore() const {
		return score / (double)branches;
	}

private:
	int score = 0;
	int branches = 0;

	Vector2 position = Vector2(0, 0);
};

int GetBestPath(const std::vector<Branch> branches) {
	size_t rIndex = 0;
	for (int i = 1; i < branches.size(); i++) {

		rIndex = branches[i].GetScore() > branches[rIndex].GetScore() ? i : rIndex;
		
		//if values are equal, randmoize what it choses
		if (branches[i].GetScore() == branches[rIndex].GetScore()) {
			rIndex = rand() % 10 > 5 ? i : rIndex;
		}
	}

	//returns the branch's position on the board
	return branches[rIndex].GetVector2().ReturnPosAsInt();
}

int factorial(const int max) {
	int value = 1;
	for (int i = 2; i < max; i++) {
		value *= i;
	}
	return value;
}

//HEADERS
bool ScanBoard(const int square, const BoardData data);

//the amount of steps the AI will look ahead 
constexpr size_t MAX_DEPTH = MAX;

void MINIMAX(const int depth, std::vector<Vector2>& spaces, std::vector<Branch>& branches) {
	//which non-predicate move are you on
	static size_t currentMove = 0;

	//if depth is even O, if odd then X
	BoardData data = depth % 2 == 0 ? BoardData::O : BoardData::X;

	//resets static/global members and dependencies
	if (depth == 0) {
		currentMove = 0;
	}

	//sets off recursive for loop
	for (int move = 0; move < spaces.size(); move++) {
		bool CONTINUE = false;
		//if the move is already in use
		if (!isEmpty(spaces[move].ReturnPosAsInt())) {
			continue;
		}
		//if on non-predicate then set it as branch pos
		if (depth == 0) {
			branches[currentMove].SetVector2(spaces[move]);
		}
		//adds current location to used vector
		boardData[spaces[move].x][spaces[move].y] = data;
		
		//check for victory
		if (ScanBoard(spaces[move].ReturnPosAsInt(), data)) {
			//the factorial value of winning in respect to depth
			int value = factorial(spaces.size() - depth);
			branches[currentMove].IncreaseBranches(value);

			switch (data) {
			case BoardData::O:
				//increase score
				branches[currentMove].IncreaseScore(value);
				break;
			case BoardData::X:
				//decrease score
				branches[currentMove].DecreaseScore(value);
				break;
			}

			CONTINUE = true;
		}
		//if a neutral round or at MAX_DEPTH
		else if (depth == MAX_DEPTH || depth + 1 == spaces.size()) {
			//score remains neutral
			branches[currentMove].IncrementBranches();
		}

		//proceed with recursion only if depth is less than MAX
		if (depth < MAX_DEPTH && !CONTINUE) {
			//recursive call with depthcount incremented
			MINIMAX(depth + 1, spaces, branches);
		}

		boardData[spaces[move].x][spaces[move].y] = BoardData::empty;

		//if on a non-predicate move, increment
		if (depth == 0) {
			currentMove++;
		}
	}
}

int GetNextMove() {
    std::vector<Vector2> spaces;
	std::vector<Branch> branches;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			//adds square to vector if empty
			if (isEmpty(x + (3 * y))) {
				spaces.push_back(Vector2(x, y));
				branches.push_back(Branch());
			}
		}
	}

	MINIMAX(0, spaces, branches);
	return GetBestPath(branches);
}