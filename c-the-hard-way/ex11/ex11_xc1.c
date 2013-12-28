#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

    int i = argc;
    while(i--) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    i = 4;
    while(i--) {
        printf("state %d: %s\n", i, states[i]);
    }

    return 0;

}
