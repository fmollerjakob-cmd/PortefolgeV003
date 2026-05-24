#include "Game.h"
#include <sqlite3.h>
#include <iostream>

#include "Database.h"

/*
git commit -m ""
cd ~/Documents/PortefolgeV003/build
mkdir -p build
cd build
cmake ..
make
./PortefolgeV003

*/

int main()
{
    /*
    Database database;
    database.createTables();

    Character player("TestPlayer");
    player.addMonster(Monster("Hest", 10, 3));
    player.addMonster(Monster("Goblin", 6, 2));

    database.saveCharacter(player);
    */

    Game game;
    game.run();

    return 0;
}


