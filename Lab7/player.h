/**
 * Created by Lukas Taylor
 * 11/18/18
 */

#ifndef LAB7_PLAYERS_H
#define LAB7_PLAYERS_H

#include "game.h"
class Game; //tells compiler "hey there's a game object in this class that'll be defined later"

class Player {

public:
	//set to 0 to make the function pure virtual
	virtual int getNextTurn(const Game& currentGame) = 0;
};

//HumanPlayer class that inherits public player function getNextTurn
class HumanPlayer : public Player
{
public:
	int getNextTurn(const Game& currentGame);
};

//AiPlayer class inherits public player function getNextTurn
class AiPlayer : public Player
{
public:
	int getNextTurn(const Game& currentGame);
};

#endif //LAB7_PLAYERS_H

