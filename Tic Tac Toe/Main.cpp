#include <iostream>
#include <conio.h>
#include <vector>

#include "Main.h"
#include "Minimax.h"

int main() {

	while (true)
	{
		BoardData winner = BoardData::empty;
		unsigned int inputIndex = 0;
		bool gameEnded = false;
		bool playerTurn;

		ResetCursor(); 
		std::cout << "  Press 'M' to play first, 'O' to play second  ";

		while (true)
		{
			char input = _getch();

			if (input == 'o') {
				playerTurn = false;
				break;
			}
			else if (input == 'm') {
				playerTurn = true;
				break;
			}
		}

		DrawBoard();

		//main game loop
		while (!gameEnded) {

			//player input loop
			int inputValue;

			while (true) {
				if (playerTurn)
				{
					//recieve input
					inputValue = _getch() - '0';

					//TODO: needs some cleanup/refactoring
					if (inputValue <= 8 && inputValue >= 0 && isEmpty(inputValue)) {
						inputIndex++;

						DrawX(inputValue);

						int x = (inputValue % 3);
						int y = floor(inputValue / 3);
						boardData[x][y] = BoardData::X;

						if (ScanBoard(inputValue, BoardData::X)) {
							gameEnded = true;
							winner = BoardData::X;
						}

						playerTurn = !playerTurn;
						break;
					}
				}
				else {
					inputIndex++;

					inputValue = GetNextMove();

					DrawO(inputValue);

					int x = (inputValue % 3);
					int y = floor(inputValue / 3);
					boardData[x][y] = BoardData::O;

					if (ScanBoard(inputValue, BoardData::O)) {
						gameEnded = true;
						winner = BoardData::O;
					}

					playerTurn = !playerTurn;
					break;
				}

			}

			if (gameEnded || inputIndex >= 9) {
				SetCursor(width + 5, 0);
				switch (winner) {
				case BoardData::X:
					std::cout << " X WON! ";
					break;
				case BoardData::O:
					std::cout << " O WON! ";
					break;
				default:
					std::cout << "  TIE!  ";
					gameEnded = true;
					break;
				}
			}
		}

		ResetCursor();
		std::cout << "     Press 'R' to replay, 'E' to quit           ";

		while (true) {
			char input = _getch();

			if (input == 'r') {
				
				gameEnded = false;

				ResetBoard();
				ClearAll();
				break;
			}

			if (input == 'e') {
				ClearAll();
				return 1;
			}
		}
	}
}