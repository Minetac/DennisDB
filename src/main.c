#include <stdio.h>
#include "database.h"
#include "input_processing.h"
#include "file_management.h"
#include "cli_handler.h"

int main(void) {
    
    Database db = init_database(0, "Main");
    handle_cli(db);

    return 0;
}
