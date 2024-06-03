#ifndef INPUT_PROCESSING_H
#define INPUT_PROCESSING_H

#include "data_structures.h"

void trim(char *str);
char **input_text_split(const char input_text[4096]);
int is_integer(const char *str);
int is_float(const char *str);
enum col_type *column_types_from_split(char **input_items);
int compare_input_with_table(Table *table, char input_text[4096]);

#endif
