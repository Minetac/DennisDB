#include "file_management.h"
#include "data_structures.h"
#include "database.h"
#include "input_processing.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void save_to_file(Database *db) {
    FILE *file = fopen("database.dennisDB", "w");

    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei\n");
        return;
    }


    for (int i = 0; i < MAX_TABLES; i++) {
        if (strlen(db->tables[i]->name) == 0) continue;
        fprintf(file, "Table: %s\n", db->tables[i]->name);
        for (int j = 0; j < db->tables[i]->column_count; j++) {
            int datatype = db->tables[i]->columns[j]->datatype;
            fprintf(file, "%s_%s", (datatype == 0) ? "INT" : (datatype == 1) ? "FLOAT" : "STRING", db->tables[i]->columns[j]->name);
            if (j < db->tables[i]->column_count - 1) {
                fprintf(file, ", ");
            }
        }
        fprintf(file, "\n");

        for (int j = 0; j < db->tables[i]->row_count; j++) {
            for (int k = 0; k < db->tables[i]->column_count; k++) {
                switch (db->tables[i]->columns[k]->datatype) {
                    case INT_TYPE:
                        fprintf(file, "%d", *((int *) db->tables[i]->columns[k]->data + j));
                        break;
                    case FLOAT_TYPE:
                        fprintf(file, "%.2f", *((float *) db->tables[i]->columns[k]->data + j));
                        break;
                    case STRING_TYPE:
                        fprintf(file, "%s", *((char **) db->tables[i]->columns[k]->data + j));
                        break;
                }
                if (k < db->tables[i]->column_count - 1) {
                    fprintf(file, ", ");
                }
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
}


void read_from_file(Database *db) {
    FILE *file = fopen("database.dennisDB", "r");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei\n");
        return;
    }
    
    char line[4096];
    int table_index = 0;
    Table *table;
    while (fgets(line, sizeof(line), file)) {
        //if (line[0] == 'T' && line[1] == 'a' && line[2] == 'b' && line[3] == 'l' && line[4] == 'e' && line[5] == ':') {
        if (strncasecmp(line, "Table:", 6) == 0) {
            if (table_index++ >= MAX_TABLES) {
                printf("Fehler: zu viele Tabelle\n");
                fclose(file);
                return;
            }
            remove_first_n_chars(line, 6);
            trim(line);
            table = initialize_table(db, line);
            
            // Columns einlesen
            fgets(line, sizeof(line), file);

            char *pt;
            pt = strtok (line,",");
            while (pt != NULL) {
                trim(pt);
                printf("Line: %s\n", pt);
                enum col_type type;
                if (strncasecmp(pt, "INT_", 4) == 0) {
                    type = INT_TYPE;
                    remove_first_n_chars(pt, 4);
                } else if (strncasecmp(pt, "FLOAT_", 6) == 0) {
                    type = FLOAT_TYPE;
                    remove_first_n_chars(pt, 6);
                } else if (strncasecmp(pt, "STRING_", 7) == 0) {
                    type = STRING_TYPE;
                    remove_first_n_chars(pt, 7);
                } else {
                    printf("\nCritical Error, could't load file\n");
                    free_data(db);
                    exit(1);
                }
                trim(pt);
                
                initialize_columns(table, type, pt);
                pt = strtok(NULL, ",");
            }
            printf("Table Initialized\nReading Rows...\n\n");
        } else {
            //printf("Reading Line: %s\n", line);
            add_beginning_char(line, '(');
            line[strlen(line) - 1] = ')';
            insert_row(table, line);
        }
    }
    fclose(file);

}

