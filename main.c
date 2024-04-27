/*
Project: Truth table generator
Subject: Logic and Discrete Structures
Professor: Miguel Ángel Ojeda Orozco
Period: Spring 2024

Authors:
- Ethan Gabriel Orozco Madrid
- José Emmanuel Pulido Tinajero
- Ian Eugenio Rodríguez Wong

Current delivery: Part II  ofT III
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
} proposition;

void request_proposition(proposition Main);

int main()
{
    proposition Main;
    printf("How many propositions do you want to evaluate? ");
    scanf("%d", &Main.num_propositions);
    getchar();
    Main.columns = Main.num_propositions;
    request_proposition(Main);

    return 0;
}

int search_column(proposition Main, char *search)
{
    for (int i = 0; i < 100; i++)
    {
        printf("Comparing with: %s\n", Main.board[0][i]);
        if (strcmp(Main.board[0][i], search) == 0)
        {
            return i;
            break;
        }
    }
    return -1;
}

proposition conjunction(proposition Main, int col1, int col2, int result_col)
{
    for (int i = 1; i < Main.rows; i++)
    {
        if (strcmp(Main.board[i][col1], "True") == 0 && strcmp(Main.board[i][col2], "True") == 0)
        {
            strcpy(Main.board[i][result_col], "True");
        }
        else
        {
            strcpy(Main.board[i][result_col], "False");
        }
    }
    return Main;
}

proposition disjunction(proposition Main, int col1, int col2, int result_col)
{
    for (int i = 1; i < Main.rows; i++)
    {
        if (strcmp(Main.board[i][col1], "True") == 0 || strcmp(Main.board[i][col2], "True") == 0)
        {
            strcpy(Main.board[i][result_col], "True");
        }
        else
        {
            strcpy(Main.board[i][result_col], "False");
        }
    }
    return Main;
}

proposition implication(proposition Main, int col1, int col2, int result_col)
{
    for (int i = 1; i < Main.rows; i++)
    {
        if (strcmp(Main.board[i][col1], "True") == 0 && strcmp(Main.board[i][col2], "False") == 0)
        {
            strcpy(Main.board[i][result_col], "False");
        }
        else
        {
            strcpy(Main.board[i][result_col], "True");
        }
    }
    return Main;
}

proposition negation(proposition Main, int col, int result_col)
{
    for (int i = 0; i < Main.rows; i++)
    {
        if (i == 0)
        {
            // strcpy(Main.board[i][col],"");
        }
        else if (strcmp(Main.board[i][col], "True") == 0)
        {
            strcpy(Main.board[i][result_col], "False");
        }
        else
        {
            strcpy(Main.board[i][result_col], "True");
        }
    }

    return Main;
}

void print_table(proposition Main)
{
    for (int i_row = 0; i_row < Main.rows; i_row++)
    {
        for (int i_column = 0; i_column < Main.columns; i_column++)
        {
            printf("|%-11s", Main.board[i_row][i_column]);
        }
        printf("\n");
    }
}

void printMenu (void)
{
    printf("Enter logical operations using the following symbols:\n"
           "1 - Negation (~), e.g., ~q\n"
           "2 - Conjunction (&), e.g., p & q\n"
           "3 - Disjunction (|), e.g., p | q\n"
           "4 - Implication (->), e.g., p -> q\n"
           "Type '0' to finish entering your prepositions\n");
}

void request_proposition(proposition Main)
{
    int option;
    Main.rows = pow(2, Main.num_propositions) + 1;

    for (int x = 0; x < Main.num_propositions; x++)
    {
        printf("Enter the proposition %d: ", x);
        scanf("%c", &Main.board[0][x][0]);
        getchar();
        fflush(stdin);
    }

    for (int x = 1; x < Main.rows; x++)
    {
        for (int y = 0; y < Main.num_propositions; y++)
        {
            if ((((x - 1) >> (Main.num_propositions - y - 1)) & 1) == 0) // Bitwise operation AND with number 1 to print the values of the propositions
            {
                strcpy(Main.board[x][y], "True");
            }
            else
            {
                strcpy(Main.board[x][y], "False");
            }
        }
    }
    printf("\n");
    print_table(Main);
    printf("\n");

    printMenu();
    scanf("%d", &option);

    while (option != 0)
    {
        char userProposition[2], secondProposition[2];
        switch (option)
        {

        case 1:
            printf("Which proposition would you like to negate? ");
            fflush(stdin);
            fgets(userProposition, 2, stdin);
            int returnedColumnIndex = search_column(Main, userProposition);

            if (returnedColumnIndex != -1)
            {
                Main = negation(Main, returnedColumnIndex, Main.columns);
                Main.columns += 1;
            }
            else
            {
                printf("Proposition not found.\n");
            }
            break;

        case 2:
            fflush(stdin);
            printf("Enter the first proposition: ");
            fgets(userProposition, 2, stdin);
            returnedColumnIndex = search_column(Main, userProposition);

            fflush(stdin);
            printf("Enter the second proposition: ");
            fgets(secondProposition, 2, stdin);
            int secondReturnedColumnIndex = search_column(Main, secondProposition);

            if (returnedColumnIndex != -1 && secondReturnedColumnIndex != -1)
            {
                Main = implication(Main, returnedColumnIndex, secondReturnedColumnIndex, Main.columns);
                Main.columns += 1;
            }
            else
            {
                printf("Propositions not found.\n");
            }
            break;

        case 3:
            fflush(stdin);
            printf("Enter the first proposition: ");
            fgets(userProposition, 2, stdin);
            int col1 = search_column(Main, userProposition);

            fflush(stdin);
            printf("Enter the second proposition: ");
            fgets(secondProposition, 2, stdin);
            int col2 = search_column(Main, secondProposition);

            if (col1 != -1 && col2 != -1)
            {
                Main = disjunction(Main, col1, col2, Main.columns);
                Main.columns += 1;
                //print_table(Main);
            }
            else
            {
                printf("Propositions not found.\n");
            }
            break;

        case 4:
            fflush(stdin);
            printf("Enter the first proposition: ");
            fgets(userProposition, 2, stdin);
            int col3 = search_column(Main, userProposition);

            // fflush(stdin);
            // printf("Enter the second proposition: ");
            // fgets(secondProposition, 2, stdin);
            // int col4 = search_column(Main, secondProposition);

            // if (col1 != -1 && col2 != -1)
            // {
            //     Main = disjunction(Main, col1, col2, Main.columns);
            //     Main.columns += 1;
            //     //print_table(Main);
            //     printf("Qiubo");
            // }
            // else
            // {
            //     printf("Propositions not found.\n");
            // }
            // break;

        default:
            break;
        }

        print_table(Main);
        printf("\n");
        printMenu();
        scanf("%d", &option);
    }
}