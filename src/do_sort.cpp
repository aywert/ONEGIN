#include"do_sort.h"


STATUS_OF_OPERATION do_sort(const char* file, const char* output_file, COMPARATOR decider)
{
    FILE* input_onegin = fopen(file, "rb");
    FILE* output_onegin = fopen(output_file, "wb");

    func_compare_t comparator = NULL;

    if (decider == STRAIGHT)
        comparator = func_compare_str_straight;
    else
        comparator = func_compare_str_backwards;

    if (input_onegin == NULL)
    {
        printf("Sorry couldn't read the file\n"); // perror
        return FAIL;
    }

    if (output_onegin == NULL)
    {
        printf("Sorry couldn't read the file\n");
        return FAIL;
    }

    struct all_inf_file file_1 =
    {
        .rows        = 0,
        .text        = NULL,
        .file_name   = file,
        .comparator  = comparator,
        .string_inf  = NULL,
        .text_data   = {},
        .input_file  = input_onegin,
        .output_file = output_onegin,
    }; // make constructor

    read_text_from_file(&file_1);
    
    write_text_to_file(&file_1); // this should be after 
    
    my_sort(file_1.string_inf, file_1.rows, sizeof(file_1.string_inf[0]), file_1.comparator);

    // according to task, you need to output the original text again after sorting
    
    write_text_to_file(&file_1);

    fclose(input_onegin);
    fclose(output_onegin);

    free(file_1.string_inf); file_1.string_inf  = NULL;
    free(file_1.text); file_1.text = NULL;

    return SUCCESS;
}