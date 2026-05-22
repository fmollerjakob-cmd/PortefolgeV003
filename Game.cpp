#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "Game.h"
#include "Monster.h"
#include "character.h"

Game::Game()
    : player("Unnamed")
{
    gameRunning = true;
    setupRandom();
}


int Game::getRandomBetween(int min, int max)
{
    return min + rand() % (max - min +1);
}

void Game::setupRandom()
{
    srand(time(0) + getpid());
}

void Game::run()
{
    setupRandom();

    std::string characterName;

    std::cout << "Enter character name: " << std::endl;
    std::cin >> characterName;
    Character player(characterName);
    
    //Freendly Mobs
    Monster& playerMonster = player.getFirstAliveMonster();


    //Enemy mobs
    Monster enemyMonster("Weak Goblin", 4, 2);

    std::cout << "Character created: " << characterName << std::endl;
    std::cout << "Your monsters:" << std::endl;
    player.print();

    std::cout << "Battle starts!" << std::endl;
    std::cout << playerMonster.getName() << " vs " << enemyMonster.getName() << std::endl;

    int playerTurn = getRandomBetween(0,1);

  
    if (playerTurn)
    {
        std::cout << playerMonster.getName() << "'s first turn!" << std::endl;
    }
    else
    {
        std::cout << enemyMonster.getName() << "'s first turn!" << std::endl;
    }
    

    while (playerMonster.isAlive() && enemyMonster.isAlive())
    {
        std::cout << playerMonster.getName() << " HP: " << playerMonster.getHp() << std::endl;
        std::cout << enemyMonster.getName() << " HP: " << enemyMonster.getHp() << std::endl;

        if (playerTurn == 1)
        {
            playerMonster.attack(enemyMonster);

        }
        else
        {
            enemyMonster.attack(playerMonster);

        }

        playerTurn += 1;
        playerTurn = playerTurn % 2;
    }

    if (playerMonster.isAlive())
    {
        std::cout << "\nYou won!" << std::endl;
    }
    else
    {
        std::cout << "\nYou lost!" << std::endl;
    }

    return;

}

