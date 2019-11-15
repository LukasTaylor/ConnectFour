/**
 * Created by Lukas Taylor
 * 11/18/18
 */

#include <iostream> //cin
#include <stdlib.h> //rand
#include <time.h>   //time
#include "player.h"

using namespace std;


/**
 *	Returns a number from 0 - 7
 * @param currentGame
 * @return
 */
int HumanPlayer::getNextTurn(const Game& currentGame)
{
	int columnNum = 0;

	//receives HumanPlayers column number
	cin >> columnNum;

	return columnNum;
}

/**
 * Returns a number from 1 - 7 randomly
 * @param currentGame
 * @return
 */
int AiPlayer::getNextTurn(const Game& currentGame)
{
	srand(time(NULL));
	//generates a random number between 1 and 7
	int columnNum = rand() % 7 + 1;
	cout << columnNum << endl;
	return columnNum;
}