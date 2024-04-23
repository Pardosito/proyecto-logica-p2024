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

typedef struct {
 int num_propositions;
 int rows;
 int columns;
 char voard[1000][1000][50];
} proposition;

int main()
{
    proposition Main;
    printf("How many propositions do you want to evaluate?");
ret = scanf("%d", &Main.num_propositions);
getchar();

    return 0;
}