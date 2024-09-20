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

void read_text_from_file(FILE* name_of_file, struct stat* TEXT_DATA, struct DATA_PER_STR* STR_DATA);
int sort_file(int rows, DATA_PER_STR* STR_DATA);
int write_text_to_file(int rows, DATA_PER_STR* STR_DATA, FILE* out_file);
COMPARE_STATUS custom_strcmp(char* str_1,int len_1, char* str_2, int len_2);
int custom_strcount(char* text, int size_of_file);
int custom_min(int var_1, int var_2);

int main(void)
{
    struct stat TEXT_DATA = {};
    const char* onegin = "ONEGIN.txt";
    FILE* onegin_file = fopen("ONEGIN.txt", "rb");
    FILE* out_onegin = fopen("OUTPUT_ONEGIN.txt", "wb");

    if (onegin_file == NULL)
    {
        printf("Sorry couldn't read the file_input\n");
        return 1;
    }

    if (out_onegin == NULL)
    {
        printf("Sorry couldn't read the file_out\n");
        return 1;
    }

    stat(onegin, &TEXT_DATA);
    char* text = (char*) calloc(TEXT_DATA.st_size, sizeof(char)); // if (text == NULL)
    fread(text, TEXT_DATA.st_size , sizeof(char), onegin_file);

    int rows = custom_strcount(text, TEXT_DATA.st_size);

    struct DATA_PER_STR STR_DATA= {.pointer_str = (char**)calloc(rows, sizeof(char*)), // NULL
                                   .length_str  = (int*)calloc(rows, sizeof(int))};    // NULL

    read_text_from_file(onegin_file, &TEXT_DATA, &STR_DATA);

    write_text_to_file(rows, &STR_DATA, out_onegin);
    
    sort_file(rows, &STR_DATA);
    
    write_text_to_file(rows, &STR_DATA, out_onegin);

    fclose(onegin_file);
    fclose(out_onegin);
    free(STR_DATA.pointer_str); STR_DATA.pointer_str = NULL;
    free(STR_DATA.length_str);  STR_DATA.length_str = NULL;
}

void read_text_from_file(FILE* name_of_file, struct stat* TEXT_DATA, struct DATA_PER_STR* STR_DATA)
{
    char* text = (char*) calloc(TEXT_DATA->st_size, sizeof(char));
    fread(text, TEXT_DATA->st_size , sizeof(char), name_of_file);
   
    int rows = custom_strcount(text, TEXT_DATA->st_size);

    STR_DATA->pointer_str[0] = &text[0];
    
    int count_len = 0;
    int index     = 0;

    for (int i = 0; i < TEXT_DATA->st_size - 1; i++)
    { 
        count_len++;
        if (text[i] == '\n')
        {
            STR_DATA->pointer_str[index+1] = &text[i+1];
            STR_DATA->length_str[index] = count_len;
            printf("%d\n", count_len);
            index++;
            count_len = 0;
            if (index == rows)
                break;
        }  
    }
}

int sort_file(int rows, DATA_PER_STR* STR_DATA)
{
    char* tempor_ptr = 0;
    int  tempor_len  = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows - 1; j++)
        {
            if (custom_strcmp(STR_DATA->pointer_str[j], STR_DATA->length_str[j], STR_DATA->pointer_str[j+1], STR_DATA->length_str[j+1]) == BIGGER)
            {
                tempor_ptr     = STR_DATA->pointer_str[j];
                STR_DATA->pointer_str[j]   = STR_DATA->pointer_str[j+1];
                STR_DATA->pointer_str[j+1] = tempor_ptr;

                tempor_len     = STR_DATA->length_str[j];
                STR_DATA->length_str[j]    = STR_DATA->length_str[j+1];
                STR_DATA->length_str[j+1]  = tempor_len;
            }

        }
    }
}

int write_text_to_file(int rows, DATA_PER_STR* STR_DATA, FILE* out_file)
{
    for (int y = 0; y < rows; y++)
    {
        for (int i = 0; i < STR_DATA->length_str[y]; i++)
        {
            //printf("%d", STR_DATA.length_str[y]);
            fprintf(out_file, "%c", STR_DATA->pointer_str[y][i]);
        }
    }
    fprintf(out_file, "\n");
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

