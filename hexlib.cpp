#include <iostream>
#include "hexlib.h"

/*
 Contains the definitions of the functions
 */

using namespace std;

void fill_board(char board[][13], int size){

	for(int i = 0; i < 14; i++){

		for(int j = 0; j < 14; j++){

			if(i <= size && j <= size){

				if(i == 0 && j == 1)		board[i][j] = 'a';	//Specifies the cells' locations vertically
				else if(i == 1 && j == 0)	board[i][j] = '1';	//Specifies the cells' locations horizontally
				else if(i == 0 && j > 1) 	board[0][j] = board[0][j-1] + 1;
				else if(j == 0 && i > 1)	board[i][0] = board[i-1][0] + 1;
				else						board[i][j] = '.';	//Fills the parts of the board where the game will take place with '.'

			}else	board[i][j] = ' ';	//Fills the parts of the board that are out of the borders with ' '

	    }

	}

	board[0][0] = ' ';

}

void print_board(char board[][13], int size){

	for(int i = 0; i < size + 1; i++){

		if(i > 9)			cout << i;
		else				cout << board[i][0];

		for(int k = 0; k < i; k++)	cout << " "; /* To make the board appear a diamond shape, there are blank spaces left before every row,
													equal to the row number*/
		for(int j = 1; j < size + 1; j++){

			cout << board[i][j] << " ";

	    }

		cout << endl;

	}

}

int x_win(char board[][13], char check[][13], int size){ //Finds an x where letter is 'a', checks every possible way it can go to

	int num = 1, letter = 1;

	while(letter != size){

		if(num != size && board[num][letter] != 'x')	++num;
		else if(board[++num][--letter] == 'x'){

			check[num][letter] = 'x';		// If it finds an x on the way, it adds the location to the check array as 'x'
			++num;
			--letter;

		}else if(board[++num][letter] == 'x'){

			check[num][letter] = 'x';
			++num;

		}else if(board[num][++letter] == 'x'){

			check[num][letter] = 'x';
			++letter;

		}else if(board[num][--letter] == 'x'){

			check[num][letter] = 'x';
			--letter;

		}else if(board[--num][letter] == 'x'){

			check[num][letter] = 'x';
			--num;

		}else if(board[--num][++letter] == 'x'){

			check[num][letter] = 'x';
			--num;
			++letter;

		}else if(letter != size)	return 0;
		else{

			check[num][letter] = '*'; 	//If the way doesn't go to the very right, it marks the way back as '*'

		}

	}

	for(int i=1; i<=size; i++){

		for(int j=1; j<=size; j++){

			if(board[i][j] == check[i][j])	board[i][j] = 'X'; // The locations of the connected path is turned to 'X' on the original array

		}

	}

	return 1;

}

int o_win(char board[][13], char check[][13], int size){

	int num = 1, letter = 1;

	while(num != size){

		if(letter != size && board[num][letter] != 'o')	++letter;
		else if(board[++num][--letter] == 'o'){

			check[num][letter] = 'o';
			++num;
			--letter;

		}else if(board[++num][letter] == 'o'){

			check[num][letter] = 'o';
			++num;

		}else if(board[num][++letter] == 'o'){

			check[num][letter] = 'o';
			++letter;

		}else if(board[num][--letter] == 'o'){

			check[num][letter] = 'o';
			--letter;

		}else if(board[--num][letter] == 'o'){

			check[num][letter] = 'o';
			--num;

		}else if(board[--num][++letter] == 'o'){

			check[num][letter] = 'o';
			--num;
			++letter;

		}else if(num != size)	return 0;
		else{

			check[num][letter] = '*';

		}

	}

	for(int i=1; i<=size; i++){

		for(int j=1; j<=size; j++){

			if(board[i][j] == check[i][j])	board[i][j] = 'O';

		}

	}

	return 1;

}

void add_move(char board[][13], int size, int player, char letter, int num){ //Adds the given move to the board

	if(player == 1)		board[num][letter - 64] = 'x'; 	// When the capital letters' ascii code is decremented by 64,
	else				board[num][letter - 64] = 'o';	// it gives us the row number of that letter

}

