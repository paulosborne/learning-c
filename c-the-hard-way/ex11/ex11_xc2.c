#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

    int i = 0;
    while(i < argc) {
        printf("arg %d: %s\n", i, argv[i]);
        i++;
    }

    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas",
        "",""
    };

    int number_of_states = 4;
    i = 0;
    while(i < number_of_states) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }

    return 0;

}
