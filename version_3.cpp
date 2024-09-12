#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<locale.h>
#include<assert.h>
#include<math.h>

// const

enum COMPARE_STATUS // compare
{
    BIGGER  =  1,
    EQUAL   =  0,
    SMALLER = -1,
};

const int LIMIT_LEN = 45;
const int HEIGHT = 14;

COMPARE_STATUS custom_strcmp(char* str_1,int len_1, char* str_2, int len_2); // struct //
int custom_strlen(char* str);
int custom_min(int var_1, int var_2);

int main(void)
{
    setlocale(LC_ALL, "Rus");
    FILE* onegin = fopen("ONEGIN.txt", "r");
    FILE* out_onegin = fopen("OUTPUT_ONEGIN.txt", "w");

    if (onegin == NULL)
    {
        printf("Sorry couldn't read the file\n");
        return 1;
    }

    char* data_ptrs[HEIGHT] = {0};
    int   data_lens[HEIGHT] = {0}; // struct

    for (int i = 0; i < HEIGHT; i++)
    {
        char buffer[LIMIT_LEN] = {0};
        fgets(buffer, LIMIT_LEN, onegin);

        int len = custom_strlen(buffer);
        char* tempor_str = (char*) calloc(len, sizeof(char)); // NULL
        if (tempor_str == NULL)
        {
            printf("Sorry couldn't read the file\n");
            return 1;
        }

        for (int j = 0; j < len; j++)
            tempor_str[j] = buffer[j];

        data_ptrs[i] = tempor_str;
        data_lens[i] = len;
    }

    fclose(onegin);
     
     for (int y = 0; y < HEIGHT; y++)
    {
        int i = 0;
        while(data_ptrs[y][i] != '\0')
        {
            fprintf(out_onegin, "%c", data_ptrs[y][i]);
            i++;
        }
    }
    fprintf(out_onegin,"\n"); 

    char* tempor_ptr = 0;
    int  tempor_len  = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < HEIGHT - 1; j++)
        {
            if (custom_strcmp(data_ptrs[j], data_lens[j], data_ptrs[j+1], data_lens[j+1]) == BIGGER)
            {
                tempor_ptr     = data_ptrs[j];
                data_ptrs[j]   = data_ptrs[j+1];
                data_ptrs[j+1] = tempor_ptr;

                tempor_len    = data_lens[j];
                data_lens[j]   = data_lens[j+1];
                data_lens[j+1] = tempor_len;
            }

        }
    }

    for (int y = 0; y < HEIGHT; y++)
    {
        int i = 0;
        while(data_ptrs[y][i] != '\0')
        {
            fprintf(out_onegin, "%c", data_ptrs[y][i]);
            i++;
        }
    }
    fprintf(out_onegin, "\n");

    for (int i = 0; i < HEIGHT; i ++)
    {
        free(data_ptrs[i]); data_ptrs[i] = NULL;
    }
    fclose(out_onegin);
}

COMPARE_STATUS custom_strcmp(char* const str_1, int len_1, char* const str_2, int len_2)
{
    assert(str_1 != 0);
    assert(str_2 != 0);
    assert(len_1 != NAN);
    assert(len_2 != NAN);

    for (int i = 0; i < custom_min(len_1, len_2); i++)
    {
        if (tolower(str_1[i])-tolower(str_2[i]) > 0)
            return BIGGER;
        if (tolower(str_1[i])-tolower(str_2[i]) < 0)
            return SMALLER;
    }
    return EQUAL;
}

int custom_strlen(char* str)
{
    int count = 0;
    for (int i = 0; i < LIMIT_LEN; i++)
    {
        if (str[i] == '\0')
            return count + 1;
        else count++;
    }
    return count;
}

int custom_min(int var_1, int var_2)
{
    if (var_1 >= var_2)
         return var_2;
    else return var_1;

}

