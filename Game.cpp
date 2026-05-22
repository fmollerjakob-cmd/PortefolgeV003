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
    while (gameRunning)
    {
        showMainMenu();

        int choice = getMenuChoice();

        if (choice == 1)
        {
            createNewCharacter();
        }
        else if (choice == 2)
        {
            player.print();
        }
        else if (choice == 3)
        {
            startAdventure();
        }
        else if (choice == 4)
        {
            gameRunning = false;
        }
        else
        {
            std::cout << "Invalid choice.\n";
        }
    }

    std::cout << "Game closed.\n";
}

void Game::startAdventure()
{
    
    if (!player.hasAliveMonster())
    {
        std::cout << "No Alive Monsters!";
        return;
    }

    //Freendly Mobs
    Monster* playerMonster = &player.getFirstAliveMonster();


    //Enemy mobs
    Monster enemyMonster("Weak Goblin", 4, 2); //palcefholder before changed

    std::cout << "Choose enemy monster:\n";
    std::cout << "1. Weak Goblin\n";
    std::cout << "2. Strong Goblin\n";
    std::cout << "3. Stronger Goblin\n";
    std::cout << "4. Den staerkeste Goblin\n";
    std::cout << "5. Abe Kongen\n";
    std::cout << "6. Enhjoerning\n";
    std::cout << "7. Return to main menu\n";
    std::cout << "Choose: ";

    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        enemyMonster = Monster("Weak Goblin", 4, 2);
    }
    else if (choice == 2)
    {
        enemyMonster = Monster("Strong Goblin", 8, 3);
    }
    else if (choice == 3)
    {
        enemyMonster = Monster("Stronger Goblin", 10, 4);
    }
    else if (choice == 4)
    {
        enemyMonster = Monster("Den staerkeste Goblin", 15, 5);
    }
    else if (choice == 5)
    {
        enemyMonster = Monster("Abe Kongen", 30, 5);
    }
    else if (choice == 6)
    {
        enemyMonster = Monster("Enhjoerning", 50, 8);
    }
    else if (choice == 7)
    {
        return;
    }
    else
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    std::cout << "Battle starts!" << std::endl;
    std::cout << playerMonster->getName() << " vs " << enemyMonster.getName() << std::endl;

    int playerTurn = getRandomBetween(0,1);

  
    if (playerTurn)
    {
        std::cout << playerMonster->getName() << "'s first turn!" << std::endl;
    }
    else
    {
        std::cout << enemyMonster.getName() << "'s first turn!" << std::endl;
    }
    

    while (playerMonster->isAlive() && enemyMonster.isAlive())
    {
        std::cout << playerMonster->getName() << " HP: " << playerMonster->getHp() << std::endl;
        std::cout << enemyMonster.getName() << " HP: " << enemyMonster.getHp() << std::endl;

        if (playerTurn == 1)
        {
            playerMonster->attack(enemyMonster);

        }
        else
        {
            //Uses the monster object that the pointer points to
            enemyMonster.attack(*playerMonster);

        }
        //This part allows for next friendly monster to be sent into battle if 
        //friendly monsters are left
        if (!playerMonster->isAlive() && player.hasAliveMonster())
        {
            std::cout << playerMonster->getName() << " was defeated!\n";

            playerMonster = &player.getFirstAliveMonster();
            std::cout << playerMonster->getName() << " is sent into battle!\n";
        }

        playerTurn += 1;
        playerTurn = playerTurn % 2;
    }

    if (playerMonster->isAlive())
    {
        std::cout << "\nYou won!" << std::endl;
        takeMonster(enemyMonster);
    }
    else
    {
        std::cout << "\nYou lost!" << std::endl;
    }

    return;
}

void Game::showMainMenu()
{
    std::cout << "MAIN MENU\n";
    std::cout << "1. Create new character\n";
    std::cout << "2. Show character\n";
    std::cout << "3. Start adventure\n";
    std::cout << "4. Exit game\n";
    std::cout << "Choose: ";
}

int Game::getMenuChoice()
{
    int choice;
    std::cin >> choice;
    return choice;
}

void Game::createNewCharacter()
{
    std::string characterName;

    std::cout << "Enter character name: ";
    std::cin >> characterName;

    player = Character(characterName);

    std::cout << "Character created.\n";
    player.print();
}

void Game::takeMonster(Monster defeatedMonster)
{
    std::cout << "Aquire Monster: " << defeatedMonster.getName() << "?\n";
    std::cout << "1. Yes\n";
    std::cout << "2. No\n";
    std::cout << "Choose: ";

    int choice;
    std::cin >> choice;

    if (choice != 1)
    {
        std::cout << defeatedMonster.getName() << " was not added.\n";
        return;
    }

    defeatedMonster.healToFull();

    if (player.hasSpaceForMonster())
    {
        player.addMonster(defeatedMonster);
        std::cout << defeatedMonster.getName() << " was added!\n";
        return;
    }

    std::cout << "NO SPACE! Choose a monster to replace:\n";
    player.print();

    std::cout << "Choose monster number 1-4, or 0 to cancel: ";

    int replace;
    std::cin >> replace;

    if (replace >= 1 && replace <= 4)
    {
        player.replaceMonster(replace - 1, defeatedMonster);
        std::cout << defeatedMonster.getName() << " was added!\n";
    }
    else
    {
        std::cout << defeatedMonster.getName() << " was not added.\n";
    }
}