#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

const int std_len = 32;
const int std_height = 15;

int r_strcmp(char* str_1, char* str_2);

int main(void)
{
    FILE* onegin = fopen("ONEGIN.txt", "r");
    char* text = (char*)calloc(std_len*std_height, sizeof(char));

    for (int i = 0; i < std_height; i++)
    {
        text[i] = getc(onegin);
    }

    fclose(onegin);
    
    for (int i = 0; i < std_height; i++)
    {
        putc(text[i], stdout);
    }
}

int r_strcmp(char* str_1, char* str_2)
{
    int flag = 1;
    for (int i = 0; i < std_len; i++)
    {
        if (tolower(str_1[i]) != tolower(str_2[i]))
            flag = 0;

        if (flag == 0)
            return 0;
    }
    return 1;
}
