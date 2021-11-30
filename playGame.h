/* 
Author: Cassandra Jacklya
Purpose: Header file for playGame.c
Last modified on: 11th October 2021
*/

#ifndef PLAY
#define PLAY
void getObj(char **board, int *row, int *col, char object, int mapRow, int mapCol);
void keyPressed(char ***board, char value, int row, int col, char *player);
void snakeMove(char ***board, int playRow, int playCol, int snakeRow, int snakeCol, int mapRow, int mapCol);
#endif
