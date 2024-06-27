Simple Array-Based-In-Memory-Database written in C

Build the program by using the following commands:

```
git clone https://github.com/minetac/dennisdb
cd dennisdb
make
.\build\main.exe
```

The following Commands are available:
- LIST TABLES: To list all loaded Tables
- SELECT: Print the whole Table at once, filter-methods aren't yet implemented
  - Syntax: SELECT *TABLE_NAME*
- CREATE TABLE: SQL-Like Create Statement
  - Syntax:CREATE TABLE *table_name*
  - After that you're prompted with the following instructions: Create Column, end with comma, Semicolon to finish.Syntax: TYPE (int, float, string), name
- LOAD | SAVE
  - Both load and save a whole Database to/from database.dennisDB, located in the root folder. File Location may be changed in file_management.c
- INSERT INTO: SQL-Like insert Statement
  - Syntax: INSERT INTO *TABLE_NAME* VALUES (*value1*, *value2*, *value3*)
  - Strings must be written within Single Quotes ''
- Exit: shuts down the Database (THIS DOES NOT SAVE IT)

Done:
- CLI Commands
- Writing/Reading to/from File

Todo:
- Query with Option to Filter
- CSV Export
