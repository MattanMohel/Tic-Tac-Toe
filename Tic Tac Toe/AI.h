#pragma once

#include <vector>
#include <random>

#include "Main.h"
#include "Vector2.h"
#include "BoardManager.h"

#define MAX 99
#define POINT 10

struct Branch {
public:
	//setters
	void SetBranch(Vector2 vector2, int score) {
		m_Pos = vector2;
		m_Score = score;
	}

	//getters
	const int GetScore() const {
		return m_Score;
	}
	const Vector2 GetPosition() const {
		return m_Pos;
	}

private:
	int m_Score = 0;
	Vector2 m_Pos = Vector2(0, 0);
};

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

//O tries to maximize, X tries to minimize, returns the depth's optimalScore
Branch MINIMAX(const int depth, std::vector<Vector2>& spaces) {
	//which non-predicate move are you on
	static size_t currentMove = 0;
	//resets static members
	if (depth == 0) {
		currentMove = 0;
	}

	Branch optimalBranch;
	//if depth is even O, if odd then X
	BoardData data = depth % 2 == 0 ? BoardData::O : BoardData::X;



	//sets off recursive for loop
	for (int move = 0; move < spaces.size(); move++) {
		bool CONTINUE = false;
		//if the move is already in use
		if (!isEmpty(spaces[move].ReturnPosAsInt())) {
			continue;
		}

		//adds current location to used vector
		boardData[spaces[move].x][spaces[move].y] = data;
		switch (data) {
		case BoardData::X:
			DrawX(spaces[move].ReturnPosAsInt());
			break;
		case BoardData::O:
			DrawO(spaces[move].ReturnPosAsInt());
			break;
		}
		
		//check for victory - ends current branch, otherwise neutral
		if (ScanBoard(spaces[move].ReturnPosAsInt(), data)) {
			switch (data) {
			case BoardData::O:
				//increase score, O wants to maximize	
				if (POINT - depth >= optimalBranch.GetScore()) {
					optimalBranch.SetBranch(spaces[move], POINT - depth);
				}

				break;
			case BoardData::X:
				//decrease score, X wants to minimize
				if (-POINT + depth <= optimalBranch.GetScore()) {
					optimalBranch.SetBranch(spaces[move], -POINT + depth);
				}

				break;
			}

			CONTINUE = true;
		}
		//ELSE - if no one/end and so branch has to be set
		else if (depth == MAX_DEPTH || (size_t)depth + 1 == spaces.size()) {
			optimalBranch.SetBranch(spaces[move], 0);
		}

		//proceed with recursion only if depth is less than MAX
		if (depth < MAX_DEPTH && !CONTINUE) {
			//recursive call with depthcount incremented
			Branch minimaxScore = MINIMAX(depth + 1, spaces);
			
			switch (data) {
			case BoardData::O:
				if (minimaxScore.GetScore() >= optimalBranch.GetScore()) {
					optimalBranch.SetBranch(minimaxScore.GetPosition(), minimaxScore.GetScore());
				}

				break;
			case BoardData::X:
				if (minimaxScore.GetScore() <= optimalBranch.GetScore()) {
					optimalBranch.SetBranch(minimaxScore.GetPosition(), minimaxScore.GetScore());
				}

				break;
			}
		}

		boardData[spaces[move].x][spaces[move].y] = BoardData::empty;
		switch (data) {
		case BoardData::X:
			ClearX(spaces[move].ReturnPosAsInt());
			break;
		case BoardData::O:
			ClearO(spaces[move].ReturnPosAsInt());
			break;
		}

		//if on a non-predicate move, increment
		if (depth == 0) {
			currentMove++;
		}

	}
	
	return optimalBranch;
}

int GetNextMove() {
    std::vector<Vector2> spaces;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			//adds square to vector if empty
			if (isEmpty(x + (3 * y))) {
				spaces.push_back(Vector2(x, y));
			}
		}
	}

	return 	MINIMAX(0, spaces).GetPosition().ReturnPosAsInt();
}