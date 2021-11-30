/* 
Author: Cassandra Jacklya
Purpose: Handles the game's features
Last modified on: 11th October 2021
*/

 
#include <stdio.h>
#include "playGame.h"

/* gets the player's row and column number */
void getObj(char **board, int *row, int *col, char object, int mapRow, int mapCol)
{   
    int found, i, j;
    found = 0;

    while (found == 0)      /* if not yet found player */
    {
        for (i = 0; i < mapRow; i++)       /* Keep iterating through the board */
        {
            for (j = 0; j < mapCol; j++)
            {
                if (board[i][j] == object)     /* Once player is found */
                {
                    *row = i;   /* get row */
                    *col = j;   /* get column */
                    found = 1;  /* end the while loop */
                    i = mapRow;
                    j = mapCol;
                }
            }
        }
    }
}

/* checks which key is pressed and respond accordingly */
void keyPressed(char ***board, char value, int oldRow, int oldCol, char *player) 
{
    int newRow, newCol;
    
    switch(value)
    {
        case 'w':
            newRow = oldRow - 1;
            newCol = oldCol;
            *player = '^';
            break;
        case 'a':
            newCol = oldCol - 1;
            newRow = oldRow;
            *player = '<';
            break;
        case 's':
            newRow = oldRow + 1;
            newCol = oldCol;
            *player = 'v';
            break;
        case 'd':
            newCol = oldCol + 1;
            newRow = oldRow;
            *player = '>';
            break; 
        default:
            newCol = oldCol;
            newRow = oldRow;
            break;
    }
    if ((board[0][newRow][newCol] == ' ') || (board[0][newRow][newCol] == 'x')) /* checks if there is no obstacle at the new path */
    {
        if (value == 'w')
        {
            board[0][newRow][newCol] = '^';
            board[0][oldRow][oldCol] = ' ';
        }
        else if (value == 'a')
        {
            board[0][newRow][newCol] = '<';
            board[0][oldRow][oldCol] = ' ';
        }
        else if (value == 's')
        {
            board[0][newRow][newCol] = 'v';
            board[0][oldRow][oldCol] = ' ';
        }
        else if (value == 'd')
        {
            board[0][newRow][newCol] = '>';
            board[0][oldRow][oldCol] = ' ';
        }
        else 
        {
            board[0][newRow][newCol] = *player;
        }
        
    }
    else    /* Else if a wall is detected, then only change the player's character but position remains */
    {
        if (value == 'w')
        {
            board[0][oldRow][oldCol] = '^';
        }
        else if (value == 'a')
        {
            board[0][oldRow][oldCol] = '<';
        }
        else if (value == 's')
        {
            board[0][oldRow][oldCol] = 'v';
        }
        else if (value == 'd')
        {
            board[0][oldRow][oldCol] = '>';
        }
        else 
        {
            board[0][oldRow][oldCol] = *player;
        }
    }
}

