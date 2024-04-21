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
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROPOSITIONS 26
#define MAX_ROWS 1024
#define BUFFER_SIZE 256

// Function prototypes
void initializeTruthTable(bool truthTable[MAX_ROWS][MAX_PROPOSITIONS], int propositions);
void printTruthTable(bool truthTable[MAX_ROWS][MAX_PROPOSITIONS], int propositions, int newCols, char *propositionList);
void processExpression(bool truthTable[MAX_ROWS][MAX_PROPOSITIONS], int rows, int propositions, int *newCols, char *expression, char *propositionList);

int main(void)
{
    int propositions, rows, newCols = 0;
    char propositionList[MAX_PROPOSITIONS];
    bool truthTable[MAX_ROWS][MAX_PROPOSITIONS] = {false};
    char expression[BUFFER_SIZE];

    // Initialize the proposition list from 'p' to available characters
    for (int i = 0; i < MAX_PROPOSITIONS; i++) {
        propositionList[i] = 'p' + i;
    }

    // Ask the user for the number of propositions to evaluate
    printf("How many propositions do you want to evaluate?: \n");
    scanf("%d", &propositions);
    getchar(); // Consume the newline character after scanf

    // Calculate the number of rows in the truth table (2^propositions)
    rows = pow(2, propositions);
    initializeTruthTable(truthTable, propositions);

    // Main interaction loop
    do {
        printTruthTable(truthTable, propositions, newCols, propositionList);

        // Get the user's logical expression
        printf("Enter your logical expression (e.g., '-r ^ p') or type 'exit' to quit:\n");
        fgets(expression, BUFFER_SIZE, stdin);
        expression[strcspn(expression, "\n")] = 0; // Remove the newline character

        if (strcmp(expression, "exit") == 0) {
            break;
        }

        // Process the entered logical expression
        processExpression(truthTable, rows, propositions, &newCols, expression, propositionList);
    } while (true);

    return 0;
}

void initializeTruthTable(bool truthTable[MAX_ROWS][MAX_PROPOSITIONS], int propositions)
{
    int rows = pow(2, propositions);
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < propositions; i++) {
            truthTable[j][i] = ((j >> (propositions - i - 1)) & 1);
        }
    }
}

void printTruthTable(bool truthTable[MAX_ROWS][MAX_PROPOSITIONS], int propositions, int newCols, char *propositionList)
{
    for (int i = 0; i < propositions + newCols; i++) {
        printf("|%-11c|", propositionList[i]);
    }
    printf("\n");

    int rows = pow(2, propositions);
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < propositions + newCols; i++) {
            printf("|%-11s|", truthTable[j][i] ? "True" : "False");
        }
        printf("\n");
    }
}

void processExpression(bool truthTable[MAX_ROWS][MAX_PROPOSITIONS], int rows, int propositions, int *newCols, char *expression, char *propositionList)
{
    // This function will need to parse the expression and apply each operation in sequence.
    // For simplicity, let's assume it only deals with binary operators and single character propositions.
    // A full implementation would need to handle parsing and operator precedence correctly.

    char *token = strtok(expression, " ");
    int lastResultCol = -1;
    
    while (token != NULL) {
        char operator = token[0];
        if (isalpha(operator)) { // If it's a proposition
            lastResultCol = operator - 'p'; // Index of the proposition
        } else if (operator == '-') { // Negation
            token = strtok(NULL, " "); // Get the next token, which should be the proposition to negate
            int index = token[0] - 'p';
            for (int j = 0; j < rows; j++) {
                truthTable[j][propositions + *newCols] = !truthTable[j][index];
            }
            lastResultCol = propositions + *newCols;
            (*newCols)++;
        } else { // Other operators like ^ and v
            char operand = strtok(NULL, " ")[0]; // Get the next token, which should be the proposition
            int operandIndex = operand - 'p';
            for (int j = 0; j < rows; j++) {
                if (operator == '^') {
                    truthTable[j][propositions + *newCols] = truthTable[j][lastResultCol] && truthTable[j][operandIndex];
                } else if (operator == 'v') {
                    truthTable[j][propositions + *newCols] = truthTable[j][lastResultCol] || truthTable[j][operandIndex];
                }
            }
            lastResultCol = propositions + *newCols;
            (*newCols)++;
        }
        token = strtok(NULL, " "); // Move to the next token in the string
    }
}
