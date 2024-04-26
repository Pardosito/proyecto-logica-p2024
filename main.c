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

proposition request_proposition(proposition Main);

int main()
{
    proposition Main;
    printf("How many propositions do you want to evaluate?");
    ret = scanf("%d", &Main.num_propositions);
    getchar();
    Main.columns = Main.num_propositions;
    request_proposition(Main);

    return 0;
}

int search_column(proposition Main, char *search)
{
    for (int i = 0; i < 100; i++)
    {
        if (Main.board[0][i] == search)
        {
            return i;
            break;
        }
    }
    return -1;
}

// void compareStrings(char* x, char* y)
// {
//     int flag = 0;
 
//     // Iterate a loop till the end
//     // of both the strings
//     while (*x != '\0' || *y != '\0') {
//         if (*x == *y) {
//             x++;
//             y++;
//         }
 
//         // If two characters are not same
//         // print the difference and exit
//         else if ((*x == '\0' && *y != '\0')
//                  || (*x != '\0' && *y == '\0')
//                  || *x != *y) {
//             flag = 1;
//             printf("Unequal Strings\n");
//             break;
//         }
//     }
 
//     // If two strings are exactly same
//     if (flag == 0) {
//         printf("Equal Strings\n");
//     }
// }

proposition conjunction(proposition Main, int col1, int col2, int result_col)
{
    for (int i = 1; i < Main.rows; i++)
    {
        if (strcmp(Main.board[col1][i], "true\0") == 0 && strcmp(Main.board[col2][i], "true\0") == 0)
        {
            strcpy(Main.board[result_col][i], "true\0");
        }
        else
        {
            strcpy(Main.board[result_col][i], "false\0");
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
        if (strcmp(Main.board[i][col], "true") == 0)
        {
            strcpy(Main.board[i][result_col], "false");
        }
        else
        {
            strcpy(Main.board[i][result_col], "true");
        }
    }
    return Main;
}

void print_table(proposition Main)
{
    for (int i_row = 0; i_row < Main.rows; i_row++)
    {
        for (int i_column = 0; i_column < Main.num_propositions; i_column++)
        {
            printf("|%-11s", Main.board[i_row][i_column]);
        }
        printf("\n");
    }
}

proposition request_proposition(proposition Main)
{
    int option;
    Main.rows = pow(2, Main.num_propositions) + 1;

    for (int x = 0; x < Main.num_propositions; x++)
    {
        printf("enter the proposition %d: ", x);
        ret = scanf("%c", &Main.board[0][x][0]);
        getchar();
        fflush(stdin);
    }

    for (int x = 1; x < Main.rows; x++)
    {
        for (int y = 0; y < Main.num_propositions; y++)
        {
            if ((((x - 1) >> (Main.num_propositions - y - 1)) & 1) == 0) // Bitwise operation AND with number 1 to print the values of the propositions
            {
                strcpy(Main.board[x][y], "True\0");
            }
            else
            {
                strcpy(Main.board[x][y], "False\0");
            }
        }
    }
    printf("\n");
    print_table(Main);
    printf("\n");

    printf("Enter logical operations using the following symbols:\n"
           "1 - Negation (~), e.g., ~q\n"
           "2 - Conjunction (&), e.g., p & q\n"
           "3 - Disjunction (|), e.g., p | q\n"
           "4 - Implication (->), e.g., p -> q\n"
           "Type '0' to finish entering your prepositions\n");

    scanf("%d", &option);

    while (option != 0)
    {
        switch (option)
        {
            char proposition, secondProposition;
        case 1:
            printf("Which proposition would you like to negate? ");
            fflush(stdin);
            scanf("%c", &proposition);
            getchar();

            int returnedColumnIndex = search_column(Main, &proposition);
            printf("%d", returnedColumnIndex);
            
            if (returnedColumnIndex != -1)
            {
                negation(Main, returnedColumnIndex, (Main.columns + 1));
                Main.columns += 1;
                print_table(Main);
            }
            else
            {
                printf("Proposition not found.\n");
            }
            break;

        case 2:
            printf("Enter the first proposition: ");
            scanf("%c", &proposition);
            getchar();
            printf("Enter the second proposition: ");
            scanf("%c", &secondProposition);
            getchar();

            conjunction(Main, proposition, secondProposition, (Main.columns + 1));
            print_table(Main);
            break;

        default:
            break;
        }

        printf("Enter logical operations using the following symbols:\n"
               "1 - Negation (~), e.g., ~q\n"
               "2 - Conjunction (&), e.g., p & q\n"
               "3 - Disjunction (|), e.g., p | q\n"
               "4 - Implication (->), e.g., p -> q\n"
               "Type '0' to finish entering your prepositions\n");

        scanf("%d", &option);
    }
}