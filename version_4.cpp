#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include <sys/stat.h>
#include <sys/types.h>


struct DATA_PER_STR
{
    char** pointer_str;
    int*    length_str;
};

enum COMPARE_STATUS
{
    BIGGER  =  1,
    EQUAL   =  0,
    SMALLER = -1,
};

COMPARE_STATUS custom_strcmp(char* str_1,int len_1, char* str_2, int len_2); 
int custom_strcount(char* text, int size_of_file);
int custom_min(int var_1, int var_2);

int main(void)
{
    struct stat TEXT_DATA = {};
    
    const char* onegin = "ONEGIN.txt";
    FILE* onegin_file = fopen("ONEGIN.txt", "rb");

    if (onegin_file == NULL)
    {
        printf("Sorry couldn't read the file\n");
        return 1;
    }

    stat(onegin, &TEXT_DATA);
    char* text = (char*) calloc(TEXT_DATA.st_size, sizeof(char));
    fread(text, TEXT_DATA.st_size , sizeof(char), onegin_file);
    FILE* out_onegin = fopen("OUTPUT_ONEGIN.txt", "wb");
   
    int rows = custom_strcount(text, TEXT_DATA.st_size);
    //printf("rows = %d", rows);
    struct DATA_PER_STR STR_DATA= {.pointer_str = (char**)calloc(rows, sizeof(char*)), 
                                   .length_str  = (int*)calloc(rows, sizeof(int))};

    STR_DATA.pointer_str[0] = &text[0];
    
    int count_len = 0;
    int index     = 0;

    for (int i = 0; i < TEXT_DATA.st_size - 1; i++)
    { 
        count_len++;
        if (text[i] == '\n')
        {
            STR_DATA.pointer_str[index+1] = &text[i+1];
            //printf("index = %d\ni - count_len = %d\n\n", index,  i - count_len);
            //printf("%d<MKMLJN%d and index = %d\n", text[i], text[i+1], i);
            STR_DATA.length_str[index] = count_len;
            printf("%d\n", count_len);
            index++;
            count_len = 0;
            if (index == rows)
                break;
        }
        
        
    }
    fclose(onegin_file);

    for (int y = 0; y < rows; y++)
    {
        for (int i = 0; i < STR_DATA.length_str[y]; i++)
        {
            //printf("%d", STR_DATA.length_str[y]);
            fprintf(out_onegin, "%c", STR_DATA.pointer_str[y][i]);
        }
    }
    fprintf(out_onegin, "\n");

    char* tempor_ptr = 0;
    int  tempor_len  = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows - 1; j++)
        {
            if (custom_strcmp(STR_DATA.pointer_str[j], STR_DATA.length_str[j], STR_DATA.pointer_str[j+1], STR_DATA.length_str[j+1]) == BIGGER)
            {
                tempor_ptr     = STR_DATA.pointer_str[j];
                STR_DATA.pointer_str[j]   = STR_DATA.pointer_str[j+1];
                STR_DATA.pointer_str[j+1] = tempor_ptr;

                tempor_len     = STR_DATA.length_str[j];
                STR_DATA.length_str[j]    = STR_DATA.length_str[j+1];
                STR_DATA.length_str[j+1]  = tempor_len;
            }

        }
    }

    for (int y = 0; y < rows;y++)
    {
        for (int i = 0; i < STR_DATA.length_str[y]; i++)
            fprintf(out_onegin, "%c", STR_DATA.pointer_str[y][i]);
    }
    fprintf(out_onegin, "\n");

    fclose(out_onegin);

    free(STR_DATA.pointer_str); STR_DATA.pointer_str = NULL;
    free(STR_DATA.length_str);  STR_DATA.length_str = NULL;
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

int custom_strcount(char* text, int size_of_file)
{
    int count = 0;
    for (int i = 0; i < size_of_file-1; i++)
    {
        if ((text[i] =='\r') && (text[i+1] == '\n'))
            count++;
    }
    return count;
}


int custom_min(int var_1, int var_2)
{
    if (var_1 >= var_2)
         return var_2;
    else return var_1;
}
