#include<stdio.h>

int main(void)
{
    for (int i = 0; i < 10; i++)
    {
        printf("first_cycle первый цикл\n");
        for (int j = 0; j < 10; j++)
        {
            printf("second cycle второй цикл\n");
            if (i == 1)
                break;
        }
    }
}
