#include <stdio.h>
#include <math.h>

int main(void)
{
    int propositions, rows, i, j, k;
    int propositionList[11] = {112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122}; // Chars de "p" a "z"

    printf("¿Cuántas proposiciones vas a evaluar?: \n");
    scanf("%d", &propositions);
    rows = pow(2, propositions) + 1;

    for (int j = 0; j < rows; j++)
    {
        for (int i = 0; i < propositions; i++)
        {
            if (j == 0)
                printf("|%-11c|", propositionList[i]);
            else
                printf("|%-11d|", ((j - 1) >> (propositions - i - 1)) & 1);
        }
        printf("\n");
        for (int z = 0; z < propositions; z++)
        {
            printf("%.*s", 15, "-------------");
        }
        printf("\n");
    }

    return 0;
}
