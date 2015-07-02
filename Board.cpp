#include "Board.h"
using namespace std;

Board::Board()
{
	resetBoard();
}

Board::~Board()
{

}

bool Board::isBoardFull()
{
	for (int i = 0; i <= 9; i++)
		if (grid[convertTo25[i]] == BLANK)
			return false;
	return true;
}

bool Board::makeMove(const int sq_num, const sq_color side) // uses a 1 to 9 value style
{
	if (sq_num < 1 || sq_num > 9 || grid [convertTo25[sq_num - 1]] != BLANK)
		return false;
	else
		grid[convertTo25[sq_num - 1]] = side;

	return true;
}

void Board::undoMove(const int sq_num)
{
	if ((sq_num >=1 || sq_num <=9) && grid[convertTo25[sq_num -1]] != BLANK)
		grid[convertTo25[sq_num - 1]] = BLANK;
}

bool Board::isThreeInARow(const sq_color side)
{
	for (int i = 0; i < 5; i++) // iterate through middle pieces
	{
		if (grid[middlePieces[i]] == side)
		{
			for (int j = 0; j < 4; ++j)
			{
                int count = howManyInARow(middlePieces[i],side,directions[j]);
				if (count == 3)
                return true;
			}
		}
	}

	return false;
}

void Board::printBoard()
{
	char symbol;
	for (int i = 0; i < 9; ++i)
	{
       int num = grid[convertTo25[i]];
       if (num == NAUGHTS)
       symbol = 'O';
       else if (num == CROSSES)
       	symbol = 'X';
       else
       	symbol = '-';

       cout << symbol;
       if ((i + 1) % 3 == 0)
       	cout << endl;
	}

	cout << endl;
            
 }

 // this method retuens the number of pieces in a row for a given direction (only middle pieces are sent to it)

 int Board::howManyInARow(const int sq_num, const sq_color side, const int direction)
 {
    int count = 1;
 	int nextPiece = grid[sq_num + direction];
 	if ((nextPiece != BORDER) && nextPiece == side)
 		count++;
 	nextPiece = grid[sq_num - direction];
 	if ((nextPiece != BORDER) && nextPiece == side)
 		count++;

    return count;
 }

// this method returs the piece occupying a certain square
 sq_color Board::getSquareColor(const int sq_num)
 {
 	return (sq_color)grid[convertTo25[sq_num]];
 }

// reset the board to starting position

 void Board:: resetBoard()
 {
 	for (int i = 0; i < 25; ++i)
		grid[i] = BORDER;
	for (int i = 0; i < 9; ++i)
		grid[convertTo25[i]] = BLANK;
 }
















