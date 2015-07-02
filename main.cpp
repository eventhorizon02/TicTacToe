#include <iostream>
#include <vector>
#include "Board.h"
#include "defs.h"
using namespace std;


Board board;
sq_color playerSide;

struct AImove
{
    AImove(){};
    AImove(int myScore)
    {
        score = myScore;
    };
    int move;
    int score;
};

bool isGameOver(const sq_color side);
bool isDraw();
void makeMove(const sq_color side, int num_players);
void makePlayerMove(const sq_color side);
void makeComputerMove(const sq_color side);
sq_color getPlayerSide();
AImove miniMax(const sq_color side);
void gameLoop(int num_players);

int main()
{
	int numPlayer;
	
	bool keepPlaying = true;
	while (keepPlaying)
	{
		cout << "please enter number of players (1, 2 or 0): " << endl;
	    cin >> numPlayer;
		gameLoop(numPlayer);
		cout << "play again? (Y/N) " << endl;
		char ch;
		cin >> ch;
		if ( ! ( (ch == 'y') || (ch == 'Y') ) )
			keepPlaying = false;
	}
    
    
}


void gameLoop(int num_players)
{
    board.resetBoard();
    sq_color side = CROSSES;
    bool gameOver = false;

     if (num_players != 0)
     playerSide = getPlayerSide();
     board.printBoard();
    while (!gameOver)
    {
        makeMove(side,num_players);
        board.printBoard();
        gameOver = isGameOver(side);
        
        side = (sq_color)(side ^ 1); // switch sides by xor ing between 0 and 1
    }
}

// player picks a side

sq_color getPlayerSide()
{
    bool success = false;
    char sideSymbol;
    
    while(!success){
    cout << "would you like to be naughts or crosses (N/C)?" << endl;
    cin >> sideSymbol;
    if (sideSymbol == 'N' || sideSymbol == 'n')
    {
        success = true;
        return  NAUGHTS;
    }else if (sideSymbol == 'C' || sideSymbol == 'c')
    {
        success = true;
        return CROSSES;
    }
    }
    return CROSSES;
}



bool isGameOver(const sq_color side)
{
    if (board.isThreeInARow(side))
    {
        if (side == CROSSES)
            cout << "Game Over!, crosses wins!" << endl;
        else
            cout << "Game Over!, naughts wins!" << endl;
        return true;
    }
    
    return isDraw();
}

bool isDraw()
{
    if (board.isBoardFull())
    {
    cout << "game drawn, thanks for playing" << endl;
        return true;
    }
    
    return false;
}


void makeMove(const sq_color side, int num_players)
{
	if (num_players == 0) // computer plays against itself 
	{
       makeComputerMove(side);

    }else if (num_players == 2) // two humans or human and a dog
    {
     makePlayerMove(side);
    }
     else // in case of one player (human vs computer) alternate between the two.
     {
     	if (playerSide == side)
        makePlayerMove(side);
    else
        makeComputerMove(side);
     }
    
}

void makePlayerMove(const sq_color side)
{
    int sq_num;
    bool success = false;
    
    do
    {
    cout << "square number:" << endl;
    cin >>sq_num;
    
    success = board.makeMove(sq_num, side);
        if (!success)
            cout << "invalid square number, please try again" << endl;
    }while (!success);

}

void makeComputerMove(const sq_color side)
{
    AImove bestMove = miniMax(side);
    board.makeMove(bestMove.move, side);

}

// calculates and returns best move

AImove miniMax(const sq_color side)
{
    // base case
  
   if (board.isThreeInARow(CROSSES))
   	return AImove(10);
   else if (board.isThreeInARow(NAUGHTS))
   	return AImove(-10);
   else if (board.isBoardFull())
   	return AImove(0);

 vector<AImove> moves;

  for (int i = 0; i < 9; ++i)
  {
    if (board.getSquareColor(i) == BLANK)
    {
        AImove move;
        board.makeMove(i + 1,side); // makeMove uses a 1 to 9 value
        move.move = (i + 1);
        move.score = miniMax((sq_color)(side ^ 1)).score;
        moves.push_back(move);
        board.undoMove(i + 1); // restore square to blank
     }
  }

  AImove bestMove;
  if (side == NAUGHTS)
  {
  	int bestScore = 1000000;
    for (int i = 0; i < moves.size(); i++)
    {
        if (moves[i].score < bestScore)
         bestMove = moves[i];
         bestScore = bestMove.score;
    }
   
 }else
  {
     int bestScore = -1000000;
    for (int i = 0; i < moves.size(); i++)
    {
        if (moves[i].score > bestScore)
         bestMove = moves[i];
         bestScore = bestMove.score;
     }
  }

   return bestMove;
}






















