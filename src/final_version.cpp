#include"do_sort.h"
#include<string.h>

int main(int argc, char* argv[])
{
    COMPARATOR decider = STRAIGHT;

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