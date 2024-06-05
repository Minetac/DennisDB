#include "input_processing.h"
#include "database.h"
#include "data_structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_COLS 10

int find_table_id(Database *db, char *input_table_name) {
    for (int i = 0; i < MAX_TABLES; i++) {
        if (strlen(db->tables[i]->name) <= 0) continue;
        if (strncasecmp(input_table_name, db->tables[i]->name, strlen(db->tables[i]->name)) == 0) {
            //printf("Matches! \n");
            return i;
        }
    }
        
    return -1;
}

void remove_first_n_chars(char *str, int n) {
    int len = strlen(str);
    if (n > len) str[0] = '\0';
    else {
        for (int i = 0; i < len - n; i++) {
            str[i] = str[i + n];
        }
        // Nullterminierung des Strings
        str[len - n] = '\0';
    }
}

void trim(char *str) {
    int start = 0;
    int end = strlen(str) - 1;

    // Leerzeichen am Anfang überspringen
    while (isspace((unsigned char)str[start])) start++;

    // Leerzeichen am Ende überspringen
    while (end > start && isspace((unsigned char)str[end])) end--;

    // Teilstring ohne Leerzeichen erstellen
    int length = end - start + 1;
    memmove(str, str + start, length);
    str[length] = '\0';
}

// TODO: Pointer input_text wäre besser
int compare_input_with_table(Table *table, char input_text[4096]) {
    char **items = input_text_split(input_text);
    enum col_type *types = column_types_from_split(items);

    for (int i = 0; i < table->column_count; i++) {
        if (types[i] != table->columns[i]->datatype) {
            printf("Error: Datatypes do not match.\n");
            free(items);
            free(types);
            exit(1);
        }
    }
    free(items);
    free(types);
    
    return 1;
}


// TODO: Pointer wäre besser
char **input_text_split(const char input_text[4096]) {
    char **items = (char **)malloc(sizeof(char *) * MAX_COLS);
    int item_count = 0;
    const char *start = input_text + 1;  // Überspringen der ersten '('
    const char *end;

    while ((end = strchr(start, ',')) != NULL || (end = strchr(start, ')')) != NULL) {
        int len = end - start;
        items[item_count] = (char *)malloc(len + 1);
        strncpy(items[item_count], start, len);
        items[item_count][len] = '\0';  // Null-terminierung des Strings
        trim(items[item_count]);  // Aufruf der trim Funktion, um Leerzeichen zu entfernen
        item_count++;
        start = end + 1;
        if (*end == ')') break;
    }

    items[item_count] = NULL;  // Null-Terminierung des Arrays
    return items;
}

enum col_type *column_types_from_split(char **input_items) {
    enum col_type *types = (enum col_type *) malloc(sizeof(enum col_type) * MAX_COLS);
    for (int i = 0; i < MAX_COLS; i++) {
        if (input_items[i] == NULL) continue;
        
        if (is_integer(input_items[i])) {
            types[i] = INT_TYPE;
        } else if (is_float(input_items[i])) {
            types[i] = FLOAT_TYPE;
        } else {
            types[i] = STRING_TYPE;
        }
    }

    return types;
}

int is_integer(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    // Überprüfen, ob das gesamte String in eine Ganzzahl umgewandelt wurde
    return *endptr == '\0';
}

int is_float(const char *str) {
    char *endptr;
    strtof(str, &endptr);
    // Überprüfen, ob das gesamte String in eine Gleitkommazahl umgewandelt wurde
    return *endptr == '\0';
}

void space_to_underscore(char *str) {
    //printf("Old String: %s\n", str);
    int start = 0;
    int end = strlen(str) - 1;

    while (str[start] != '\0' && start < end) {
        if (isspace((unsigned char)str[start])) str[start] = '_';
        start++;
    }
    //printf("New String: %s\n", str);
}


void add_beginning_char(char *str, char ch) {
    int len = strlen(str);
    memmove(str + 1, str, len + 1);
    str[0] = ch;
}

void add_ending_char(char *str, char ch) {
    int len = strlen(str);
    str[len] = ch;
    str[len + 1] = '\0';
}