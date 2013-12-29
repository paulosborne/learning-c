#include <stdio.h>
// assert.h gives you access to the assert() macro
#include <assert.h>

 // stdlib.h provides general utils for memory mgmt, utils, str conv & rand num
#include <stdlib.h>

// string.h gives you access to string utilities
#include <string.h>


// create a new person struct with 4 elements/properties.
struct Person {
    char *name;
    int age;
    int height;
    int weight;
};


void Person_print(struct Person who)
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);

}

int main(void)
{
    struct Person joe = {"Joe Alex", 32, 64, 140};
    struct Person frank = {"Frank Blank", 20, 72, 180};

    // print them out and where they are in memory
    Person_print(joe);
    Person_print(frank);

    // make everyone age 20 years and then print them again
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;

    Person_print(joe);

    return 0;

}
