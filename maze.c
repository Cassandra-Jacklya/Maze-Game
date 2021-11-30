/* 
Author: Cassandra Jacklya
Purpose: This is the main program of the game
Last modified on: 11th October 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"
#include "playGame.h"
#include "LinkedList.h"

/*prints list*/
void printResult(void *data) 
{
    printf("%d %d %d %d %c\n", ((MazeGame *)data)->snakeRow, ((MazeGame *)data)->snakeCol, ((MazeGame *)data)->playerRow, ((MazeGame *)data)->playerCol, ((MazeGame *)data)->player);
}

/*frees the pointers in the list*/
void freeList(void *data)
{
    free(data);
    data = NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)      /* Ensures that only if there is only one argument excluding the executable file */
    {
        printf("There should be only one argument\n");
    }
    else 
    {
        FILE *inPtr = NULL;
        inPtr = fopen(argv[1], "r");    /*sets the file pointer to read mode*/
        if (inPtr == NULL)  /*checks if the file pointer still points to NULL*/
        {
            perror("Error in opening file\n");  /*prints message for file error*/
        }
        else
        {   
            /*variables*/
            int objRow, objCol, objCode;
            int objCount, gameRow, gameCol;
            int i, j, playRow, playCol, snakeRow, snakeCol;
            int goalRow, goalCol;
            int **values = NULL;
            char **board = NULL;
            char player, ch, snake;
            LinkedList *LL = createLinkedList();    /*make a new linked list*/
            MazeGame *temp = NULL;  /*points the pointers to NULL*/
            MazeGame *game = NULL;

            fscanf(inPtr, "%d %d %d\n", &objCount, &gameRow, &gameCol); /*gets the first line in the file*/

            board = (char **) malloc(sizeof(char * ) * (gameRow));    /*mallocs the double pointers to make memory for the values*/
            for(i = 0; i < gameRow; i++)
            {
                board[i] = (char *) malloc(sizeof(char) * gameCol); 
            }

            values = (int **) malloc(sizeof(int *) * gameRow);
            for (i = 0; i < gameRow; i++) 
            {
                values[i] = (int *)malloc(sizeof(int) * gameCol);
            }

            for (i = 0; i < gameRow; i++)   /*makes the values to be 0 first, to avoid problems of uninitialized values*/
            {
                for (j = 0; j < gameCol; j++)
                {
                    values[i][j] = 0;
                }
            }

            while (fscanf(inPtr, "%d %d %d\n", &objRow, &objCol, &objCode) != EOF)  /*if not yet the last line in the file*/
            {
                values[objRow][objCol] = objCode;   /*places in the values in the array*/
                if (objCode == 0)
                {
                    values[objRow][objCol] = 4; /*since player is code 0, create another special value for player*/
                }
                else if (objCode == 2) 
                {
                    goalCol = objCol;
                    goalRow = objRow;
                }
            }
            fclose(inPtr);  /*close file*/

            gameBoard(&values, &board, gameRow, gameCol, objCount); /*create the board*/
            player = '^';   
            snake = '~';
    
            getObj(board, &playRow, &playCol, player, gameRow, gameCol); /*gets the row and col for player*/
            getObj(board, &snakeRow, &snakeCol, snake, gameRow, gameCol);   /*gets the row and col for snake*/
            
            display(board, gameRow, gameCol, playRow, playCol, snakeRow, snakeCol, player); /*diplays the board on the terminal*/
            disableBuffer();    /*disable buffer*/
            while(!(((playRow == goalRow) && (playCol == goalCol)) || ((playRow == snakeRow) && (playCol == snakeCol))))    /*checks whether the player loses or wins*/
            { 
                scanf(" %c", &ch);  /*gets input from user to move player*/
                if (ch == 'u')  /*if player wants to undo*/
                {
                    free(removeStart(LL));  /*remove the first element in the list*/
                    temp = getTop(LL); /*gets the current top node*/

                    if (temp != NULL)   /*if list is not empty*/
                    {
                        /*create the board from previous step*/
                        board[playRow][playCol] = ' '; 
                        player = temp->player;
                        playRow = temp->playerRow;
                        playCol = temp->playerCol;
                        snakeRow = temp->snakeRow;
                        snakeCol = temp->snakeCol;
                    }
                    else
                    {
                        /*if empty, then create the initial board again*/
                        gameBoard(&values, &board, gameRow, gameCol, objCount);
                        player = '^';
                        snake = '~';
                
                        getObj(board, &playRow, &playCol, player, gameRow, gameCol);
                        getObj(board, &snakeRow, &snakeCol, snake, gameRow, gameCol);
                    }
                    temp = NULL;    /*free the temporary pointer*/
                }
                else
                { 
                    game = (MazeGame *)malloc(sizeof(MazeGame));    /*creates memory for the node*/
                    keyPressed(&board, ch, playRow, playCol, &player);  /*checks which key is pressed*/
                    getObj(board, &playRow, &playCol, player, gameRow, gameCol);    /*gets the row and col of the player*/
                    snakeMove(&board, playRow, playCol, snakeRow, snakeCol, gameRow, gameCol);  /*moves the snake to chase the player*/         
                    getObj(board, &snakeRow, &snakeCol, snake, gameRow, gameCol);   /*gets the row and col of the snake*/     
                    game->player = player;
                    game->playerRow = playRow;
                    game->playerCol = playCol;
                    game->snakeRow = snakeRow;
                    game->snakeCol = snakeCol;
                    insertStart(LL, game);     /*insert the node to be the first in the list*/
                }
                system("clear");    /*clears the terminal*/
                display(board, gameRow, gameCol, playRow, playCol, snakeRow, snakeCol, player); /*display the current board*/
            }
            enableBuffer(); /*enables buffer*/
            freeLinkedList(LL, &freeList);  /*frees the pointer and the list*/
            if ((playRow == goalRow) && (playCol == goalCol))
            {
                printf("%s\n","Woah, you won!"); /*prints message if player wins*/
            }
            else
            {
                printf("%s\n", "Sorry, you lost! Try again.");  /*prints message if player lost*/
            }

            /*free remaining pointers*/
            for (i = 0; i < gameRow; i++)
            {
                free(board[i]); 
                board[i] = NULL;
            }
            free(board);
            board = NULL;

            for (i = 0; i < gameRow; i++)
            {
                free(values[i]);
                values[i] = NULL;
            }
            free(values);
            values = NULL;
        }     
    }
    return 0;
}