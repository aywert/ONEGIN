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
    char* text;
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
void my_qsort(void* pointer_str, size_t size, size_t element_size, int (*func_compare_str)(const void* a, const void* b));
int func_compare_str(const void* a, const void* b);
void sort_lengths(ALL_INF_FILE* FILE_1);
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
        .text        = NULL,
        .ptr_file    = onegin,
        .STR_DATA    = &STR_DATA,
        .text_data   = &TEXT_DATA,
        .input_file  = onegin_file,
        .output_file = out_onegin,
    };

    read_text_from_file(&FILE_1);

    write_text_to_file(&FILE_1);
    
    my_qsort(FILE_1.STR_DATA->pointer_str, FILE_1.rows, sizeof(char*), func_compare_str);
    sort_lengths(&FILE_1);

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

    FILE_1->text = (char*) calloc(FILE_1->text_size, sizeof(char));
    fread(FILE_1->text, FILE_1->text_size , sizeof(char), FILE_1->input_file);

    FILE_1->rows = custom_strcount(FILE_1->text, FILE_1->text_size);

    FILE_1->STR_DATA->pointer_str = (char**)calloc(FILE_1->rows, sizeof(char*));
    FILE_1->STR_DATA->length_str  = (int*)calloc(FILE_1->rows, sizeof(int));

    FILE_1->STR_DATA->pointer_str[0] = &FILE_1->text[0];

    int count_len = 0;
    int index     = 0;

    for (int i = 0; i < FILE_1->text_size; i++)
    {
        count_len++;
        if (FILE_1->text[i] == '\n')
        {
            if (index < FILE_1->rows - 1)
            {
                FILE_1->STR_DATA->pointer_str[index+1] = &FILE_1->text[i+1];
            }

            FILE_1->STR_DATA->length_str[index] = count_len;
            index++;
            count_len = 0;
        }
    }

}

void my_qsort(void* pointer_str, size_t size, size_t element_size, int (*func_compare_str)(const void* a, const void* b))
{
    assert(pointer_str != NULL);

    char tempor_ptr = 0;

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size - 1; j++)
        {
            if (func_compare_str((char*)pointer_str + element_size*j, (char*)pointer_str + element_size*(j + 1)) == BIGGER)
            {
                for (int s = 0; s < element_size; s++)
                {
                    tempor_ptr = 0;
                    tempor_ptr = *(((char*)pointer_str + element_size*j) + s);
                    *(((char*)pointer_str + element_size*j) + s) = *(((char*)pointer_str + element_size*(j+1)) + s);
                    *(((char*)pointer_str + element_size*(j+1)) + s) = tempor_ptr;
                }
            }
        }
    }
}

void sort_lengths(ALL_INF_FILE* FILE_1)
{
    for (int i = 0; i < FILE_1->rows; i++)
    {
        int count_len = 0;
        int j = 0;

        while(FILE_1->STR_DATA->pointer_str[i][j] != '\n')
        {
            count_len++;
            j++;
        }
        //printf("before = %d\n", FILE_1->STR_DATA->length_str[i]);
        FILE_1->STR_DATA->length_str[i] = count_len;
        //printf("after = %d\n", FILE_1->STR_DATA->length_str[i]);
    }
}

int func_compare_str(const void* a, const void* b)
{
    int i = 0;
    while (*((char*)a + i) != '\n' && *((char*)a + i + 1) != '\n')
    {
        if ((tolower(**((char**)a + i))-tolower(**((char**)b + i))) > 0)
            return BIGGER;
        if ((tolower(**((char**)a + i))-tolower(**((char**)b + i))) < 0)
            return SMALLER;
        i++;
    }
    return EQUAL;
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

