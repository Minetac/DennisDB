// Project Headers
#include "data_structures.h"
#include "database.h"
#include "input_processing.h"

// C-Headers
#include <stdio.h>
#include <string.h>
#include <math.h>

Database init_database(int input_id, char input_name[50]) {
    Database db;

    strcpy_s(db.name, sizeof(db.name), input_name);
    db.id = input_id;
    for (int i = 0; i < 10; i++) {
        db.tables[i] = (Table *) malloc(sizeof(Table));
        db.tables[i]->id = i;
        strcpy(db.tables[i]->name, "");
        db.tables[i]->row_count = 0;
        db.tables[i]->column_count = 0;
    }

    return db;
}

void initialize_table(Table *table, char input_name[50]) {
    strcpy(table->name, input_name);
    for (int i = 0; i < MAX_COLS; i++) {
        table->columns[i] = NULL;
    }
}

void initialize_columns(Table *table, enum col_type col_type, char input_name[50]) {
    printf("%d", table->column_count);
    if (table->column_count < MAX_COLS) {
        // Allocate Memory for Column Pointer
        table->columns[table->column_count] = (Column *) malloc(sizeof(Column));
        table->columns[table->column_count]->id = table->column_count;
        strcpy(table->columns[table->column_count]->name, input_name);
        if (col_type == INT_TYPE) {
            table->columns[table->column_count]->datatype = INT_TYPE;
            table->columns[table->column_count]->data = (int *) malloc(sizeof(int) * MAX_ROWS);
            
        } else if (col_type == STRING_TYPE) {
            table->columns[table->column_count]->datatype = STRING_TYPE;
            table->columns[table->column_count]->data = (char **) malloc(MAX_ROWS * sizeof(char *));
            for (int i = 0; i < MAX_ROWS; i++) {
                ((char **)table->columns[table->column_count]->data)[i] = malloc(STRING_LENGTH * sizeof(char));
            }
            
        } else if (col_type == FLOAT_TYPE) {
            table->columns[table->column_count]->datatype = FLOAT_TYPE;
            table->columns[table->column_count]->data = (float *) malloc(sizeof(float) * MAX_ROWS);
        }
        table->columns[table->column_count]->col_width = strlen(input_name);
        table->column_count++;
    } else {
        printf("Error: Maximum number of columns reached.\n");
    }
}


void insert_row(Table *table, char input_string[4096]) {
    if (table->row_count < MAX_ROWS) {
        int check = compare_input_with_table(table, input_string);
        if (!check) exit(1);
        char **items = input_text_split(input_string);
        for (int i = 0; i < table->column_count; i++) {
            if (strlen(items[i]) > (size_t) table->columns[i]->col_width) {
                table->columns[i]->col_width = strlen(items[i]);
            }
            switch (table->columns[i]->datatype) {
                case INT_TYPE:
                    ((int *) table->columns[i]->data)[table->row_count] = atoi(items[i]);
                    break;
                case FLOAT_TYPE:
                    ((float *) table->columns[i]->data)[table->row_count] = atof(items[i]);
                    break;
                case STRING_TYPE:
                    ((char **) table->columns[i]->data)[table->row_count] = items[i];
                    break;
                default:
                    printf("Error: Unknown Datatype!\n");
                    exit(1);
            }
            
        }

        table->row_count++;
        
    } else {
        printf("Table is full. Cannot insert row.\n");
    }
}

void free_data(Database *db) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < db->tables[i]->column_count; j++) {
            free(db->tables[i]->columns[j]->data);
            free(db->tables[i]->columns[j]);
            free(db->tables[i]);
        }
    }
    // free(db->tables);
}

