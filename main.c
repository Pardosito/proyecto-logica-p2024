/*
Project: Truth table generator
Subject: Logic and Discrete Structures
Professor: Miguel Ángel Ojeda Orozco
Period: Spring 2024

Authors:
- Ethan Gabriel Orozco Madrid
- José Emmanuel Pulido Tinajero
- Ian Eugenio Rodríguez Wong

Current delivery: Part I of III
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
    //Variable initialization
    int propositions, rows, i, j, k;

    //Array holding ASCII values of characters "p" through "z"
    int propositionList[11] = {112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};

    printf("¿Cuántas proposiciones vas a evaluar?: \n");
    scanf("%d", &propositions);

    //Elevating 2 to the power of N (Number of propositions given by the user) and adding 1 to account for the header
    rows = pow(2, propositions) + 1;

    //Loop in charge of printing N columns (Number of propositions) and N rows
    for (int j = 0; j < rows; j++)
    {
        for (int i = 0; i < propositions; i++)
        {
            if (j == 0)
                printf("|%-11c|", propositionList[i]); //If in row number 1 (Index 0), print characters (Header)
            else
                if ((((j-1) >> (propositions - i - 1 )) & 1) == 0)//Bitwise operation AND with number 1 to print the values of the propositions 
                {
                    printf("|%-11s|","V");
                }
                else printf("|%-11s|","F");
        }
        printf("\n");
        for (int z = 0; z < propositions; z++)
        {
            printf("%.*s", 15, "-------------"); //Printing hyphens to make table format more appealing
        }
        printf("\n");
    }

    return 0;
}
