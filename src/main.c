#include <stdio.h>
#include "database.h"
#include "input_processing.h"
#include "file_management.h"
#include "cli_handler.h"

int main(void) {
    
    Database db = init_database(0, "Main");
    handle_cli(db);


    /*
    initialize_table(&db, "M_Kunden");

    initialize_columns(db.tables[0], INT_TYPE, "id");
    initialize_columns(db.tables[0], STRING_TYPE, "nachname");
    initialize_columns(db.tables[0], STRING_TYPE, "vorname");
    initialize_columns(db.tables[0], INT_TYPE, "alter");
    //initialize_columns(db.tables[0], STRING_TYPE, "mail");
    //initialize_columns(db.tables[0], STRING_TYPE, "adresse");
    //initialize_columns(db.tables[0], FLOAT_TYPE, "brutto-monatsgehalt");

    //insert_row(db.tables[0], "(1, 'Stoermer', 'Dennis', 'de.stoermer@web.de', 23, '37247 Grossalmerode', 2400.)");
    //insert_row(db.tables[0], "(2, 'Stoermer', 'Jan', 'jan.stoermer@web.de', 23, '37247 Grossalmerode', 4000.)");
    //insert_row(db.tables[0], "(3, 'Muehlausen', 'Lucas', 'lucas.muehlhausen@gmx.de', 24, '37247 Grossalmerode', 3500.)");

    // print_table(db.tables[0]);
    */

    return 0;
}