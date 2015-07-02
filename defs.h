#ifndef __defs__
#define __defs__

const int directions[4] = { 1, 5, 4, 6 };

const int convertTo25[9] = {
	6, 7, 8,
	11,12,13,
	16,17,18
};

const int middlePieces[5] = { 7, 11, 13, 17, 12 };

enum sq_color { NAUGHTS, CROSSES, BLANK, BORDER };
enum turn {COM,PLAYER};


#endif 