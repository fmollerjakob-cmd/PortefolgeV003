#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "Monster.h"
#include "Grotte.h"
#include "Database.h"

class Game
{
private:
    Character player;
    bool gameRunning;

    Database database;

public:
    Game();
    void run();

private:
    void setupRandom();
    int getRandomBetween(int min, int max);

    void showMainMenu();
    int getMenuChoice();

    void createNewCharacter();
    void startAdventure();
    void battle(Monster enemyMonster);
    void takeMonster(Monster defeatedMonster);

    void startGrotte();

    void saveGame();
    void loadGame();
};

#endif