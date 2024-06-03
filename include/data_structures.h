#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdlib.h>

#define MAX_ROWS 1000
#define MAX_COLS 10
#define STRING_LENGTH 255

enum col_type {
    INT_TYPE,
    STRING_TYPE,
    FLOAT_TYPE
};

enum print_pos {
    LEFT_SIDE, MIDDLE, RIGHT_SIDE
};

typedef struct {
    int id;
    char name[50];
    size_t column_size;
    void *data;
    enum col_type datatype;
    int col_width;
} Column;

typedef struct {
    int id;
    char name[50];
    Column *columns[MAX_COLS];
    int column_count;
    int row_count;
} Table;

typedef struct {
    int id;
    char name[50];
    Table *tables[10];
} Database;

void print_col_type(enum col_type type);

#endif