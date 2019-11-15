/**
 * Created by Lukas Taylor
 * 11/18/18
 */

#ifndef LAB7_GAME_H
#define LAB7_GAME_H
#include "player.h"
class Player;   //tells compiler "hey there's a player object in this class that'll be defined later"

enum BoardField { Empty, Player1, Player2 };
enum GameState { TurnP1, TurnP2, P1Won, P2Won, Draw };

class Game {
public:
	const int BoardWidth = 7;
	const int BoardHeight = 6;

	//constructor that takes two players as parameters
	Game(Player &p1, Player &p2);

	/**
	 * returns the current state of a game
	 * @return
	 */
	GameState getState();

	/**
	 * overides the () operator
	 * Returns the state of the board at a the given coordinate.
	 * The top left element has coordinate (0,0)
	 * Returns Empty if the coordinate is out of range of the board.
	 * @param x
	 * @param y
	 * @return
	 */
	BoardField operator() (int x, int y) const;

	/**
	 * returns true if the game is still running
	 * or false if the game finished with a player win or a draw
	 * @return
	 */
	bool isRunning();

	/**
	 * performs the next turn by the Game class calling the getNextTurn of the current player.
	 * If the return value is valid nothing happens.
	 * Otherwise the function should process the move of the player.
	 * 
	 */
	void nextTurn();
	/**
	 * creates a board of 6 x 7
	 */
	void createBoardMatrix();
	/**
	 * function to check if a player has won
	 */
	void checkForWinner();
private:
	//reserving the memory locations for a Boardfield matrix
	BoardField** boardMatrix = nullptr;
	//holds the state of a game
	GameState state;

	//used to hold players data for current game
	Player &player1;
	Player &player2;
};

#endif //LAB7_GAME_H

