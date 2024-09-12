#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<TXLib.h>

enum COMPARISON_STATUS
{
    BIGGER  =  1,
    EQUAL   =  0,
    SMALLER = -1,
};

const int WIDTH = 32;
const int HEIGHT = 15;

int custom_strcmp(char* str_1, char* str_2);
int r_strcmp(const char* str_1, const char* str_2);
void str_swap(char* str_1, char* str_2);

int main(void)
{
    FILE* onegin = fopen("ONEGIN.txt", "r");

    char text[HEIGHT][WIDTH] = {0};
    char* data_ptrs[HEIGHT]  = {0};
    char* adress = &text[0][0];

    for (int i = 0; i < HEIGHT; i++)
    {
        fgets(text[i], WIDTH, onegin);
        data_ptrs[i] = adress;
        adress += WIDTH;

    }

    for (int y = 0; y < HEIGHT; y++)
    {

        for (int i = 0; i < WIDTH; i++)
            printf("%c", data_ptrs[y][i]);

    }
    printf("\n");


    char* tempor_ptr = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < HEIGHT - 1; j++)
        {
            if (custom_strcmp(data_ptrs[j], data_ptrs[j+1]) == BIGGER)
            {
                tempor_ptr     = data_ptrs[j];
                data_ptrs[j] = data_ptrs[j+1];
                data_ptrs[j+1]   = tempor_ptr;
            }

        }
    }

    for (int y = 0; y < HEIGHT; y++)
    {

        for (int i = 0; i < WIDTH; i++)
            printf("%c", data_ptrs[y][i]);
    }
    printf("\n");

    fclose(onegin);
}

int custom_strcmp(char* str_1, char* str_2)
{
    for (int i = 0; i < WIDTH; i++)
    {
        if (str_1[i]-str_2[i] > 0)
            return BIGGER;
        if (str_1[i]-str_2[i] < 0)
            return SMALLER;
    }
    return EQUAL;
}

/*void print_text(char* data_ptrs)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            printf("%c", *(data_ptrs+y*WIDTH+i));
        }
    }

    printf("\n");
}             */

/*int r_strcmp(const char* str_1, const char* str_2)
{
    for (int i = 0; i < WIDTH; i++)
    {
        if (tolower(str_1[i]) = tolower(str_2[i]))
            return 0;
    }
    return 1;
}  */

/*void str_swap(char** str_1, char** str_2)
{
    assert(str_1 != NULL);
    assert(str_2 != NULL);

    char* tempor_ptr = *str_1;
    *str_1 = str_2;
    *str_2 = tempor_ptr;
}   */
