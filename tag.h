#ifndef TAG_H
#define TAG_H

#include <stdio.h>

/* Operation Status */
typedef enum
{
    e_success,
    e_failure
} Operation;

/* Tag operation type */
typedef enum
{
    e_view,
    e_edit,
    e_help,
    e_unsupported
} Tag;

/* Function Prototypes */
Tag check(char *symbol);
void view_tag(FILE *mp3_ptr);
int edit_tag(FILE *mp3_ptr, int argc, char *argv[]);

#endif