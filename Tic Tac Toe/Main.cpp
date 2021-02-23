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
		bool playerTurn = true;
		int m_Input;
		DrawBoard();

		//main game loop
		while (!gameEnded) {
			//player input loop
			while (true) {
				if (playerTurn)
				{
					//recieve input
					m_Input = _getch() - '0';

					//TODO: needs some cleanup/refactoring
					if (m_Input <= 8 && m_Input >= 0 && isEmpty(m_Input)) {
						inputIndex++;

						DrawX(m_Input);

						int x = (m_Input % 3);
						int y = floor(m_Input / 3);
						boardData[x][y] = BoardData::X;

						if (ScanBoard(m_Input, BoardData::X)) {
							gameEnded = true;
							winner = BoardData::X;
						}

						playerTurn = false;
						break;
					}
				}
				else {
					inputIndex++;

					m_Input = GetNextMove();

					DrawO(m_Input);

					int x = (m_Input % 3);
					int y = floor(m_Input / 3);
					boardData[x][y] = BoardData::O;

					if (ScanBoard(m_Input, BoardData::O)) {
						gameEnded = true;
						winner = BoardData::O;
					}

					playerTurn = true;
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

		SetCursor(width + 5, 3);
		std::cout << "  Press 'R' to replay, 'E' to quit  ";

		char input = ' ';
		while (input != 'r' && input != 'e') {
			input = _getch();
		}

		switch (input) {
		case 'r':
			ResetBoard();
			ClearAll();
			break;
		default:
			ClearAll();
			return 1;
		}
	}
}