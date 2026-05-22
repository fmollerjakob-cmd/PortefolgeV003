#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "Monster.h"

class Game
{
private:
    Character player;
    bool gameRunning;

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
};

#endif