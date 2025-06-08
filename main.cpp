/*
 * Contains just the main function of the program
 * Takes the board size from the user
 * Asks if they will play the game with a friend or by themselves and calls the functions accordingly
 *
 */

#include <iostream>
#include "hexlib.h"

using namespace std;

int main(void){

	int size, player;
	char board[13][13];

	do{

		cout << "What do you want the board size to be? " << endl;
		cin >> size;

		if(size < 6 || size > 12)	cout << "Board size should be between 6 and 12. " << endl;

	}while(size < 6 || size > 12);

	fill_board(board, size);

	do{

		cout << "Is this a two player game or a user vs. computer game?" << endl;
		cout << "Enter 1 for two players and 0 for user vs. computer" << endl;
		cin >> player;

		if(player != 1 && player != 0)	cout << "You should enter 1 or 0" << endl;

	}while(player != 1 && player != 0);

	if(player == 0)			user_vs_computer(board, size);
	else if(player == 1)	user_vs_user(board, size);

}
