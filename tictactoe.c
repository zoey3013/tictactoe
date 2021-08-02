#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//Prototypes
void playerturn(int player);
bool evaluatewinner(void);
void printboard(void);
bool evaluatedraw(void);

//Starts the board
int board[3][3] = { { 0, 0, 0 }, {0, 0, 0}, {0, 0, 0} };

int main(void)
{
    //Initializes the variables
    int turn = 0, player = 0;
    bool winner = false, draw = false;

    do
    {
        turn++;

        printboard();

        //Gets the actual player and runs the play
        if (turn % 2 == 0)
        {
            player = 2;
        }
        else
        {
            player = 1;
        }

        playerturn(player);

        //Evaluates if needs finish
        winner = evaluatewinner();
        draw = evaluatedraw();
    }
    while (winner == false && draw == false);

    //Endgame screen
    printboard();
    if (winner == true)
    {
        printf("Player %i wins!", player);
    }

    else
    {
        printf("Draw!");
    }
}

void playerturn(int player)
{
    //Initializes variables
    int linecoord, columncoord;
    string spacecoord;
    bool check = true;

    printf("Player %i turn:\n", player);

    //Gets space from player
    do
    {
        do
        {
            spacecoord = get_string("Space: ");
            if (strlen(spacecoord) == 2)
            {
                if (islower(spacecoord[0]))
                {
                    spacecoord[0] = toupper(spacecoord[0]);
                }

                //Turns string to int
                linecoord = spacecoord[0] - 65;
                columncoord = spacecoord[1] - 49;

                if ((linecoord >= 0 && linecoord < 3) && (columncoord >= 0 && columncoord < 3))
                {
                    check = false;
                }
                else
                {
                    printf("Invalid format, try again (ex. A1).\n");
                }
            }
            else
            {
                printf("Invalid format, try again (ex. A1).\n");
            }
        }
        while (check);
        if (board[linecoord][columncoord] != 0)
        {
            printf("Casilla ocupada, intentalo de nuevo.\n");
        }
    }
    while (board[linecoord][columncoord] != 0);

    //Plays on space
    board[linecoord][columncoord] = player;
}

bool evaluatewinner(void)
{
    //Looks for line win
    for (int line = 0; line < 3; line++)
    {
        if (board[line][0] == board[line][1] && board[line][0] == board[line][2] && board[line][0] != 0)
        {
            return true;
        }
    }

    //Looks for column win
    for (int column = 0; column < 3; column++)
    {
        if (board[0][column] == board[1][column] && board[0][column] == board[2][column] && board[0][column] != 0)
        {
            return true;
        }
    }

    //Looks for diagonal win
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0)
    {
        return true;
    }

    //Looks for second diagonal win
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[2][0] != 0)
    {
        return true;
    }

    return false;
}

void printboard(void)
{
    //Prints the board
    printf("   1 2 3\n");
    for (int line = 0; line < 3; line++)
    {
        printf("%c ", line + 65);
        for (int column = 0; column < 3; column++)
        {
            if (board[line][column] == 0)
            {
                printf("| ");
            }
            else if (board[line][column] == 1)
            {
                printf("|x");
            }
            else if (board[line][column] == 2)
            {
                printf("|o");
            }
        }
        printf("|\n");
    }
}

bool evaluatedraw(void)
{
    //Looks for empty spaces
    for (int line = 0; line < 3; line++)
    {
        for (int column = 0; column < 3; column++)
        {
            if (board[line][column] == 0)
            {
                return false;
            }
        }
    }

    return true;
}
