#include <stdio.h>
#include <math.h>

int main(void)
{

    int i, j, proposiciones, renglones;

    printf("¿Cuántas proposiciones vas a evaluar?: \n");
    scanf("%d", &proposiciones);

    renglones = pow(2, proposiciones) + 1;

    for (j = 1; j <= renglones; j++)
    {
        for (i = 1; i <= proposiciones; i++)
        {
            printf("|          |");
        }
        printf("\n");
        for (int z = 1; z <= proposiciones; z++)
        {
            printf("------------");
        }
        printf("\n");
    }
    return 0;
}
