#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database
{
private:
    //db is a pointer to the SQLite database connection
    sqlite3* db;

public:
    Database();
    ~Database(); //Destructor for deleting objects when done

    void createTables();
};

#endif