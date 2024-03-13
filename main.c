#include <stdio.h>
#include <math.h>
#include "fort.h"

void listCreator (int propositions, int rows);

int main(void)
{

    int propositions, rows;
    int propositionList[11] = {80,81,82,83,84,85,86,87,88,89,90}; //Chars de P a Z
    //ft_table_t *table = ft_table_create();
    //ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("¿Cuántas proposiciones vas a evaluar?: \n");
    scanf("%d", &propositions);

    rows = pow(2, propositions) + 1;

    for (int j = 1; j <= rows; j++)
    {
        for (int i = 1; i <= propositions; i++)
        {
            if (j == 1) printf("|%11c|",propositionList[i-1]);
            else printf("|           |");
        }
        printf("\n");
        for (int z = 1; z <= propositions; z++)
        {
            printf("%.*s", 15, "-------------");
        }
        printf("\n");
    }

    //listCreator(propositions,rows-1);
    return 0;
}

// void listCreator (int propositions, int rows){
//     for (int i = 0; i < propositions; i++)
//     {
//         int x[rows];

//         printf(x);
//     }
// }


