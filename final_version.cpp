#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include <sys/stat.h>
#include<string.h>

// TEST COMMENT MAIN

enum COMPARE_STATUS
{
    BIGGER  =  1,
    EQUAL   =  0,
    SMALLER = -1,
};

enum COMPORATOR
{
    STRAIGHT = 1,
    BACKWARD = 0,
};

enum STATUS_OF_OPERATION
{
    SUCCESS = 0,
    FAIL    = 1,
};

typedef COMPARE_STATUS (*func_compare_t)(const void* a, const void* b);

struct ptr_and_len
{
    char* pointer;
    int   length;
};

struct all_inf_file
{
    int rows;
    int text_size;
    char* text;
    const char* ptr_file;
    func_compare_t comporator;
    struct ptr_and_len* pointer_struct;
    struct stat* text_data;
    FILE*  input_file;
    FILE* output_file;
};


void do_sort(const char* file, const char* output_file, COMPORATOR decider);
void read_text_from_file(all_inf_file* FILE);
void write_text_to_file(all_inf_file* FILE);
void my_sort(void* pointer_str, size_t size, size_t element_size, func_compare_t func_compare_str);
COMPARE_STATUS func_compare_str_straight(const void* a, const void* b);
COMPARE_STATUS func_compare_str_backwards(const void* a, const void* b);
int custom_strcount(char* text, int size_of_file);
int custom_min(int var_1, int var_2);
int custom_max(int var_1, int var_2);
STATUS_OF_OPERATION check_ptr(void* pointer);

int main(int argc, char* argv[])
{
    COMPORATOR decider = STRAIGHT;

    if (argc >= 2)
        decider = (strcmp(argv[argc-1], "backwards") == 0)? BACKWARD : STRAIGHT;
    else
        printf("For initiating backwards sorting type in \"backwards\" after calling exe file\n");

    if (decider == BACKWARD)
        printf("Initiating backwards compilation...\n");
    else
        printf("Initiating straight sorting...\n");

    do_sort("ONEGIN.txt", "OUTPUT_ONEGIN.txt", decider);

    printf("READY!\n");

}

void do_sort(const char* file, const char* output_file, COMPORATOR decider)
{
    struct stat text_data = {};
    const char* onegin = file;
    FILE* onegin_file = fopen(file, "rb");
    FILE* out_onegin = fopen(output_file, "wb");

    func_compare_t comporator = NULL;

    if (decider == STRAIGHT)
        comporator = func_compare_str_straight;
    else
        comporator = func_compare_str_backwards;
    
    assert(check_ptr(onegin_file) != FAIL);
    assert(check_ptr(out_onegin)  != FAIL);

    struct all_inf_file file_1 =
    {
        .rows        = 0,
        .text_size   = 0,
        .text        = NULL,
        .ptr_file    = onegin,
        .comporator = comporator,
        .pointer_struct = NULL,
        .text_data   = &text_data,
        .input_file  = onegin_file,
        .output_file = out_onegin,
    };

    read_text_from_file(&file_1);
    
    write_text_to_file(&file_1);
    
    my_sort(file_1.pointer_struct, file_1.rows, sizeof(file_1.pointer_struct[0]), file_1.comporator);
    
    write_text_to_file(&file_1);

    fclose(onegin_file);
    fclose(out_onegin);

    free(file_1.pointer_struct); file_1.pointer_struct  = NULL;
    free(file_1.text); file_1.text = NULL;
}

void read_text_from_file(all_inf_file* file_1)
{
    assert(file_1 != NULL);

    stat(file_1->ptr_file, file_1->text_data);
    file_1->text_size = file_1->text_data->st_size;
    file_1->text = (char*) calloc(file_1->text_size, sizeof(char));

    assert(check_ptr(file_1->text) != FAIL);

    fread(file_1->text, file_1->text_size , sizeof(char), file_1->input_file);
    file_1->rows = custom_strcount(file_1->text, file_1->text_size);

    file_1->pointer_struct = (ptr_and_len*)calloc(file_1->rows, sizeof(char*)+sizeof(int));
    file_1->pointer_struct[0].pointer = &file_1->text[0];

    int index     = 0;
    int count_len = 0;
    int count_current_str = 0;

    for (int i = 0; i < file_1->text_size; i++)
    {
        count_len++;
        if (file_1->text[i] == '\n')
        {
            count_current_str++;
            if (index < file_1->rows - 1)
            {
                file_1->pointer_struct[count_current_str].pointer = &file_1->text[i+1];
            }
            file_1->pointer_struct[index].length = count_len;
            index++;
            count_len = 0;
        }
    }

}

void my_sort(void* pointer_str, size_t size, size_t element_size, func_compare_t func_compare_str)
{
    assert(pointer_str != NULL);
    assert(size != NAN);
    assert(element_size != NAN);

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

COMPARE_STATUS func_compare_str_straight(const void* a, const void* b)
{
    assert(a != NULL);
    assert(b != NULL);

    ptr_and_len* new_a = ((ptr_and_len*)a);
    ptr_and_len* new_b = ((ptr_and_len*)b);

    int i = 0;
    int j = 0;
    
    while ((i < new_a->length) && (j < new_b->length))
    {
        if (!isalnum(*(new_a->pointer + i)))
            i++;
        if (!isalnum(*(new_b->pointer + j)))
            j++;

        if ((tolower(*(new_a->pointer + i))-tolower(*(new_b->pointer + j))) > 0)
            return BIGGER;
        if ((tolower(*(new_a->pointer + i))-tolower(*(new_b->pointer + j))) < 0)
            return SMALLER;
        i++;
        j++;
    }
    return EQUAL;
}

COMPARE_STATUS func_compare_str_backwards(const void* a, const void* b)
{
    assert(a != NULL);
    assert(b != NULL);

    ptr_and_len* new_a = ((ptr_and_len*)a);
    ptr_and_len* new_b = ((ptr_and_len*)b);

    int i = 0;
    int j = 0;
    
    while ((i < new_a->length) && (j < new_b->length))
    {
        if (!isalnum(*(new_a->pointer + new_a->length - 1 - i)))
            i++;
        if (!isalnum(*(new_b->pointer + new_b->length - 1 - j)))
            j++;

        if ((tolower(*(new_a->pointer + new_a->length - 1 - i)) - tolower(*(new_b->pointer + new_b->length - 1 - j))) > 0)
            return BIGGER;
        if ((tolower(*(new_a->pointer + new_a->length - 1 - i)) - tolower(*(new_b->pointer + new_b->length - 1 - j))) < 0)
            return SMALLER;
        i++;
        j++;
    }
    return EQUAL;
}

void write_text_to_file(all_inf_file* file_1)
{
    assert(file_1 != 0);

    for (int y = 0; y < file_1->rows; y++)
    {
        for (int i = 0; i < file_1->pointer_struct[y].length; i++)
        {
            fprintf(file_1->output_file, "%c", file_1->pointer_struct[y].pointer[i]);
        }
    }
    fprintf(file_1->output_file, "\n");
}

int custom_strcount(char* text, int size_of_file)
{
    assert(text != NULL);
    assert(size_of_file != NAN);

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

int custom_max(int var_1, int var_2)
{
    if (var_1 >= var_2)
         return var_1;
    else return var_2;
}

STATUS_OF_OPERATION check_ptr(void* pointer)
{
    if (pointer == NULL)
    {
        printf("Sorry couldn't read the file 3\n");
        return FAIL;
    }
}