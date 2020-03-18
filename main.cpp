

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
#include "Board.h"
#include "Player.h"

int main() {
	int rows = 8;
	int columns = 8;
	char player1, player2;
	char gamePiece_1 = 'B';
	char gamePiece_2 = 'W';
	bool gameEnded;
	char* EmptyBoard = NULL;
	int depth = 4;
	Board gameBoard(rows, columns);

			cout << "Is Player 1 Human(h) or AI(a)? ";
			cin >> player1;

			cout << "B or W for Player1? ";
			cin >> gamePiece_1;

			cout << "Is player 2 Human(h) or AI(a)? ";
			cin >> player2;
			
			if (gamePiece_1 == 'B') { gamePiece_2 = 'W'; }
			else { gamePiece_2 = 'B'; }
			

	

	if (EmptyBoard == NULL) {
		Player player1(player1, gamePiece_1, depth);
		Player player2(player2, gamePiece_2, depth);
		player1.firstMove(gameBoard);
		gameBoard.displayBoard(cout); 
		gameEnded = player2.secondMove(gameBoard);
		gameBoard.displayBoard(cout); 
		while (!gameEnded) {
			gameEnded = player1.nextMove(gameBoard);
			if (gameEnded) {
				cout << "Player1 loses, Player 2 wins." << endl;
			}
			gameBoard.displayBoard(cout); 
			if (!gameEnded) {
				gameEnded = player2.nextMove(gameBoard);
				if (gameEnded) {
					cout << "Player 2 loses, Player 1 wins." << endl;
				}
				 gameBoard.displayBoard(cout);
			}
		}
	}
	/*	else {
		Board board(rows, cols, EmptyBoard);
		Player player(player1, gamePiece_1, depth1);
		if (board.getBlanks() == 0) {
			player.firstMove(board, true);
		}
		else if (board.getBlanks() == 1) {
			player.secondMove(board, true);
		}
		else {
			player.nextMove(board, true);
		}
	}*/

	return 0;
}
