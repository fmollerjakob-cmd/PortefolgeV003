#include "Database.h"
#include <iostream>

Database::Database()
{
    //opens dataase file
    sqlite3_open("game.db", &db);
}

Database::~Database()
{
    //closes database file
    sqlite3_close(db);
}


void Database::createTables()
{
    //Create table (If that specific table does not already exist)
    //in sqlite3 named heroes with 2 columns id and name
    std::string sql =
        "CREATE TABLE IF NOT EXISTS heroes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS hero_monsters ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "hero_id INTEGER NOT NULL,"
        "name TEXT NOT NULL,"
        "hp INTEGER NOT NULL,"
        "strength INTEGER NOT NULL,"
        "FOREIGN KEY(hero_id) REFERENCES heroes(id)"
        ");";

    //Runs the command above, translated from string for sqlite3 to perform
    sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    std::cout << "Databse tables success" << std::endl;
}