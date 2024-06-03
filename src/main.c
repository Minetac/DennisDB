#include <stdio.h>
#include "database.h"
#include "input_processing.h"
#include "file_management.h"

int main(void) {
    Database db = init_database(1, "Main");
    
    initialize_table(db.tables[0], "Kunden");

    initialize_columns(db.tables[0], INT_TYPE, "id");
    initialize_columns(db.tables[0], STRING_TYPE, "nachname");
    initialize_columns(db.tables[0], STRING_TYPE, "vorname");
    initialize_columns(db.tables[0], STRING_TYPE, "mail");
    initialize_columns(db.tables[0], INT_TYPE, "alter");
    initialize_columns(db.tables[0], STRING_TYPE, "adresse");
    initialize_columns(db.tables[0], FLOAT_TYPE, "brutto-monatsgehalt");

    insert_row(db.tables[0], "(1, 'Stoermer', 'Dennis', 'de.stoermer@web.de', 23, '37247 Grossalmerode', 2400.)");
    insert_row(db.tables[0], "(2, 'Stoermer', 'Jan', 'jan.stoermer@web.de', 23, '37247 Grossalmerode', 4000.)");
    insert_row(db.tables[0], "(3, 'Muehlausen', 'Lucas', 'lucas.muehlhausen@gmx.de', 24, '37247 Grossalmerode', 3500.)");

    print_table(db.tables[0]);


    save_to_file(&db);

    


    // Daten Dump
    /*
    for (int i = 4; i < 500; i++) {
        // Berechne die benötigte Puffergröße
        int size = snprintf(NULL, 0, "(%d, 'xxx', 'xxx', 'xxx', %d, 'xxx', %f)", i, i * 2, i * 25.0);

        // Allokiere Speicher für den formatierten String
        char *formatted_string = (char *)malloc(size + 1); // +1 für das Nullterminierungszeichen

        if (formatted_string == NULL) {
            printf("Speicherzuweisung fehlgeschlagen\n");
            return 1;
        }

        // Erstelle den formatierten String
        snprintf(formatted_string, size + 1, "(%d, 'xxx', 'xxx', 'xxx', %d, 'xxx', %f)", i, i * 2, i * 25.0);

        // Rufe die insert_row Funktion auf und übergebe den formatierten String
        insert_row(db.tables[0], formatted_string);

        // Gib den dynamisch allokierten Speicher frei
        free(formatted_string);
    }

    print_table(db.tables[0]);
    */
    return 0;
}