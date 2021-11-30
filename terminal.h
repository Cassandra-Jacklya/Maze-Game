/* 
Author: Cassandra Jacklya
Purpose: Header file for terminal.c
Last modified on: 11th October 2021
*/

#ifndef TERMINAL_H
#define TERMINAL_H

void gameBoard(int ***table, char ***temp, int mapRow, int mapCol, int obj);
void disableBuffer();
void enableBuffer();
char object(int data);
void display(char **board, int mapRow, int mapCol, int playerRow, int playerCol, int snakeRow, int snakeCol, char player);
#endif