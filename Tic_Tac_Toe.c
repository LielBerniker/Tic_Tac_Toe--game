#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';
const int rowSize = sizeof(board) / sizeof(board[0]);
const int colSize = sizeof(board[0]) / sizeof(board[0][0]);
void resetBoard();
void printBoard();
int checkFreeSpaces();
void computerMove();
void PlayerMove();
char checkWinner();
void printWinner(char winner);
char checkCon();

int main()
{
    char winner;
    char response;
    do
    {
        winner = ' ';
        response = ' ';
        resetBoard();
        while (winner == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();

            PlayerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }

            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
        }
        printBoard();
        printWinner(winner);
        response = checkCon();
    } while (response == 'Y');
    return 0;
}

void resetBoard()
{
    for (size_t i = 0; i < rowSize; i++)
    {
        for (size_t j = 0; j < colSize; j++)
        {
            board[i][j] = ' ';
        }
    }
}
void printBoard()
{
    for (size_t i = 0; i < rowSize; i++)
    {
        for (size_t j = 0; j < colSize; j++)
        {
            if (j % rowSize == 2)
            {
                printf(" %c ", board[i][j]);
            }
            else
            {
                printf(" %c |", board[i][j]);
            }
        }
        if (i % rowSize != 2)
        {
            printf("\n---|---|---\n");
        }
        else
        {
            printf("\n");
        }
    }
}
int checkFreeSpaces()
{
    int freeSpaces = 9;
    for (size_t i = 0; i < rowSize; i++)
    {
        for (size_t j = 0; j < colSize; j++)
        {
            if (board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}
void computerMove()
{
    // create seed to random number
    srand(time(0));
    int x;
    int y;

    if (checkFreeSpaces() > 0)
    {
        do
        {
            x = rand() % rowSize;
            y = rand() % colSize;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else
    {
        printWinner('.');
    }
}
void PlayerMove()
{
    int x;
    int y;
    do
    {
        printf("Enter row #(1-3): \n");
        scanf("%d", &x);
        x--;
        printf("Enter colum #(1-3): \n");
        scanf("%d", &y);
        y--;

        if (board[x][y] != ' ')
        {
            printf("INvalid move!\n");
        }
        else
        {
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
}
char checkWinner()
{
    // check rows
    for (size_t i = 0; i < rowSize; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }
    // check colums
    for (size_t j = 0; j < colSize; j++)
    {
        if (board[0][j] == board[1][j] && board[0][j] == board[2][j])
        {
            return board[0][j];
        }
    }
    // check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }
    return ' ';
}
void printWinner(char winner)
{
    if (winner == PLAYER)
    {
        printf("YOU WON!!");
    }
    else if (winner == COMPUTER)
    {
        printf("YOU LOSE :(");
    }
    else
    {
        printf("IT IS A TIE!");
    }
}
char checkCon()
{
    char response = ' ';
    bool correctAns = false;
    printf("\nWould you like to play again? (Y/N)");
    while (correctAns == false)
    {
        scanf("%c", &response);
        response = toupper(response);
        if (response != 'Y' || response != 'N')
        {
            printf("\nplease choose one of the letters (Y/N)");
        }
        else
        {
            correctAns = true;
        }
    }
    return correctAns;
}