void print_table(Table *table) {
    printf("Table: %s\n", table->name);
    printf("|");
    for (int c = 0; c < table->column_count; c++) {
        print_padded_string(table->columns[c]->name, table->columns[c]->col_width, MIDDLE);
    }
    printf("\n");
    
    for (int r = 0; r < table->row_count; r++) {
        printf("|");
        for (int i = 0; i < table->column_count; i++) {
            switch(table->columns[i]->datatype) {
                case INT_TYPE:
                    print_padded_int(((int *) table->columns[i]->data)[r], table->columns[i]->col_width, RIGHT_SIDE);
                    break;
                case FLOAT_TYPE:
                    print_padded_float(((float *) table->columns[i]->data)[r], table->columns[i]->col_width, RIGHT_SIDE);
                    break;
                case STRING_TYPE:
                    print_padded_string(((char **) table->columns[i]->data)[r], table->columns[i]->col_width, LEFT_SIDE);
                    break;
            }
        }
        printf("\n");
    }
}

void print_padded_string(char *str, int total_width, enum print_pos position) {
    int str_len = strlen(str);
    int padding = total_width - str_len;

    if (padding <= 0) {
        printf(" %s ", str);
    } else {
        switch (position) {
            case LEFT_SIDE:
                printf(" %s ", str);
                if (padding > 0) for (int i = 0; i < padding; i++) printf(" ");
                break;
            case MIDDLE:
                if (padding > 0) {
                    if (padding % 2 == 0) {
                        for (int i = 0; i < padding / 2; i++) printf(" ");
                        printf(" %s ", str);
                        for (int i = 0; i < padding / 2; i++) printf(" ");
                    } else {
                        for (int i = 0; i < padding / 2; i++) printf(" ");
                        printf(" %s ", str);
                        for (int i = 0; i < padding / 2 + 1; i++) printf(" ");
                    }
                }
                break;
            case RIGHT_SIDE:
                if (padding > 0) for (int i = 0; i < padding; i++) printf(" ");
                printf(" %s ", str);
                break;
            default:
                printf("Error in Printing Position");
                exit(1);
                break;
        }
    }
    printf("|");
}

void print_padded_int(int num, int total_width, enum print_pos position) {
    int num_width = 1;
    int temp = num;
    while (temp / 10 != 0) {
        num_width++;
        temp /= 10;
    }
    int padding = total_width - num_width;

    if (padding <= 0) {
        printf(" %d ", num);
    } else {
        switch (position) {
            case LEFT_SIDE:
                printf(" %d ", num);
                if (padding > 0) for (int i = 0; i < padding; i++) printf(" ");
                break;
            case MIDDLE:
                if (padding > 0) {
                    for (int i = 0; i < (int) floor((float) padding) / 2; i++) printf(" ");
                    printf(" %d ", num);
                    for (int i = 0; i < (int) ceil((float) padding) / 2; i++) printf(" ");
                }
                break;
            case RIGHT_SIDE:
                if (padding > 0) for (int i = 0; i < padding; i++) printf(" ");
                printf(" %d ", num);
                break;
            default:
                printf("Error in Printing Position");
                exit(1);
                break;
        }
    }
    printf("|");
}

void print_padded_float(float num, int total_width, enum print_pos position) {
    int num_width = snprintf(NULL, 0, "%.2f", num); // Anzahl der Zeichen im Float (einschließlich der Nachkommastellen)
    int padding = total_width - num_width;

    if (padding <= 0) {
        printf(" %.2f ", num);
    } else {
        switch (position) {
            case LEFT_SIDE:
                printf(" %.2f ", num);
                if (padding > 0) for (int i = 0; i < padding; i++) printf(" ");
                break;
            case MIDDLE:
                if (padding > 0) {
                    for (int i = 0; i < (int) floor((float) padding) / 2; i++) printf(" ");
                    printf(" %.2f ", num);
                    for (int i = 0; i < (int) ceil((float) padding) / 2; i++) printf(" ");
                }
                break;
            case RIGHT_SIDE:
                if (padding > 0) for (int i = 0; i < padding; i++) printf(" ");
                printf(" %.2f ", num);
                break;
            default:
                printf("Error in Printing Position");
                exit(1);
                break;
        }
    }
    printf("|");
}