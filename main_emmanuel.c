#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
    int num_propositions;
    int rows;
    int columns;
    char board[100][100][50];
} proposition;

void request_proposition(proposition *Main);

int main(void) {
    proposition Main;
    printf("How many propositions do you want to evaluate? ");
    scanf("%d", &Main.num_propositions);
    getchar();
    Main.columns = Main.num_propositions;
    request_proposition(&Main);

    return 0;
}

int search_column(proposition *Main, char *search) {
    for (int i = 0; i < Main->columns; i++) {
        if (strcmp(Main->board[0][i], search) == 0) {
            return i;
        }
    }
    return -1;
}

proposition conjunction(proposition Main, int col1, int col2, int result_col) {
    for (int i = 1; i < Main.rows; i++) {
        if (strcmp(Main.board[i][col1], "True") == 0 && strcmp(Main.board[i][col2], "True") == 0) {
            strcpy(Main.board[i][result_col], "True");
        } else {
            strcpy(Main.board[i][result_col], "False");
        }
    }
    return Main;
}

proposition disjunction(proposition Main, int col1, int col2, int result_col) {
    for (int i = 1; i < Main.rows; i++) {
        if (strcmp(Main.board[i][col1], "True") == 0 || strcmp(Main.board[i][col2], "True") == 0) {
            strcpy(Main.board[i][result_col], "True");
        } else {
            strcpy(Main.board[i][result_col], "False");
        }
    }
    return Main;
}

proposition implication(proposition Main, int col1, int col2, int result_col) {
    for (int i = 1; i < Main.rows; i++) {
        if (strcmp(Main.board[i][col1], "True") == 0 && strcmp(Main.board[i][col2], "False") == 0) {
            strcpy(Main.board[i][result_col], "False");
        } else {
            strcpy(Main.board[i][result_col], "True");
        }
    }
    return Main;
}

proposition negation(proposition Main, int col, int result_col) {
    for (int i = 1; i < Main.rows; i++) {
        if (strcmp(Main.board[i][col], "True") == 0) {
            strcpy(Main.board[i][result_col], "False");
        } else {
            strcpy(Main.board[i][result_col], "True");
        }
    }
    return Main;
}

void print_table(proposition *Main) {
    for (int i_row = 0; i_row < Main->rows; i_row++) {
        for (int i_column = 0; i_column < Main->columns; i_column++) {
            printf("|%-11s", Main->board[i_row][i_column]);
        }
        printf("|\n");
    }
}

void printMenu(void) {
    printf("Enter logical operations using the following symbols:\n"
           "1 - Negation (~), e.g., ~q\n"
           "2 - Conjunction (&), e.g., p & q\n"
           "3 - Disjunction (|), e.g., p | q\n"
           "4 - Implication (->), e.g., p -> q\n"
           "Type '0' to finish entering your prepositions\n");
}

void request_proposition(proposition *Main) {
    char temp[100];
    int option;
    Main->rows = pow(2, Main->num_propositions) + 1;

    for (int x = 0; x < Main->num_propositions; x++) {
        printf("Enter the proposition %d: ", x);
        scanf(" %s", temp);
        strcpy(Main->board[0][x], temp);
    }

    for (int x = 1; x < Main->rows; x++) {
        for (int y = 0; y < Main->num_propositions; y++) {
            if ((((x - 1) >> (Main->num_propositions - y - 1)) & 1) == 0) {
                strcpy(Main->board[x][y], "True");
            } else {
                strcpy(Main->board[x][y], "False");
            }
        }
    }

    print_table(Main);
    printMenu();
    scanf("%d", &option);

    while (option != 0) {
        char userProposition[50], secondProposition[50];
        int returnedColumnIndex, secondReturnedColumnIndex;
        printf("Enter the operation number: ");
        switch (option) {
            case 1:
                printf("Which proposition would you like to negate? ");
                scanf("%s", userProposition);
                returnedColumnIndex = search_column(Main, userProposition);

                if (returnedColumnIndex != -1) {
                    Main->columns++;
                    *Main = negation(*Main, returnedColumnIndex, Main->columns - 1);
                } else {
                    printf("Proposition not found.\n");
                }
                break;
            case 2:
                printf("Enter the first proposition: ");
                scanf("%s", userProposition);
                printf("Enter the second proposition: ");
                scanf("%s", secondProposition);

                returnedColumnIndex = search_column(Main, userProposition);
                secondReturnedColumnIndex = search_column(Main, secondProposition);

                if (returnedColumnIndex != -1 && secondReturnedColumnIndex != -1) {
                    Main->columns++;
                    *Main = conjunction(*Main, returnedColumnIndex, secondReturnedColumnIndex, Main->columns - 1);
                } else {
                    printf("Propositions not found.\n");
                }
                break;
            case 3:
                printf("Enter the first proposition: ");
                scanf("%s", userProposition);
                printf("Enter the second proposition: ");
                scanf("%s", secondProposition);

                returnedColumnIndex = search_column(Main, userProposition);
                secondReturnedColumnIndex = search_column(Main, secondProposition);

                if (returnedColumnIndex != -1 && secondReturnedColumnIndex != -1) {
                    Main->columns++;
                    *Main = disjunction(*Main, returnedColumnIndex, secondReturnedColumnIndex, Main->columns - 1);
                } else {
                    printf("Propositions not found.\n");
                }
                break;
            case 4:
                printf("Enter the first proposition: ");
                scanf("%s", userProposition);
                printf("Enter the second proposition: ");
                scanf("%s", secondProposition);

                returnedColumnIndex = search_column(Main, userProposition);
                secondReturnedColumnIndex = search_column(Main, secondProposition);

                if (returnedColumnIndex != -1 && secondReturnedColumnIndex != -1) {
                    Main->columns++;
                    *Main = implication(*Main, returnedColumnIndex, secondReturnedColumnIndex, Main->columns - 1);
                } else {
                    printf("Propositions not found.\n");
                }
                break;
        }

        print_table(Main);
        printMenu();
        scanf("%d", &option);
    }
}
