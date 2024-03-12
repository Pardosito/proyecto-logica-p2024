#include <stdio.h>
#include <math.h>

int main(void)
{

int i, j,      propositions, renglones;

    printf("¿Cuántas proposiciones vas a evaluar?: \n");
    scanf("%d", &propositions);

    renglones = pow(2, propositions) + 1;

    for (j = 1; j <= renglones; j++)
    {
        for (i = 1; i <= propositions; i++)
        {
            printf("|          |");
        }
        printf("\n");
        for (int z = 1; z <= propositions; z++)
        {
            printf("------------");
        }
        printf("\n");
    }
    return 0;
}