void user_vs_user(char board[][13], int size){

	char letter;
	int num;

	char check[13][13]; //Check will be a replica of the empty board, it will be used to check if a player won the game
	for(int i=0; i<13; i++){
		for(int j=0; j<13; j++)	check[i][j] = '*';
	}

	while(x_win(board, check, size) == 0 && o_win(board, check, size) == 0){ //The game will go on until a player wins the game since
																				//there can be no ties in the hex game
		print_board(board, size);

		do{

			cout << "Player 1: ";
			cin >> letter >> num;

			if(board[num][letter - 64] != '.' || letter > 'L')	cout << "Invalid move. Enter another move. " << endl;

		}while(board[num][letter - 64] != '.' || letter > 'L');

		add_move(board, size, 1, letter, num);

		if(x_win(board, check, size) == 1)		cout << endl << "Congratulations Player 1, you won!" << endl;
		else{

			print_board(board, size);

			do{

				cout << "Player 2: ";
				cin >> letter >> num;

				if(board[num][letter - 64] != '.' || letter > 'L')	cout << "Invalid move. Enter another move. " << endl;

			}while(board[num][letter - 64] != '.' || letter > 'L');

			add_move(board, size, 2, letter, num);

			if(o_win(board, check, size) == 1)	cout << endl << "Congratulations Player 2, you won!" << endl;

		}

	}

	print_board(board, size); //Prints the final board

}

void user_vs_computer(char board[][13], int size){

	char letter, letter_c = 'A'; 						// letter_c and num_c represents computer's position
	int num, num_c = size / 2, count = -1; 			//the computer will start from the very left of the board and
														//try to make its way to the very right
	char check[13][13];									// count is used to determine the moves the computer will make
	fill_board(check, size);

	print_board(board, size);

	cout << "Computer: " << letter_c << " " << num_c << endl;

	add_move(board, size, 1, letter_c, num_c);

	while(x_win(board, check, size) == 0 && o_win(board, check, size) == 0){

		print_board(board, size);

		do{

			cout << "Your move: ";
			cin >> letter >> num;

			if(board[num][letter - 64] != '.' || letter > 'L')	cout << "Invalid move. Enter another move." << endl;

		}while(board[num][letter - 64] != '.' || letter > 'L'); // If that position is not marked by '.' or if it's greater then 'L',
																// player should pick another move
		add_move(board, size, 2, letter, num);

		if(o_win(board, check, size) == 1)	cout << endl << "Congratulations, you won!" << endl;
		else{

			print_board(board, size);

			count++;

			if(count == 0){ 		// Computer will go to one of the available positions on its six sides

				if(board[num_c][(letter_c - 64) + 1] != '.')	count += 2;
				else										letter_c++;

			}

			if(count == 1){

				if(board[num_c + 1][letter_c - 64] != '.')	count += 2;
				else											num_c++;

			}

			if(count == 2){

				if(board[num_c - 1][(letter_c - 64) + 1] != '.')	count += 2;
				else{

					letter_c++;
					num_c--;

				}

			}

			if(count == 3){

				if(board[num_c - 1][letter_c - 64] != '.')	count += 2;
				else										num_c--;

			}

			if(count == 4){

				if(board[num_c][(letter_c - 64) - 1] != '.')	count = (count + 3) % 6;
				else											letter_c--;

			}

			if(count == 5){

				if(board[num_c + 1][(letter_c - 64) - 1] != '.'){

					if(board[num_c - 1][(letter_c - 64) + 1] == '.'){

						letter_c++;
						num_c--;

					}

					count = -1;

				}
				else{

					letter_c--;
					num_c++;

				}

			}



			cout << "Computer: " << letter_c << " " << num_c << endl;

			add_move(board, size, 1, letter_c, num_c);

			if(x_win(board, check, size) == 1)	cout << endl << "You lost..." << endl;

		}

	}

	print_board(board, size);

}

