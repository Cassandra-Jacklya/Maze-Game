/* 
Author: Cassandra Jacklya
Purpose: This file mainly focuses on the terminal output of the program
Last modified on: 11th October 2021
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include "terminal.h"

/*done!*/
void gameBoard(int ***table, char ***temp, int mapRow, int mapCol, int data)
{
    int i, j;
    char corner = '#';      /* corners of the board */
    char leftRight = '|';   /* The left and right of the board */
    char topBottom = '-';   /* top and bottom border of the board */

 /*   temp = (char**) malloc(sizeof(char*)*(mapRow));    
    for(i = 0; i < mapRow; i++)
    {
        temp[i] = (char*) malloc(sizeof(char)*mapCol); 
    } */
    
    temp[0][0][0] = temp[0][0][mapCol-1] = temp[0][mapRow-1][0] = temp[0][mapRow-1][mapCol-1] = corner; /* Gives the corners for the board */

    for (i = 0; i < mapRow; i++)
    {
        if ((i == 0) || (i == (mapRow-1)))
        {
            for (j = 1; j < mapCol-1; j++) 
            {
                temp[0][i][j] = topBottom;         /* Places the border at the top and bottom of the board */
            }
        }
        else
        {
            for (j = 0; j < mapCol; j++) 
            {
                if ((j == 0) || (j == (mapCol-1)))
                {
                    temp[0][i][j] = leftRight;     /* Places the border at the left and right of the board */
                }
                else
                {
                    temp[0][i][j] = ' ';          /* Initial placement of spaces in the board */
                }
            }
        }
    }
    for (i = 1; i < mapRow-1; i++) 
    {
        for (j = 1; j < mapCol-1; j++)
        {
            temp[0][i][j] = object(table[0][i][j]);
        }
    }
}

/*displays the current situation of the board*/
void display(char **board, int mapRow, int mapCol, int playerRow, int playerCol, int snakeRow, int snakeCol, char player)
{
    int i, j;
    for (i = 0; i < mapRow; i++)   
    {
        for (j = 0; j < mapCol; j++)
        {
            if ((i == playerRow) && (j == playerCol))   /*places the player in the correct location*/
            {
                printf("%c ", player);
            }
            else if ((i == snakeRow) && (j == snakeCol))    /*places the snake in the correct location*/
            {
                printf("%c ", '~');
            }
            else if (board[i][j] == 'o' || board[i][j] == '|' || board[i][j] == '-' || board[i][j] == '#' || board[i][j] == 'x' )   
            {
                printf("%c ", board[i][j]); /*prints the borders and obstacles*/
            }
            else 
            {
                printf("%c ", ' ');
            }
        }
        printf("%s", "\n");     /* prints a new line for next row */
    }
}

/*check the code of the object for correct placement on the board*/
char object(int data)
{
    char value = ' ';
    switch(data)
    {
        case 0:
            value = ' ';   
            break;
        case 1:
            value = '~';    
            break;
        case 2:
            value = 'x';    
            break;
        case 3:
            value = 'o';
            break;
        case 4:
            value = '^';
            break;
    }
    return value;
}

/* this disables the buffer in the terminal */
void disableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

/* enables the buffer in the terminal */
void enableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

 