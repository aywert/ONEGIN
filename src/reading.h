#ifndef READING

#define READING

#include<stdlib.h>
#include<sys/stat.h>
#include"sorting.h"

enum COMPARATOR
{
    STRAIGHT = 1,
    BACKWARD = 0,
};

enum STATUS_OF_OPERATION
{
    SUCCESS = 0,
    FAIL    = 1,
};

struct all_inf_file
{
    int rows;
    char* text;
    const char* file_name;
    func_compare_t comparator;
    struct ptr_and_len* string_inf;
    struct stat text_data;
    FILE*  input_file;
    FILE* output_file;
};

STATUS_OF_OPERATION read_text_from_file(all_inf_file* FILE);
void write_text_to_file(all_inf_file* FILE);
char* record_inf_from_file(const char* file_name, struct stat* text_data, FILE* input_file);

#endif