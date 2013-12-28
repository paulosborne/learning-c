#include <stdio.h>

int main()
{
    int age = 10;
    int height = 72;
    double decimal_age = 10.50;
    char a[] = "posbo";
    char initial = 'p';

    /**
     * d,i - accepts an integer value and converts it to signed decimal
     * notation. The precision specifies the minimum number of digits to
     * be displayed. If the value being converted can be represented in fewer
     * digits, it is expanded with leading zeros. The default precision is 1.
     * The result of converting a zero value with a precision of zero is a
     * null string. Specifying a field width with a zero as a leading character
     * causes the field with value to be padded with leading zeros
     */
    printf("I am %d years old.\n", age); // I am 10 years old.
    printf("I am %d inches tall.\n", height); // I am 72 inches tall.

    /**
     * o - accepts an integer value and converts it to unsigned octal notation
     */
    printf("My octal age is %o\n", age);

    /**
     * u - accepts an integer value and converts it to hexadecimal notation.
     */

    /**
     * f - accepts a float or double value and converts it to decimal notation.
     */
    printf("My decimal age is %3.2f\n", decimal_age); 

    /* e - float or double value and converts it to exponential form. */
    printf("My exponent is %e\n", decimal_age);

    /* c - accepts a value as a string and prints the first character. */
    printf("The first letter of my name is %c\n", initial);

    /**
     * s - accepts a value as a string and prints characters from the string
     * until the end of the string is encountered.
     */
     printf("My name is %s\n", a);

     /**
      * b - accepts a value as a string that may contain backslash escape
      * sequences
      */


    return 0;
}
