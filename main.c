/*
Project: Truth table generator
Subject: Logic and Discrete Structures
Professor: Miguel Ángel Ojeda Orozco
Period: Spring 2024

Authors:
- Ethan Gabriel Orozco Madrid
- José Emmanuel Pulido Tinajero
- Ian Eugenio Rodríguez Wong

Special thanks to Erick Eduardo Rodríguez Gómez

Current delivery: Part III of III
Just never again pls
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct
{
    int num_propositions;
    int rows;
    int columns;
    char board[100][100][50];
} proposition; //Creating the structure that will serve as our table for the program

void request_proposition(proposition *Main);
int search_column(proposition *Main, char *search);
proposition operate(proposition Main, char *operation, int col1, int col2, int result_col);
void criticalRows(proposition *Main);

int main(void)
{
    proposition Main;
    printf("How many propositions do you want to evaluate? ");
    scanf("%d", &Main.num_propositions);
    getchar();
    Main.columns = Main.num_propositions; //Equalizing the columns to the number of propositions for Main.columns to be updated throughout the program
    request_proposition(&Main);
    criticalRows(&Main);
    return 0;
}

//Function in charge of searching for the index of a column given the memory address of the proposition as a parameter
int search_column(proposition *Main, char *search)
{
    for (int i = 0; i < Main->columns; i++)
    {
        if (strcmp(Main->board[0][i], search) == 0)
        {
            return i;
        }
    }
    return -1;
}

//Function in charge of asigning a "true" or "false" value to each "cell" according to the operation given as a parameter
proposition operate(proposition Main, char *operation, int col1, int col2, int result_col)
{
    for (int i = 1; i < Main.rows; i++)
    {
        int true1 = strcmp(Main.board[i][col1], "True") == 0;
        int true2 = strcmp(Main.board[i][col2], "True") == 0;
        if (strcmp(operation, "&") == 0)
        {
            strcpy(Main.board[i][result_col], (true1 && true2) ? "True" : "False");
        }
        else if (strcmp(operation, "|") == 0)
        {
            strcpy(Main.board[i][result_col], (true1 || true2) ? "True" : "False");
        }
        else if (strcmp(operation, "->") == 0)
        {
            strcpy(Main.board[i][result_col], (!true1 || true2) ? "True" : "False");
        }
    }
    strcpy(Main.board[0][result_col], operation);
    return Main;
}

//Function in charge of printing the formatted table
void print_table(proposition *Main)
{
    for (int i_row = 0; i_row < Main->rows; i_row++)
    {
        for (int i_column = 0; i_column < Main->columns; i_column++)
        {
            printf("|%-11s", Main->board[i_row][i_column]);
        }
        printf("|\n");
    }
}

//Function that prints the menu the user sees
void printMenu(void)
{
    printf("Enter logical operations using the following numbers:\n"
            "1 - Negation, e.g., q'\n"
            "2 - Conjunction (&), e.g., p & q\n"
            "3 - Disjunction (|), e.g., p | q\n"
            "4 - Copy proposition\n"
            "5 - Implication (->), e.g., p -> q\n"
            "Type '0' to finish entering your prepositions\n");
}

//Function in charge of analizing whether the entire argument is valid or not
void criticalRows(proposition *Main)
{
    short value = 1;
    int returnedColumnIndex, TrueCriticalRows = 0, FalseCriticalRows = 0;
    char premise[50];

    printf("Enter the beginning of your premises: ");
    scanf("%s", premise);
    returnedColumnIndex = search_column(Main, premise);
    if (returnedColumnIndex == -1) printf("Premise not found.\n");

    for (int x = 1; x <= Main->rows; x++)
    {
        int counter1 = 0, counter2 = 0, y, preConclusionColumn=Main->columns-2;

        for (y = returnedColumnIndex; y <= preConclusionColumn; y++)
        {
            counter1++;
            if (strcmp(Main->board[x][y], "True") == 0)
            {
                counter2++;
            }
        }

        int variable = strcmp(Main->board[x][preConclusionColumn+1], "True");
        if (counter1 == counter2 && variable == 0)
        {
            TrueCriticalRows++;
        }
        if (counter1 == counter2 && variable != 0)
        {
            FalseCriticalRows++;
        }
    }
    
    if (FalseCriticalRows > 0){
        TrueCriticalRows = 0;
    }

    if (TrueCriticalRows > 0)
    {
        printf("Valid argument. %d critical rows.\n", TrueCriticalRows);
    }
    else
    {
        printf("Argument NOT valid.");
    }
}

/*
In general, a mess of a function. Its original purpose was to recieve the propositions from the user,
now it morphed into this abomination.
*/
void request_proposition(proposition *Main)
{
    char temp[100];
    int option;
    Main->rows = pow(2, Main->num_propositions) + 1;

    for (int x = 0; x < Main->num_propositions; x++)
    {
        printf("Enter the proposition %d: ", x);
        scanf(" %s", temp);
        strcpy(Main->board[0][x], temp); //Puts the proposition as a header
    }

    for (int x = 1; x < Main->rows; x++)
    {
        for (int y = 0; y < Main->num_propositions; y++)
        {
            if ((((x - 1) >> (Main->num_propositions - y - 1)) & 1) == 0) //Bitwise operation to determine the values of true or false of the initial propositions
            {
                strcpy(Main->board[x][y], "True");
            }
            else
            {
                strcpy(Main->board[x][y], "False");
            }   
        }
    }

    print_table(Main);
    printMenu();
    scanf("%d", &option);

    while (option != 0)
    {
        char userProposition[50], secondProposition[50], operation[10];
        int returnedColumnIndex, secondReturnedColumnIndex, flag;
        switch (option)
        {
        case 1:
            printf("Which proposition would you like to negate? ");
            scanf("%s", userProposition);
            returnedColumnIndex = search_column(Main, userProposition);

            if (returnedColumnIndex != -1)
            {
                Main->columns++;
                strcpy(Main->board[0][Main->columns - 1], userProposition);
                strcat(Main->board[0][Main->columns - 1], "'");
                for (int i = 1; i < Main->rows; i++)
                {
                    strcpy(Main->board[i][Main->columns - 1], strcmp(Main->board[i][returnedColumnIndex], "True") == 0 ? "False" : "True");
                }
            }
            else
            {
                printf("Proposition not found.\n");
            }
            break;
        case 2:
            printf("Enter the first proposition: ");
            scanf("%s", userProposition);

            printf("Enter the second proposition: ");
            scanf("%s", secondProposition);
            strcpy(operation, "&");
            flag = 2;
            goto common_logic;
        case 3:
            printf("Enter the first proposition: ");
            scanf("%s", userProposition);

            printf("Enter the second proposition: ");
            scanf("%s", secondProposition);
            strcpy(operation, "|");
            flag = 3;
            goto common_logic;
        case 4:
            printf("Enter proposition: ");
            scanf("%s", userProposition);
            returnedColumnIndex = search_column(Main, userProposition);

            if (returnedColumnIndex != -1)
            {
                Main->columns++;
                strcpy(Main->board[0][Main->columns - 1], userProposition);
                for (int i = 1; i < Main->rows; i++)
                {
                    strcpy(Main->board[i][Main->columns - 1], Main->board[i][returnedColumnIndex]);
                }
            }
            else
            {
                printf("Proposition not found.\n");
            }
            break;

        case 5:
            printf("Enter the first proposition: ");
            scanf("%s", userProposition);

            printf("Enter the second proposition: ");
            scanf("%s", secondProposition);
            strcpy(operation, "->");
            flag = 4;
            goto common_logic;

        common_logic:

            returnedColumnIndex = search_column(Main, userProposition);
            secondReturnedColumnIndex = search_column(Main, secondProposition);

            if (returnedColumnIndex != -1 && secondReturnedColumnIndex != -1)
            {
                Main->columns++;
                *Main = operate(*Main, operation, returnedColumnIndex, secondReturnedColumnIndex, Main->columns - 1);

                if (flag == 2)
                {
                    strcpy(Main->board[0][Main->columns - 1], userProposition);
                    strcat(Main->board[0][Main->columns - 1], "&");
                    strcat(Main->board[0][Main->columns - 1], secondProposition);
                }
                else if (flag == 3)
                {
                    strcpy(Main->board[0][Main->columns - 1], userProposition);
                    strcat(Main->board[0][Main->columns - 1], "|");
                    strcat(Main->board[0][Main->columns - 1], secondProposition);
                }
                else if (flag == 4)
                {
                    strcpy(Main->board[0][Main->columns - 1], userProposition);
                    strcat(Main->board[0][Main->columns - 1], "->");
                    strcat(Main->board[0][Main->columns - 1], secondProposition);
                }
            }
            else
            {
                printf("Propositions not found.\n");
            }
            break;
        }

        print_table(Main);
        printMenu();
        scanf("%d", &option);
        if (option == 0)
        {
            char exit;
            printf("This will make the last premise your conclusion. Are you sure? y/n\n");
            fflush(stdin);
            scanf("%c", &exit);
            if (exit == 'y')
                continue;
            else
            {
                printMenu();
                scanf("%d", &option);
            }
        }
    }
}
