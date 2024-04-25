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
int ret;
typedef struct
{
    int num_propositions;
    int rows;
    int columns;
    char board[100][100][50];
} proposition;
void print_columns_propositions(proposition Main);
proposition request_proposition(proposition Main);
int main()
{
    proposition Main;
    printf("How many propositions do you want to evaluate?");
    ret = scanf("%d", &Main.num_propositions);
    getchar();
    print_columns_propositions(Main);
    request_proposition(Main);

    return 0;
}

void print_columns_propositions(proposition Main)
{
    // Array holding ASCII values of characters "p" through "z"
    int propositionList[11] = {112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};

    // Elevating 2 to the power of N (Number of propositions given by the user) and adding 1 to account for the header
    int rows = pow(2, Main.num_propositions) + 1;

    // Loop in charge of printing N columns (Number of propositions) and N rows
    for (int j = 0; j < rows; j++)
    {
        for (int i = 0; i < Main.num_propositions; i++)
        {
            if (j == 0)
                printf("|%-11c|", propositionList[i]);                        // If in row number 1 (Index 0), print characters (Header)
            else if ((((j - 1) >> (Main.num_propositions - i - 1)) & 1) == 0) // Bitwise operation AND with number 1 to print the values of the propositions
            {
                printf("|%-11s|", "V");
            }
            else
                printf("|%-11s|", "F");
        }
        printf("\n");
        for (int z = 0; z < Main.num_propositions; z++)
        {
            printf("%.*s", 15, "-------------"); // Printing hyphens to make table format more appealing
        }
        printf("\n");
    }
}

proposition request_proposition(proposition Main)
{
    Main.rows = pow(2, Main.num_propositions) + 1;
    int rows = pow(2, Main.num_propositions);
    int half = rows / 2;
    for (int x = 0; x < Main.num_propositions; x++)
    {
        int current_value = 0;
        int counter = 0;
        for (int y = 1; y <= Main.rows; y++)
        {
            if (counter < half && current_value == 0)
            {
                strcpy(Main.board[x][y], "false");
                counter++;
            }
            if (counter >= half && current_value == 0)
            {
                counter = 0;
                current_value = 1;
            }
            if (counter < half && current_value == 1)
            {
                strcpy(Main.board[x][y], "true");
                counter++;
            }
            if (counter >= half && current_value == 1)
            {
                counter = 0;
                current_value = 0;
            }
        }
        half = half / 2;
    }
    for (int x = 0; x < Main.num_propositions; x++)
    {
        printf("enter the proposition %d", x);
        ret = scanf("%c", &Main.board[0][x][0]);
        getchar();
    }
    printf("Enter logical operations using the following symbols:\n"
           "- Negation (~), e.g., ~q\n"
           "- Conjunction (&), e.g., p & q\n"
           "- Disjunction (|), e.g., p | q\n"
           "- Implication (->), e.g., p -> q\n"
           "Example: ~q & s -> r | r\n"
           "type exit to finish entering your prepositions");

    int flag = 0;
    char preposition[50];
    while (flag != 1)
    {
        ret = fgets(preposition, 50, stdin);
        if (strcmp(preposition, "exit\n") == 0)
        {
            flag = 1;
        }
    }
}
int buscar_columna(proposition Main, const char *busqueda)
{
    for (int i = 0; i < 100; i++)
    {
        if (strcmp(Main.board[0][i], busqueda) == 0)
        {
            return i;
        }
    }
    return -1;
}
int search_column(proposition Main, const char *search)
{
    for (int i = 0; i < 100; i++)
    {
        if (strcmp(Main.board[0][i], search) == 0)
        {
            return i;
        }
    }
    return -1;
}
proposition conjunction(proposition Main, int col1, int col2, int result_col)
{
    for (int i = 1; i < Main.rows; i++)
    {
        if (strcmp(Main.board[col1][i], "true") == 0 && strcmp(Main.board[col2][i], "true") == 0)
        {
            strcpy(Main.board[result_col][i], "true");
        }
        else
        {
            strcpy(Main.board[result_col][i], "false");
        }
    }
    return Main;
}
proposition disjunction(proposition Main, int col1, int col2, int result_col)
{
    for (int i = 1; i < Main.rows; i++)
    {
        if (strcmp(Main.board[col1][i], "true") == 0 || strcmp(Main.board[col2][i], "true") == 0)
        {
            strcpy(Main.board[result_col][i], "true");
        }
        else
        {
            strcpy(Main.board[result_col][i], "false");
        }
    }
    return Main;
}
proposition implication(proposition Main, int col1, int col2, int result_col)
{
    for (int i = 1; i < Main.rows; i++)
    {
        if (strcmp(Main.board[col1][i], "true") == 0 && strcmp(Main.board[col2][i], "false") == 0)
        {
            strcpy(Main.board[result_col][i], "false");
        }
        else
        {
            strcpy(Main.board[result_col][i], "true");
        }
    }
    return Main;
}
proposition negation(proposition Main, int col, int result_col)
{
    for (int i = 1; i < Main.rows; i++)
    {
        if (strcmp(Main.board[col][i], "true") == 0)
        {
            strcpy(Main.board[result_col][i], "false");
        }
        else
        {
            strcpy(Main.board[result_col][i], "true");
        }
    }
    return Main;
}
void print_table(proposition Main)
{
    for (int i = 0; i < Main.rows; i++)
    { // Loop through each row
        for (int j = 0; j < Main.num_propositions; j++)
        {                                       // Loop through each column
            printf("|%-11s", Main.board[j][i]); // Print each string in the cell with padding for alignment
        }
        printf("|\n"); // New line after each row
    }
}