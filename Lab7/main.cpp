#include <iostream>

#include "player.h"
#include "game.h"

using namespace std;

/**
 * returns a pointer to a player
 * @return
 */
Player* getPlayer()
{
	static int playerNumber = 1;

	int input;
	//loop will continue until user inputs a 1 and a 2
	for (input = 0; input != 1 && input != 2;)
	{
		cout << "Select Player " << playerNumber << " (human: 1, ai: 2) ";
		cin >> input;
	}
	//increments player number from 1 to 2
	playerNumber++;
	//creates a new HumanPlayer if input == 1
	if (input == 1)
	{
		return new HumanPlayer;
	}
	//creates a new AiPlayer if input == 2
	else // input == 2
	{
		return new AiPlayer;
	}

}

void PrintBoard(const Game &game)
{
	cout << endl;

	for (int y = 0; y < game.BoardHeight; y++)
	{
		cout << "  | ";
		for (int x = 0; x < game.BoardWidth; x++)
		{
			char boardChar;
			switch (game(x, y))
			{
			case BoardField::Empty:
				boardChar = ' ';
				break;
			case BoardField::Player1:
				boardChar = 'O';
				break;
			case BoardField::Player2:
				boardChar = 'X';
				break;
			}
			cout << boardChar << ' ';
		}
		cout << "|\n";
	}

	cout << "  ---";
	for (int x = 0; x < game.BoardWidth; x++)
	{
		cout << "--";
	}
	cout << endl;

	cout << "   ";
	for (int x = 0; x < game.BoardWidth; x++)
	{
		cout << " " << x + 1;
	}
	cout << endl << endl;

}

int main()
{
	cout << "* * * * * * * * * * * * *\n";
	cout << "  Welcome to Connect 4!\n\n";

	Player* player1 = getPlayer();
	Player* player2 = getPlayer();

	Game game(*player1, *player2);

	while (game.isRunning())
	{
		PrintBoard(game);

		int curPlayer;

		switch (game.getState())
		{
		case GameState::TurnP1:
			curPlayer = 1;
			break;
		case GameState::TurnP2:
			curPlayer = 2;
			break;
		}

		cout << "Turn for Player " << curPlayer << ": ";

		game.nextTurn();
	}

	PrintBoard(game);

	switch (game.getState())
	{
	case GameState::P1Won:
		cout << "Player 1 won the game!";
		break;
	case GameState::P2Won:
		cout << "Player 2 won the game!";
		break;
	case GameState::Draw:
		cout << "Draw, no winner.";
		break;
	}

	cout << endl;

	delete player1;
	delete player2;

	system("pause");

	return 0;
}
