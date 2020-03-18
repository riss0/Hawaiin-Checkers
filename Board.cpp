

#include <iostream>

using namespace std;

#include "Board.h"

Board::Board()
{
}


//Fill the board with alternating characters
Board::Board(unsigned rows, unsigned cols)
{
	for (decltype(rows) r = 1; r <= rows; r++) {
		for (decltype(cols) c = 1; c <= cols; c++) {
			if ((r + c) % 2)
				boardArray[r][c] = 'B';
			else boardArray[r][c] = 'W';
		}
	}
	populateVectors();
}




void Board::populateVectors() {
	Position p;
	
		p.row = 1; p.col = 1;
		boardCorners.push_back(p);
		p.row = 1; p.col = boardCols;
		boardCorners.push_back(p);
		p.row = boardRows; p.col = 1;
		boardCorners.push_back(p);
		p.row = boardRows; p.col = boardCols;
		boardCorners.push_back(p);

		p.row = 1; p.col = 2;
		boardAdjCorners.push_back(p);
		p.row = 1; p.col = boardCols - 1;
		boardAdjCorners.push_back(p);
		p.row = boardRows - 1; p.col = 1;
		boardAdjCorners.push_back(p);
		p.row = boardRows - 1; p.col = boardCols;
		boardAdjCorners.push_back(p);
		p.row = 2; p.col = 1;
		boardAdjCorners.push_back(p);
		p.row = 2; p.col = boardCols;
		boardAdjCorners.push_back(p);
		p.row = boardRows; p.col = 2;
		boardAdjCorners.push_back(p);
		p.row = boardRows; p.col = boardCols - 1;
		boardAdjCorners.push_back(p);

		if (((boardRows % 2) == 1) && ((boardCols % 2) == 1)) {
			p.row = (1 + boardRows) / 2; p.col = (1 + boardCols) / 2;
			boardCenters.push_back(p);
		}
		else if ((boardRows % 2) == 1) {
			p.row = (1 + boardRows) / 2; p.col = (1 + boardCols) / 2;
			boardCenters.push_back(p);
			p.col += 1;
			boardCenters.push_back(p);
		}
		else if ((boardCols % 2) == 1) {
			p.row = (1 + boardRows) / 2; p.col = (1 + boardCols) / 2;
			boardCenters.push_back(p);
			p.row += 1;
			boardCenters.push_back(p);
		}
		else {
			p.row = (1 + boardRows) / 2; p.col = (1 + boardCols) / 2;
			boardCenters.push_back(p);
			p.row += 1;
			boardCenters.push_back(p);
			p.row = (1 + boardRows) / 2; p.col += 1;
			boardCenters.push_back(p);
			p.row += 1;
			boardCenters.push_back(p);
		}
	
}


unsigned Board::getBlanks() const {
	return blanks;
}


/* Print the current board to an output stream
 * Mark the most recent move by an underscore for
 * the start position and capitalize the end position
 */
void Board::displayBoard(ostream& out) const
{
	Move lastMove;
	Position lastFrom, lastTo;
	char lastPiece;
	int num = 1;

	if (moveHistory.size() > 0) {
		lastMove = moveHistory[moveHistory.size() - 1];
		lastFrom = lastMove.from;
		lastTo = lastMove.to;
		lastPiece = boardArray[lastTo.row][lastTo.col];
	}
	else {
		lastFrom.row = 0; lastFrom.col = 0; lastTo.row = 0; lastTo.col = 0;
	}

	for (decltype(boardCols) c = 1; c <= boardCols; c++) {
		if (c < 10) { out << ""; }
		else { out << (c / 10); }
	}
	cout << endl << "     ";;
	
	for (decltype(boardCols) c = 1; c <= boardCols; c++) {
		cout << (num++);
	}
	out << endl<<endl;
	for (decltype(boardRows) r = boardRows; r >= 1; r--) {
		cout<<" "<<r<< "   ";
		for (decltype(boardCols) c = 1; c <= boardCols; c++) {
			if ((r == lastFrom.row) && (c == lastFrom.col)) {
				out << " ";
			}
			else if ((r == lastTo.row) && (c == lastTo.col)) {
				if (lastPiece == 'B') {
					out << 'B';
				}
				else {
					out << 'W';
				}
			}
			else {
				out << boardArray[r][c];
			}
		}
		out << endl;
	}
	
}

void Board::setRows(int rows)
{
	boardRows = rows;
}

void Board::setCols(int cols)
{
	boardCols = cols;
}

void Board::gamePiece(int r, int c, char piece)
{
	boardArray[r][c] = piece;
}

void Board::setFirstMove(Position p)
{
	firstMove.row = p.row;
	firstMove.col = p.col;
	boardArray[p.row][p.col] = ' ';
}

void Board::setSecondMove(Position p)
{
	secondMove.row = p.row;
	secondMove.col = p.col;
	boardArray[p.row][p.col] = ' ';
}

/* Make a move.  The move must have been previously
 * checked for legality.  Moves can be horizontal
 * or vertical, in a positive or negative direction,
 * but not on a diagonal.
 */
void Board::makeMove(Move m)
{
	int r, c, direction;
	char piece;
	Position p1, p2;

	p1 = m.from;
	p2 = m.to;
	
	piece = boardArray[p1.row][p1.col];
	boardArray[p1.row][p1.col] = ' ';
	boardArray[p2.row][p2.col] = piece;
	r = p1.row;
	c = p1.col;
	if (p1.row == p2.row) {
		if (p2.col > p1.col) { direction = 1; }
		else { direction = -1; }

		while (c != p2.col) {
			boardArray[p1.row][c + direction] = ' ';
			c += (2 * direction);
		}
	}
	else {
		if (p2.row > p1.row) { direction = 1; }
		else { direction = -1; }
	
		while (r != p2.row) {
			boardArray[r + direction][p1.col] = ' ';
			r += (2 * direction);
		}
	}
}

int Board::getRows() const
{
	return boardRows;
}

int Board::getCols() const
{
	return boardCols;
}

char Board::getPiece(Position p) const
{
	return boardArray[p.row][p.col];
}

void Board::getFirstMove(Position& p) const
{
	p.row = firstMove.row;
	p.col = firstMove.col;
}

bool Board::isCorner(Position p)
{
	vector< Position >::iterator location;

	for (location = boardCorners.begin(); location != boardCorners.end(); ++location) {
		if ((location->row == p.row) && (location->col == p.col)) { return true; };
	}
	return false;
}

bool Board::isNextToCorner(Position p)
{
	vector< Position >::iterator location;

	for (location = boardAdjCorners.begin(); location != boardAdjCorners.end(); ++location) {
		if ((location->row == p.row) && (location->col == p.col)) { return true; };
	}
	return false;
}

bool Board::isCenter(Position p)
{
	vector< Position >::iterator location;

	for (location = boardCenters.begin(); location != boardCenters.end(); ++location) {
		if ((location->row == p.row) && (location->col == p.col)) { return true; };
	}
	return false;
}

