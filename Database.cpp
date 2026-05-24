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

    clearSave();

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

void Database::clearSave()
{
    std::string sql = 
        "DELETE FROM hero_monsters;"
        "DELETE FROM heroes;";

    sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

}

bool Database::loadCharacter(Character& character)
{
    std::string sqlHero =
        "SELECT id, name FROM heroes LIMIT 1;";

    sqlite3_stmt* stmtHero;

    int result = sqlite3_prepare_v2(db, sqlHero.c_str(), -1, &stmtHero, NULL);

    if (result != SQLITE_OK)
    {
        std::cout << "Could not read save.\n";
        return false;
    }

    if (sqlite3_step(stmtHero) != SQLITE_ROW)
    {
        std::cout << "No saved character found.\n";
        sqlite3_finalize(stmtHero);
        return false;
    }

    int heroId = sqlite3_column_int(stmtHero, 0);

    const unsigned char* nameText = sqlite3_column_text(stmtHero, 1);
    std::string characterName = reinterpret_cast<const char*>(nameText);

    sqlite3_finalize(stmtHero);

    Character loadedCharacter(characterName);

    // clear 2 horsesfrom constructor
    loadedCharacter.monsters.clear();

    std::string sqlMonsters =
        "SELECT name, hp, strength FROM hero_monsters WHERE hero_id = " +
        std::to_string(heroId) + ";";

    sqlite3_stmt* stmtMonsters;

    result = sqlite3_prepare_v2(db, sqlMonsters.c_str(), -1, &stmtMonsters, NULL);

    if (result != SQLITE_OK)
    {
        std::cout << "Could not read saved monsters.\n";
        return false;
    }

    while (sqlite3_step(stmtMonsters) == SQLITE_ROW)
    {
        const unsigned char* monsterNameText = sqlite3_column_text(stmtMonsters, 0);
        std::string monsterName = reinterpret_cast<const char*>(monsterNameText);

        int hp = sqlite3_column_int(stmtMonsters, 1);
        int strength = sqlite3_column_int(stmtMonsters, 2);

        loadedCharacter.addMonster(Monster(monsterName, hp, strength));
    }

    sqlite3_finalize(stmtMonsters);

    character = loadedCharacter;

    std::cout << "Character loaded from database.\n";

    return true;
}