#ifndef __Board__
#define __Board__

#include "defs.h"
#include <iostream>

class  Board
{
public:
	 Board();
	~ Board();

	bool isBoardFull();
	bool makeMove (const int sq_num ,const sq_color side);
	bool isThreeInARow (const sq_color side);
	void undoMove (const int sq_num);
	void printBoard();
	void resetBoard();
	sq_color getSquareColor(const int sq_num);

private:
	int grid[25];
	int howManyInARow(const int sq_num, sq_color side, const int direction);
	
};

#endif 