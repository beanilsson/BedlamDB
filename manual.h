#ifndef MANUAL
#define MANUAL
#include <string>

std::string manual_text = "BedlamDB has two different modes. Overview and Single DB.\n \
\n \
In Overview mode($) the following commands are available : \n \
\n \
* open_db db_name - Enters SingleDB mode by opening a database with name db_name.If no such database exists, one will be created.\n \
* print_db_names - Prints the names of all databases\n \
* delete_db db_name - Deletes the database with name db_name\n \
* quit - Quits the program\n \
* manual - Prints this text\n \
\n \
In Single DB mode(db_name$) the follwing commands are available : \
\n \
* print_content - Prints the entire content of the database (first added entry first)\n \
* print_content_reverse - Prints the entire content of the database in reverse order (last added entry first)\n \
* print_entry my_entry - Prints all entries containing the word my_entry\n \
* insert my_entry - Inserts the data my_entry to the database\n \
* quit - Quits Single DB mode and enters Overview mode\n \
* insert_bulk - Insert more than one entry at the same time. Wrap each entry in a pair of curlybraces, like so: {data}{more data}{cats}\n \
\n \
\n \
All entries are stored in chronological order within the database.";


#endif
