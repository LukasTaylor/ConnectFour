/**
 * Created by Lukas Taylor
 * 11/18/18
 */

#include "game.h"


//constructor initializes player1 and player2 immediately
Game::Game(Player &p1, Player &p2) : player1(p1), player2(p2)
{
	createBoardMatrix();

	//initial state of the game is player1's turn
	this->state = TurnP1;
}

void Game::createBoardMatrix()
{
	//creating a new BoardField array for the height
	boardMatrix = new BoardField*[this->BoardHeight];

	//creates a new Boardfield 2D array
	for (int i = 0; i < this->BoardHeight; i++)
	{
		boardMatrix[i] = new BoardField[BoardWidth];
	}

	//each point in the matrix is set to Empty aka 0
	for (int i = 0; i < this->BoardHeight; i++)
	{
		for (int j = 0; j < this->BoardWidth; j++)
		{
			boardMatrix[i][j] = BoardField::Empty;
		}
	}
}
GameState Game::getState()
{	
	//return current state of the game
	return this->state;
}

BoardField Game::operator() (int x, int y) const
{
	//if x or y are greater than board height or board width return empty. Otherwise return a point in the boardMatrix
	if (x > BoardWidth - 1 || y > BoardHeight - 1)
		return BoardField::Empty;
	else
		return this->boardMatrix[y][x];
}

bool Game::isRunning()
{
	//if getState returns Draw, P1Won, or P2Won than return false otherwise the game is still running so return true
	if (getState() == GameState::Draw || getState() == GameState::P1Won || getState() == GameState::P2Won)
		return false;
	else
		return true;
}

void Game::nextTurn()
{
	int player1ColNum = 0;
	int player2ColNum = 0;

	//call getNextTurn for player1 if it's their turn
	if (this->state == TurnP1)
		//by using *this, the current game is being passed to getNextTurn
		player1ColNum = this->player1.getNextTurn(*this);

	//call getNextTurn for player2 if it's their turn
	if (this->state == TurnP2)
		player2ColNum = this->player2.getNextTurn(*this);

	//Checking for empty spaces on the board by traversing up the columns 
	for (int y = BoardHeight - 1; y >= 0; y--)
	{
			if (this->state == TurnP1)
			{
				//if point on the board is empty set to BoardField::Player1
				if (boardMatrix[y][player1ColNum - 1] == Empty)
				{
					boardMatrix[y][player1ColNum - 1] = Player1;
					break;
				}
			}
			if (this->state == TurnP2)
			{
				//if point on the board is empty set to BoardField::Player2
				if (boardMatrix[y][player2ColNum - 1] == Empty)
				{
					boardMatrix[y][player2ColNum - 1] = Player2;
					break;
				}
			}	
	}
	//switch states aka switching player turns
	if (this->state == TurnP1)
		this->state = TurnP2;
	else
		this->state = TurnP1;
	
	//check for a winner
	checkForWinner();
}

void Game::checkForWinner()
{
	//check horizontal
	{
		for (int y = BoardHeight - 1; y >= 0; y--)
		{
			//check up to index 3 to stay in bounds (checking 4 points each iteration)
			for (int x = 0; x < BoardWidth - 3; x++) 
			{
				if (boardMatrix[y][x] == Player1 &&
					boardMatrix[y][x + 1] == Player1 &&
					boardMatrix[y][x + 2] == Player1 &&
					boardMatrix[y][x + 3] == Player1)
				{
					this->state = P1Won;
				}
				if (boardMatrix[y][x] == Player2 &&
					boardMatrix[y][x + 1] == Player2 &&
					boardMatrix[y][x + 2] == Player2 &&
					boardMatrix[y][x + 3] == Player2)
				{
					this->state = P2Won;
				}
			}
		}
		
	}
	//check vertical
	{
		//check to index 2 to stay in bounds (checking 4 points each iteration)
		for (int y = BoardHeight - 1; y >= 3; y--)
		{
			for (int x = 0; x < BoardWidth; x++)
			{
				
				if (boardMatrix[y][x] == Player1 &&
					boardMatrix[y - 1][x] == Player1 &&
					boardMatrix[y - 2][x] == Player1 &&
					boardMatrix[y - 3][x] == Player1 )
				{
					this->state = P1Won;
				}
				if (boardMatrix[y][x] == Player2 &&
					boardMatrix[y - 1][x] == Player2 &&
					boardMatrix[y - 2][x] == Player2 &&
					boardMatrix[y - 3][x] == Player2 )
				{
					this->state = P2Won;
				}
			}
		}
	}
	//check diagonal
	{
		//check up to y = 2 and x = 3 to stay in bounds
		for (int y = BoardHeight - 1; y >= 3; y--)
		{
			for (int x = 0; x < BoardWidth - 3; x++)
			{
				//positive diagonal (/)
				if ((boardMatrix[y][x] == Player1 &&
					boardMatrix[y - 1][x + 1] == Player1 &&
					boardMatrix[y - 2][x + 2] == Player1 &&
					boardMatrix[y - 3][x + 3] == Player1) 
					||
					//negative diagonal (\)
					(boardMatrix[y][x + 3] == Player1 &&
						boardMatrix[y - 1][x + 2] == Player1 &&
						boardMatrix[y - 2][x + 1] == Player1 &&
						boardMatrix[y - 3][x] == Player1))
				{
					this->state = P1Won;
				}
				//positive diagonal (/)
				if ((boardMatrix[y][x] == Player2 &&
					boardMatrix[y - 1][x + 1] == Player2 &&
					boardMatrix[y - 2][x + 2] == Player2 &&
					boardMatrix[y - 3][x + 3] == Player2) 
					||
					//negative diagonal (\)
					(boardMatrix[y][x + 3] == Player2 &&
						boardMatrix[y - 1][x + 2] == Player2 &&
						boardMatrix[y - 2][x + 1] == Player2 &&
						boardMatrix[y - 3][x] == Player2))
				{
					this->state = P2Won;
				}
			}
		}
	}
}