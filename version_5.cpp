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

struct ALL_INF_FILE
{
    int rows;
    int text_size;
    const char* ptr_file;
    struct DATA_PER_STR* STR_DATA;
    struct stat* text_data;
    FILE*  input_file;
    FILE* output_file;
};

enum COMPARE_STATUS
{
    BIGGER  =  1,
    EQUAL   =  0,
    SMALLER = -1,
};

void read_text_from_file(ALL_INF_FILE* FILE);
void sort_file(ALL_INF_FILE* FILE);
void write_text_to_file(ALL_INF_FILE* FILE);
COMPARE_STATUS custom_strcmp(char* str_1,int len_1, char* str_2, int len_2);
int custom_strcount(char* text, int size_of_file);
int custom_min(int var_1, int var_2);

int main(void)
{
    struct stat TEXT_DATA = {};
    struct DATA_PER_STR STR_DATA= {0};
    const char* onegin = "ONEGIN.txt";
    FILE* onegin_file = fopen(onegin, "rb");
    FILE* out_onegin = fopen("OUTPUT_ONEGIN.txt", "wb");

    if (onegin_file == NULL)
    {
        printf("Sorry couldn't read the file\n");
        return 1;
    }

    if (out_onegin == NULL)
    {
        printf("Sorry couldn't read the file\n");
        return 1;
    }

    struct ALL_INF_FILE FILE_1 =
    {
        .rows        = 0,
        .text_size   = 0,
        .ptr_file    = onegin,
        .STR_DATA    = &STR_DATA,
        .text_data   = &TEXT_DATA,
        .input_file  = onegin_file,
        .output_file = out_onegin,
    };

    read_text_from_file(&FILE_1);

    write_text_to_file(&FILE_1);

    sort_file(&FILE_1);

    write_text_to_file(&FILE_1);

    fclose(onegin_file);
    fclose(out_onegin);

    free(STR_DATA.pointer_str); STR_DATA.pointer_str = NULL;
    free(STR_DATA.length_str);  STR_DATA.length_str  = NULL;
}

void read_text_from_file(ALL_INF_FILE* FILE_1)
{
    assert(FILE_1 != NULL);

    stat(FILE_1->ptr_file, FILE_1->text_data);

    FILE_1->text_size = FILE_1->text_data->st_size;

    char* text = (char*) calloc(FILE_1->text_size, sizeof(char));
    fread(text, FILE_1->text_size , sizeof(char), FILE_1->input_file);

    FILE_1->rows = custom_strcount(text, FILE_1->text_size);

    FILE_1->STR_DATA->pointer_str = (char**)calloc(FILE_1->rows, sizeof(char*));
    FILE_1->STR_DATA->length_str  = (int*)calloc(FILE_1->rows, sizeof(int));

    FILE_1->STR_DATA->pointer_str[0] = &text[0];

    int count_len = 0;
    int index     = 0;

    for (int i = 0; i < FILE_1->text_size; i++)
    {
        count_len++;
        if (text[i] == '\n')
        {
            if (index < FILE_1->rows - 1)
                FILE_1->STR_DATA->pointer_str[index+1] = &text[i+1];

            FILE_1->STR_DATA->length_str[index] = count_len;
            index++;
            count_len = 0;
        }
    }
}

void sort_file(ALL_INF_FILE* FILE_1)
{
    assert(FILE_1 != 0);
    DATA_PER_STR* STR_DATA = FILE_1->STR_DATA;

    char* tempor_ptr = 0;
    int  tempor_len  = 0;
    for (int i = 0; i < FILE_1->rows; i++)
    {
        for (int j = 0; j < FILE_1->rows  - 1; j++)
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

void write_text_to_file(ALL_INF_FILE* FILE_1)
{
    assert(FILE_1 != 0);
    for (int y = 0; y < FILE_1->rows; y++)
    {
        for (int i = 0; i < FILE_1->STR_DATA->length_str[y]; i++)
        {
            fprintf(FILE_1->output_file, "%c", FILE_1->STR_DATA->pointer_str[y][i]);
        }
    }
    fprintf(FILE_1->output_file, "\n");
}

COMPARE_STATUS custom_strcmp(char* const str_1, int len_1, char* const str_2, int len_2)
{
    assert(str_1 != NULL);
    assert(str_2 != NULL);
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