/*snake will chase the player*/
void snakeMove(char ***board, int playRow, int playCol, int snakeRow, int snakeCol, int mapRow, int mapCol) 
{   
    int newRow, newCol;
    newRow = snakeRow;
    newCol = snakeCol;
    /*compares the location of the player and snake*/
    if ((playCol > snakeCol) && (playRow > snakeRow))
    {
        newCol = snakeCol + 1;
        if (((newCol <= mapCol-2) || (newCol >= 1)) && ((newRow <= mapRow-2) || (newRow >= 1))) /*ensures that the value of the new row and new col are within range of board*/
        {
            if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
            {
                /*if all requirements met, change the location of snake*/
                board[0][newRow][newCol] = '~';
                board[0][snakeRow][snakeCol] = ' ';
            }
            else if (board[0][newRow][newCol] == 'o')   /*if not, try to move the snake to the next empty space*/
            {
                newRow = snakeRow + 1;
                newCol = snakeCol;
                if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                {
                    board[0][newRow][newCol] = '~';
                    board[0][snakeRow][snakeCol] = ' ';
                }
            }
        }
    }
    else if ((playCol > snakeCol) && (playRow < snakeRow))
    {
        newCol = snakeCol + 1;
        if (((newCol <= mapCol-2) || (newCol >= 1)) && ((newRow <= mapRow-2) || (newRow >= 1)))
        {
            if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
            {
                board[0][newRow][newCol] = '~';
                board[0][snakeRow][snakeCol] = ' ';
            }
            else if (board[0][newRow][newCol] == 'o')
            {
                newRow = snakeRow - 1;
                newCol = snakeCol;
                if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                {
                    board[0][newRow][newCol] = '~';
                    board[0][snakeRow][snakeCol] = ' ';
                }
            }
        }
    }
    else if ((playCol < snakeCol) && (playRow > snakeRow))
    {
        newCol = snakeCol - 1;
        if (((newCol <= mapCol-2) || (newCol >= 1)) && ((newRow <= mapRow-2) || (newRow >= 1)))
        {
            if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
            {
                board[0][newRow][newCol] = '~';
                board[0][snakeRow][snakeCol] = ' ';
            }
            else if (board[0][newRow][newCol] == 'o')
            {
                newRow = snakeRow + 1;
                newCol = snakeCol;
                if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                {
                    board[0][newRow][newCol] = '~';
                    board[0][snakeRow][snakeCol] = ' ';
                }
            }
        }
    }
    else if ((playCol < snakeCol) && (playRow < snakeRow))
    {
        newCol = snakeCol - 1;
        if (((newCol <= mapCol-2) || (newCol >= 1)) && ((newRow <= mapRow-2) || (newRow >= 1)))
        {
            if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
            {
                board[0][newRow][newCol] = '~';
                board[0][snakeRow][snakeCol] = ' ';
            }
            else if (board[0][newRow][newCol] == 'o')
            {
                newRow = snakeRow - 1;
                newCol = snakeCol;
                if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                {
                    board[0][newRow][newCol] = '~';
                    board[0][snakeRow][snakeCol] = ' ';
                }
            }
        }
    }
    else if (playRow == snakeRow)
    {
        if (playCol < snakeCol)
        {
            newCol = snakeCol - 1;
            if (((newCol <= mapCol-2) || (newCol >= 1)) && ((newRow <= mapRow-2) || (newRow >= 1)))
            {
                if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                {
                    board[0][newRow][newCol] = '~';
                    board[0][snakeRow][snakeCol] = ' ';
                }
            }
            else if (board[0][newRow][newCol] == 'o')
            {
                newCol = snakeCol;
                newRow = snakeRow + 1;
                if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                {
                    board[0][newRow][newCol] = '~';
                    board[0][snakeRow][snakeCol] = ' ';
                }
            }
        }
        else
        {
            newCol = snakeCol + 1;
            if (((newCol <= mapCol-2) || (newCol >= 1)) && ((newRow <= mapRow-2) || (newRow >= 1)))
            {
                if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                {
                    board[0][newRow][newCol] = '~';
                    board[0][snakeRow][snakeCol] = ' ';
                }
            }
            else if (board[0][newRow][newCol] == 'o')
            {
                newCol = snakeCol;
                newRow = snakeRow + 1;
                if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                {
                    board[0][newRow][newCol] = '~';
                    board[0][snakeRow][snakeCol] = ' ';
                }
            }
        }
    }
    else if (playCol == snakeCol)
    {
        if (playRow < snakeRow)
        {
            newRow = snakeRow - 1;
            if (((newCol <= mapCol-2) || (newCol >= 1)) && ((newRow <= mapRow-2) || (newRow >= 1)))
            {
                if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                {
                    board[0][newRow][newCol] = '~';
                    board[0][snakeRow][snakeCol] = ' ';
                }
                else if (board[0][newRow][newCol] == 'o')
                {
                    newRow = snakeRow;
                    newCol = snakeCol + 1;
                    if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                    {
                        board[0][newRow][newCol] = '~';
                        board[0][snakeRow][snakeCol] = ' ';
                    }
                }
            }
        }
        else
        {
            newRow = snakeRow + 1;
            if (((newCol <= mapCol-2) || (newCol >= 1)) && ((newRow <= mapRow-2) || (newRow >= 1)))
            {
                if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                {
                    board[0][newRow][newCol] = '~';
                    board[0][snakeRow][snakeCol] = ' ';
                }
                else if (board[0][newRow][newCol] == 'o')
                {
                    newRow = snakeRow;
                    newCol = snakeCol + 1;
                    if ((board[0][newRow][newCol] != 'o') && (board[0][newRow][newCol] != 'x')) /* checks if there is no obstacle at the new path */
                    {
                        board[0][newRow][newCol] = '~';
                        board[0][snakeRow][snakeCol] = ' ';
                    }
                }
            }
        }
    }
}