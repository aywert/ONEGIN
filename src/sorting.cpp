#include "sorting.h"

void my_sort(void* pointer_str, size_t size, size_t element_size, func_compare_t func_compare_str)
{
    assert(pointer_str != NULL);
    assert(size != NAN);
    assert(element_size != NAN);

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size - 1; j++)
        {
            if (func_compare_str((char*)pointer_str + element_size*j, (char*)pointer_str + element_size*(j + 1)) == BIGGER)
            {
                for (int s = 0; s < element_size; s++)
                {
                    char tempor_ptr = *(((char*)pointer_str + element_size*j) + s);
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

int custom_strcount(char* text, int size_of_file)
{
    assert(text != NULL);
    assert(size_of_file != NAN);

    int count = 0;

    for (int i = 0; i < size_of_file-1; i++)
    {
        if ((text[i] =='\r') && (text[i+1] == '\n')) // do not bully linux users
        {
            count++;
        }
    }
    return count;
}
