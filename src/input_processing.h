#ifndef INPUT_PROCESSING_H
#define INPUT_PROCESSING_H

#include "data_structures.h"

int find_table_id(Database *db, char *input_table_name);
void remove_first_n_chars(char *str, int n);
void trim(char *str);
char **input_text_split(const char input_text[4096]);
int is_integer(const char *str);
int is_float(const char *str);
enum col_type *column_types_from_split(char **input_items);
int compare_input_with_table(Table *table, char input_text[4096]);
void space_to_underscore(char *str);

void add_beginning_char(char *str, char ch);
void add_ending_char(char *str, char ch);

#endif
