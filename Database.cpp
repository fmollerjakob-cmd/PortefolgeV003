#include "Database.h"
#include <iostream>
#include <string>
#include <vector>

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

void Database::saveCharacter(Character& character)
{
    std::string sqlHero =
        "INSERT INTO heroes (name) VALUES ('" + character.getName() + "');";

    sqlite3_exec(db, sqlHero.c_str(), NULL, NULL, NULL);

    int heroId = sqlite3_last_insert_rowid(db);

    std::vector<Monster> monsters = character.getMonsters();

    for (int i = 0; i < monsters.size(); i++)
    {
        std::string sqlMonster =
            "INSERT INTO hero_monsters (hero_id, name, hp, strength) VALUES (" +
            std::to_string(heroId) + ", '" +
            monsters[i].getName() + "', " +
            std::to_string(monsters[i].getHp()) + ", " +
            std::to_string(monsters[i].getStrength()) +
            ");";

        sqlite3_exec(db, sqlMonster.c_str(), NULL, NULL, NULL);
    }

    std::cout << "Character saved to database." << std::endl;
}