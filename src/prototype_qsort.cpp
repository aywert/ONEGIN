#include<stdio.h>

const int length_of_array = 8;

int my_qsort(int length, int* array);

int main(void)
{
    int array[length_of_array] = {45, 4, -9, 0, 3, 6, 17, 99};
    my_qsort(length_of_array, array);
    return 0;
}

int my_sort(int length, int* array)
{
    int* pivot_index = &array[(int)length/2];
    int pivot_value  = array[(int)length/2];
    int J = (int)length/2;
    int I = 0;
    int tempor_value = 0;
    for (int i = I; i < length/2; i++)
    {
        if (array[i] > pivot_value)
        {
            for (int j = J; j < length; j++)
            {
                if (array[j] < pivot_value)
                {
                    tempor_value = array[j];
                    array[j] = array[i];
                    array[i] = array[j];
                    J = j + 1;
                    break;
                }
            }
        }
    }

}