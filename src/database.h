#ifndef DATABASE_H
#define DATABASE_H

#include "data_structures.h"

Database init_database(int input_id, char input_name[50]);

Table *initialize_table(Database *db, char input_name[50]);

void insert_row(Table *table, char input_string[4096]);

void print_table_list(Database *db);

void print_table(Table *table);

void free_data(Database *db);

void initialize_columns(Table *table, enum col_type col_type, char input_name[50]);

void print_padded_string(char *str, int total_width, enum print_pos position);
void print_padded_int(int num, int total_width, enum print_pos position);
void print_padded_float(float num, int total_width, enum print_pos position);

#endif