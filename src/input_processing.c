#include "input_processing.h"
#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STRING_LENGTH 255
#define MAX_COLS 10

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
