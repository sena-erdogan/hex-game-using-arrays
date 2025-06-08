/*
 * 	This is the header file for the library of hex game
 * 	Contains the declarations of the functions used in the program
 *
 */

#ifndef HEXLIB_H
#define HEXLIB_H

void fill_board(char board[][13], int size);

void print_board(char board[][13], int size);

int x_win(char board[][13], char check[][13], int size);

int o_win(char board[][13], char check[][13], int size);

void add_move(char board[][13], int size, int player, char letter, int num);

void user_vs_user(char board[][13], int size);

void user_vs_computer(char board[][13], int size);

#endif
