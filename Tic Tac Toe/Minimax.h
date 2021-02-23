#pragma once

#include <vector>
#include <random>

#include "Main.h"
#include "Branch.h"
#include "Vector2.h"
#include "BoardManager.h"

#define MAX 9999
#define POINT 10

#define SHOW_PROCESS false

//the amount of steps the AI will look ahead 
constexpr size_t MAX_DEPTH = MAX;

//O tries to maximize, X tries to minimize, returns the depth's optimalScore
Branch MINIMAX(const int depth, std::vector<Vector2>& spaces) {
	//which non-predicate move are you on
	static size_t currentMoveIndex = 0;
	//resets static members
	if (depth == 0) {
		currentMoveIndex = 0;
	}

	//if depth is even O, if odd then X
	BoardData data = depth % 2 == 0 ? BoardData::O : BoardData::X;
	//set startingScore to -infinity if O, infinity if X
	Branch optimalBranch(data == BoardData::X ? MAX : -MAX);

	//sets off recursive for loop
	for (int move = 0; move < spaces.size(); move++) {
		bool SKIP_ITERATION_RECURSION = false;

		//if the space is already in use -> skip
		if (!isEmpty(spaces[move].ReturnPosAsInt())) {
			continue;
		}

		//adds current location to used vector
		boardData[spaces[move].x][spaces[move].y] = data;

#if SHOW_PROCESS
		switch (data) {
		case BoardData::X:
			DrawX(spaces[move].ReturnPosAsInt());
			break;
		case BoardData::O:
			DrawO(spaces[move].ReturnPosAsInt());
			break;
		}
#endif
		
		//check for victory - ends current branch, otherwise neutral
		if (ScanBoard(spaces[move].ReturnPosAsInt(), data)) {
			switch (data) {
			case BoardData::O:
				//increase score, O wants to maximize	
				if (POINT - depth > optimalBranch.GetScore()) {
					optimalBranch.SetBranch(spaces[currentMoveIndex], POINT - depth);
				}

				break;
			case BoardData::X:
				//decrease score, X wants to minimize
				if (-POINT + depth < optimalBranch.GetScore()) {
					optimalBranch.SetBranch(spaces[currentMoveIndex], -POINT + depth);
				}

				break;
			}

			SKIP_ITERATION_RECURSION = true;
		}
		//if no one won ->at the very bottom with no plays left or at MAX
		else if (depth == MAX_DEPTH || (size_t)depth + 1 == spaces.size()) {

			switch (data) {
			case BoardData::O:
				if (0 > optimalBranch.GetScore()) {
					optimalBranch.SetBranch(spaces[currentMoveIndex], 0);
				}
			case BoardData::X:
				if (0 < optimalBranch.GetScore()) {
					optimalBranch.SetBranch(spaces[currentMoveIndex], 0);
				}
			}

			SKIP_ITERATION_RECURSION = true;
		}

		//if you can neither win, lose, or tie this step, don't skip recursion
		if (!SKIP_ITERATION_RECURSION) {
			
			//recursive call with depth incremented
			Branch minimaxScore = MINIMAX(depth + 1, spaces);
			
			switch (data) {
			case BoardData::O:
				if (minimaxScore.GetScore() > optimalBranch.GetScore() || !optimalBranch.isSet()) {
					optimalBranch.SetBranch(spaces[currentMoveIndex], minimaxScore.GetScore());
				}

				break;
			case BoardData::X:
				if (minimaxScore.GetScore() < optimalBranch.GetScore() || !optimalBranch.isSet()) {
					optimalBranch.SetBranch(spaces[currentMoveIndex], minimaxScore.GetScore());
				}

				break;
			}
		}

		boardData[spaces[move].x][spaces[move].y] = BoardData::empty;

#if SHOW_PROCESS
		switch (data) {
		case BoardData::X:
			ClearX(spaces[move].ReturnPosAsInt());
			break;
		case BoardData::O:
			ClearO(spaces[move].ReturnPosAsInt());
			break;
		}
#endif

		//if on a non-predicate move, increment
		if (depth == 0) {
			currentMoveIndex++;
		}

	}
	
	//returns up the score but also the placement
	//placement overrides the above placement???
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