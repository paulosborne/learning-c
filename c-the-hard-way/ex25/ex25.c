#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer)
{
    // calloc allocates memory for an array of num objects and initializes them.
    *out_string = calloc(1, max_buffer + 1);
    check_mem(*out_string);

    /*
     * fgets reads at max_buffer characters from stdin and stores them in
     * out_string.
     */
    char *result = fgets(*out_string, max_buffer, stdin);
    check(result != NULL, "Input Error.");

    return 0;

error:
    if(*out_string) free(*out_string);
    *out_string = NULL;
    return -1;
}

int read_int(int *out_int)
{
    char *input = NULL;
    int rc = read_string(&input, MAX_DATA);
    check(rc == 0, "Failed to read number.");

    // atoi - converts string to integer
    *out_int = atoi(input);

    free(input);
    return 0;

error:
    if(input) free(input);
    return -;
}

int read_scan(const char *fmt, ...)
{
    int i = 0;
    int rc = 0;
    int *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;
    int max_buffer = 0;

    /*
     * va_list is a complete object type suitable for holding the information
     * needed by the macros va_start, va_copy, va_arg and va_end
     */
    va_list argp;

    /*
     * va_start macro enables access to the variable arguments following the named
     * argument parm_n
     */
    va_start(argp, fmt);

    for(i = 0; fmt[i] != '\0'; i++) {
        if(fmt[i] == '%') {
            i++;

        }
    }


}
