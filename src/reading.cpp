#include"reading.h"

STATUS_OF_OPERATION read_text_from_file(all_inf_file* file_1)
{
    assert(file_1 != NULL);

    file_1->text = record_inf_from_file(file_1->file_name, &(file_1->text_data), file_1->input_file);

    if (file_1->text == NULL)
    {
        printf("Sorry couldn't read the file!!\n");
        return FAIL;
    }

    file_1->rows = custom_strcount(file_1->text, file_1->text_data.st_size);

    file_1->string_inf = (ptr_and_len*)calloc(file_1->rows, sizeof(char*)+sizeof(int));

    if (file_1->string_inf == NULL)
    {
        printf("Sorry couldn't read the file!\n");
        return FAIL;
    }

    file_1->string_inf[0].pointer = &file_1->text[0];

    int index     = 0;
    int count_len = 0;
    int count_current_str = 0;

    for (int i = 0; i < file_1->text_data.st_size; i++)
    {
        count_len++;
        if (file_1->text[i] == '\n')
        {
            count_current_str++;
            if (index < file_1->rows - 1)
            {
                file_1->string_inf[count_current_str].pointer = &file_1->text[i+1];
            }
            file_1->string_inf[index].length = count_len;
            index++;
            count_len = 0;
        }
    }
    return SUCCESS;

}

void write_text_to_file(all_inf_file* file_1)
{
    assert(file_1 != 0);

    for (int y = 0; y < file_1->rows; y++)
    {
        fprintf(file_1->output_file, "%.*s", file_1->string_inf[y].length, file_1->string_inf[y].pointer);
    }
    putc('\n', file_1->output_file);
}

char* record_inf_from_file(const char* file_name, struct stat* text_data, FILE* input_file)
{
    stat(file_name, text_data);

    char* text = (char*) calloc(text_data->st_size, sizeof(char));
    
    fread(text, text_data->st_size , sizeof(char), input_file);
    return text;
}