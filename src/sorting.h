#ifndef SORTING

#define SORTING

#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<assert.h>

struct ptr_and_len
{
    char* pointer;
    int   length;
};

enum COMPARE_STATUS
{
    BIGGER  =  1,
    EQUAL   =  0,
    SMALLER = -1,
};

typedef COMPARE_STATUS (*func_compare_t)(const void* a, const void* b);

void my_sort(void* pointer_str, size_t size, size_t element_size, func_compare_t func_compare_str);
COMPARE_STATUS func_compare_str_straight(const void* a, const void* b);
COMPARE_STATUS func_compare_str_backwards(const void* a, const void* b);
int custom_strcount(char* text, int size_of_file);
#endif