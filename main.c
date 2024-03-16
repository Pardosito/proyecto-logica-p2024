#include <stdio.h>
#include <math.h>
#include "fort.h"

// void listCreator (int propositions, int rows);

int main(void)
{

    int propositions, rows, i, j, k;
    int propositionList[11] = {112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122}; // Chars de "p" a "z"
    // ft_table_t *table = ft_create_table();
    // ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("¿Cuántas proposiciones vas a evaluar?: \n");
    scanf("%d", &propositions);
    rows = pow(2, propositions) + 1;

    for (int j = 1; j <= rows; j++)
    {
        for (int i = 1; i <= propositions; i++)
        {
            if (j == 1)
                printf("|%-11c|", propositionList[i - 1]);
            else
                printf("|%-11d|", i);
        }
        printf("\n");
        for (int z = 1; z <= propositions; z++)
        {
            printf("%.*s", 15, "-------------");
        }
        printf("\n");
    }

    //Esta lógica capaz y nos sirve para imprimir sin necesidad de la libreria
    for (i = 0; i <= 1; i++)
    {
        for (j = 0; j <= 1; j++)
        {
            for (k = 0; k <= 1; k++)
            {
                printf("%d %d %d\n", i, j, k);
            }
        }
    }

    return 0;
}
