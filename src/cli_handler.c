#include "cli_handler.h"
#include "input_processing.h"
#include "file_management.h"
#include "database.h"
#include <stdio.h>
#include <string.h>

void handle_cli(Database db) {
    char input[INPUT_SIZE];

    //print_table_list(&db);
    //read_input(input, "Wählen Sie eine Tabellen ID: ");

    while (1) {
        read_input(input, "Command: ");
        if (strlen(input) < 4) { printf("Command not valid\n"); continue; }

        // Daten in Tabelle einfügen
        if (strncasecmp(input, "INSERT INTO", 11) == 0) {
            remove_first_n_chars(input, 11);
            trim(input);
            int table_id = find_table_id(&db, input);
            if (table_id == -1) { printf("Table not found!\n"); continue; }
            Table *table = db.tables[table_id];
            remove_first_n_chars(input, strlen(table->name));
            trim(input);
            if (strncasecmp(input, "VALUES", 6) != 0) { printf( "Error in Command: %s\n", input); continue; }
            remove_first_n_chars(input, 6);
            trim(input);
            insert_row(table, input);
            continue;

            
        // Tabellen auflisten
        } else if (strncasecmp(input, "LIST TABLES", 11) == 0) {
            for (int i = 0; i < 10; i++) {
                if (strlen(db.tables[i]->name) > 0) {
                    printf("Table ID: %d, Table Name: %s, Zeilen: %d\n", db.tables[i]->id, db.tables[i]->name, db.tables[i]->row_count);
                }
            }
            continue;

        // SQL-Like Select
        } else if (strncasecmp(input, "SELECT", 6) == 0) {
            remove_first_n_chars(input, 6);
            trim(input);
            int table_id = find_table_id(&db, input);
            if (table_id == -1) { printf("Table not found!\n"); continue; }
            Table *table = db.tables[table_id];
            print_table(table);
            continue;

        // Tabelle erstellen
        } else if (strncasecmp(input, "CREATE TABLE", 12) == 0) {
            remove_first_n_chars(input, 12);
            trim(input);
            if (strlen(input) > 50) { printf("Table name too long!\n"); continue; }
            space_to_underscore(input);
            if (find_table_id(&db, input) != -1) { printf("Table already exists!\n"); continue; }
            Table *table = initialize_table(&db, input);
            do {
                read_input(input, "Create Column, end with comma, Semicolon to finish.\nSyntax: TYPE (int, float, string), name\n");
                trim(input);
                enum col_type column_type;
                if (strncasecmp(input, "int", 3) == 0) {
                    column_type = INT_TYPE;
                    remove_first_n_chars(input, 3);
                } else if (strncasecmp(input, "float", 5) == 0) {
                    column_type = FLOAT_TYPE;
                    remove_first_n_chars(input, 5);
                } else if (strncasecmp(input, "string", 6) == 0) {
                    column_type = STRING_TYPE;
                    remove_first_n_chars(input, 6);
                } else {
                    continue;
                }
                trim(input);
                if (strlen(input) > 50) { printf("Column name too long!\n"); continue; }
                space_to_underscore(input);
                initialize_columns(table, column_type, input);
                
            } while (input[0] != ';');
            continue;

        // Load from File
        } else if (strncasecmp(input, "LOAD", 4) == 0) {
            //read_input(input, "Choose dennisDB file: ");
            trim(input);
            space_to_underscore(input);
            read_from_file(&db);

            
            continue;

        // Save File to database.dennisdb
        } else if (strncasecmp(input, "SAVE", 4) == 0) {
            save_to_file(&db);
            printf("Database Saved to database.dennisDB\n");
            continue;
            
        // Programm beenden, TODO: Speichern
        } else if (strncasecmp(input, "EXIT", 4) == 0) {
            printf("Shutting Down Database!");
            return;
        }
    }
}

void read_input(char *input, char *prompt) {
    do {
        size_t len = 0;
        // Input mit 0 füllen / zurücksetzen
        memset(input, '\0', INPUT_SIZE);
        printf("%s", prompt);
        len = strlen(input);
        if (fgets(input, sizeof(char) * INPUT_SIZE, stdin)) {
            // Entfernen des newline-Charakters, falls vorhanden
            if (len > 0 && input[len-1] == '\n') {
                input[len-1] = '\0';
            }
            //printf("Sie haben eingegeben: %s\n", input);
        } else {
            printf("Fehler beim Lesen der Eingabe, versuche es erneut.\n");
            clearerr(stdin);
        }
        trim(input);
    } while (strlen(input) == 0);
}