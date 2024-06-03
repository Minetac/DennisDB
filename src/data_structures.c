#include "data_structures.h"
#include <stdio.h>

void print_col_type(enum col_type type) {
    switch(type) {
        case INT_TYPE:
            printf("Datatype: Integer\n");
            break;
        case FLOAT_TYPE:
            printf("Datatype: Float\n");
            break;
        case STRING_TYPE:
            printf("Datatype: String\n");
            break;
        default:
            printf("Datatype: Unknown\n");
            break;
    }
}

