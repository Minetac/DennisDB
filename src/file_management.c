#include "file_management.h"
#include "data_structures.h"
#include <stdio.h>
#include <unistd.h>

void save_to_file(Database *db) {
    FILE *file = fopen("database.dennisDB", "w");

    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei\n");
        return;
    }


    for (int i = 0; i < 10; i++) {
        if (strlen(db->tables[i]->name) == 0) continue;
        fprintf(file, "Table: %s\n", db->tables[i]->name);
        fprintf(file, "|");
        for (int j = 0; j < db->tables[i]->column_count; j++) {
            fprintf(file, "%s", db->tables[i]->columns[j]->name);
            if (j < db->tables[i]->column_count - 1) {
                fprintf(file, ", ");
            }
        }
        fprintf(file, "\n");
 
        for (int j = 0; j < db->tables[i]->row_count; j++) {
            fprintf(file, "|");
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

/*
void read_from_file(Database *db) {
    FILE *file = fopen("database.dennisDB", "r");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei\n");
        return;
    }
    char line[100];
    int table_index = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'T' && line[1] == 'a' && line[2] == 'b' && line[3] == 'l' && line[4] == 'e' && line[5] == ':') {
            // Neue Tabelle erkannt
            table_index++;
            if (table_index >= 10) {
                printf("Fehler: zu viele Tabelle\n");
                fclose(file);
                return;
            }
            db->tables[table_index] = (Table *)malloc(sizeof(Table));
            db->tables[table_index]->name = (char *)malloc(sizeof(char) * 20);
            db->tables[table_index]->columns = (Column **)malloc(sizeof(Column *) * 10);
            db->tables[table_index]->row_count = 0;
            db->tables[table_index]->column_count = 0;
        }
    }
    fclose(file);

}
*/