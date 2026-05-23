#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "Game.h"
#include "Monster.h"
#include "character.h"
#include "Item.h"

/*
Bugs:
WHen not creating a new character, you do not get standart items!
status effect dissapears when friendly mosnter who applied it dies

*/


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
            startGrotte();
        }
        else if (choice == 5)
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

    std::cout << "\n\t\tBattle starts!" << std::endl;
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
            playerMonster->runStatuses();

            //Making sure enemy not dead by status before player turn
            if (!playerMonster->isAlive())
            {
                std::cout << playerMonster->getName() << " was already defeated by status!\n";

            }
            else
            {

                std::cout << "\n\t\tYour turn!\n";
                std::cout << "1. Attack\n";

                if (playerMonster->getItemCount() > 0)
                {
                    std::cout << "2. Use item\n";
                }

                std::cout << "Choose: ";

                int actionChoice;
                std::cin >> actionChoice;

                if (actionChoice == 1)
                {
                    playerMonster->attack(enemyMonster);
                }
                else if (actionChoice == 2 && playerMonster->getItemCount() > 0)
                {
                    std::cout << "\nChoose item:\n";
                    playerMonster->showItems();

                    std::cout << "Choose: ";
                    int itemChoice;
                    std::cin >> itemChoice;

                    itemChoice = itemChoice - 1; //-1 to get item 0 when type 1

                    if (itemChoice >= 0 && itemChoice < playerMonster->getItemCount()) //item within 0 and number of items
                    {
                        Item chosenItem = playerMonster->getItem(itemChoice);

                        std::cout << playerMonster->getName() << " uses " << chosenItem.getName()
                                << " on " << enemyMonster.getName() << " dealing " << chosenItem.getDamage() << " damage.\n";

                        enemyMonster.takeDamage(chosenItem.getDamage());
                        playerMonster->removeItem(itemChoice);
                    }
                    else
                    {
                        std::cout << "Invalid item choice. Normal attack used instead.\n";
                        playerMonster->attack(enemyMonster);
                    }
                }
                else
                {
                    std::cout << "Invalid choice. Normal attack used instead.\n";
                    playerMonster->attack(enemyMonster);
                }
            }
        }
        else
        {
            enemyMonster.runStatuses();
            //Making sure enemy not dead by status before turn
            if (enemyMonster.isAlive())
            {
                enemyMonster.attack(*playerMonster);
            }
            
        }


        //This part allows for next friendly monster to be sent into battle if 
        //friendly monsters are left
        if (!playerMonster->isAlive() && player.hasAliveMonster())
        {
            std::cout << "\n\t\t" << playerMonster->getName() << " was defeated!\n";

            playerMonster = &player.getFirstAliveMonster();
            std::cout << playerMonster->getName() << " is sent into battle!\n";
        }

        playerTurn += 1;
        playerTurn = playerTurn % 2;
    }

    if (playerMonster->isAlive())
    {
        std::cout << "\n\t\t You won!" << std::endl;
        takeMonster(enemyMonster);
    }
    else
    {
        std::cout << "\nYou lost!" << std::endl;
    }

    return;
}

void Game::startGrotte()
{
    if (!player.hasAliveMonster())
    {
        std::cout << "No alive monsters!\n";
        return;
    }

    Grotte chosenGrotte("Small Grotte", Item("Bombe", 10));

    int playerLevel = player.getCombinedHp();
    if (playerLevel < 15)
    {
        chosenGrotte = Grotte("Small Grotte", Item("Koelle", 5));
        chosenGrotte.addMonster(Monster("Cave Rat", 5, 2));
        chosenGrotte.addMonster(Monster("Small Goblin", 7, 2));
        chosenGrotte.addMonster(Monster("Grotte Boss", 12, 3));
    }
    else if (playerLevel < 40)
    {
        chosenGrotte = Grotte("medium Grotte", Item("Gift", 2, "Poisoned", 100, true));
        chosenGrotte.addMonster(Monster("Spider Egg", 0, 0));
        chosenGrotte.addMonster(Monster("Cave Spider", 2, 4));
        chosenGrotte.addMonster(Monster("Cave Spider", 2, 4));
        chosenGrotte.addMonster(Monster("Cave Spider", 2, 4));
        chosenGrotte.addMonster(Monster("Broodmother", 22, 7));
    }
    else 
    {
        chosenGrotte = Grotte("deep Grotte", Item("Bombe", 15));
        chosenGrotte.addMonster(Monster("Piranha", 1, 2));
        chosenGrotte.addMonster(Monster("Piranha", 1, 2));
        chosenGrotte.addMonster(Monster("Alligator", 18, 5));
        chosenGrotte.addMonster(Monster("Denisuchus", 45, 12));
    }

    std::cout << "\nYou enter " << chosenGrotte.getName() << "!\n";

    for (int i = 0; i < chosenGrotte.getMonsterCount(); i++)
    {
        Monster& enemyMonster = chosenGrotte.getMonster(i);

        std::cout << "\nEnemy " << i + 1 << " of " << chosenGrotte.getMonsterCount() << "\n";
        std::cout << enemyMonster.getName() << " appears!\n";

        Monster* playerMonster = &player.getFirstAliveMonster();

        int playerTurn = getRandomBetween(0, 1);

        //This part untill player shift turn is excect copy of the adventure part,
        // in future, make it a function instead of hardcoding
        while (playerMonster->isAlive() && enemyMonster.isAlive())
        {
            std::cout << playerMonster->getName() << " HP: " << playerMonster->getHp() << std::endl;
            std::cout << enemyMonster.getName() << " HP: " << enemyMonster.getHp() << std::endl;

            if (playerTurn == 1)
            {
                playerMonster->runStatuses();

                //Making sure enemy not dead by status before player turn
                if (!playerMonster->isAlive())
                {
                    std::cout << playerMonster->getName() << " was already defeated by status!\n";

                }
                else
                {

                    std::cout << "\n\t\tYour turn!\n";
                    std::cout << "1. Attack\n";

                    if (playerMonster->getItemCount() > 0)
                    {
                        std::cout << "2. Use item\n";
                    }

                    std::cout << "Choose: ";

                    int actionChoice;
                    std::cin >> actionChoice;

                    if (actionChoice == 1)
                    {
                        playerMonster->attack(enemyMonster);
                    }
                    else if (actionChoice == 2 && playerMonster->getItemCount() > 0)
                    {
                        std::cout << "\nChoose item:\n";
                        playerMonster->showItems();

                        std::cout << "Choose: ";
                        int itemChoice;
                        std::cin >> itemChoice;

                        itemChoice = itemChoice - 1; //-1 to get item 0 when type 1

                        if (itemChoice >= 0 && itemChoice < playerMonster->getItemCount()) //item within 0 and number of items
                        {
                            Item chosenItem = playerMonster->getItem(itemChoice);

                            std::cout << playerMonster->getName() << " uses " << chosenItem.getName()
                                    << " on " << enemyMonster.getName() << " dealing " << chosenItem.getDamage() << " damage.\n";

                            enemyMonster.takeDamage(chosenItem.getDamage());
                            playerMonster->removeItem(itemChoice);
                        }
                        else
                        {
                            std::cout << "Invalid item choice. Normal attack used instead.\n";
                            playerMonster->attack(enemyMonster);
                        }
                    }
                    else
                    {
                        std::cout << "Invalid choice. Normal attack used instead.\n";
                        playerMonster->attack(enemyMonster);
                    }
                }
            }
            else
            {
                enemyMonster.runStatuses();
                //Making sure enemy not dead by status before turn
                if (enemyMonster.isAlive())
                {
                    enemyMonster.attack(*playerMonster);
                }
                
            }


            //This part allows for next friendly monster to be sent into battle if 
            //friendly monsters are left
            if (!playerMonster->isAlive() && player.hasAliveMonster())
            {
                std::cout << "\n\t\t" << playerMonster->getName() << " was defeated!\n";

                playerMonster = &player.getFirstAliveMonster();
                std::cout << playerMonster->getName() << " is sent into battle!\n";
            }

            playerTurn += 1;
            playerTurn = playerTurn % 2;
        }

        if (!player.hasAliveMonster())
        {
            std::cout << "\nYou lost in the grotte!\n";
            return;
        }

        std::cout << enemyMonster.getName() << " was defeated!\n";
    }

    std::cout << "\nYou completed the grotte!\n";
    //takeMonster replaced with item
    Item reward = chosenGrotte.getRewardItem();

    std::cout << "You received item: " << reward.getName() << "\n";
    std::cout << "Choose which monster should receive the item:\n";

    player.print();

    std::cout << "Choose monster number: ";

    int monsterChoice;
    std::cin >> monsterChoice;

    if (monsterChoice >= 1 && monsterChoice <= player.monsters.size())
    {
        player.monsters[monsterChoice - 1].addItem(reward);

        std::cout << reward.getName() << " was given to "
                  << player.monsters[monsterChoice - 1].getName() << "!\n";
    }
    else
    {
        std::cout << "Invalid choice. Item was lost.\n";
    }
}


void Game::showMainMenu()
{
    std::cout << "\nMAIN MENU\n";
    std::cout << "1. Create new character\n";
    std::cout << "2. Show character\n";
    std::cout << "3. Start adventure\n";
    std::cout << "4. Enter grotte\n";
    std::cout << "5. Exit game\n";
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

    // starting items
    player.monsters[0].addItem(Item("Bombe", 20));
    player.monsters[0].addItem(Item("Koelle", 5));
    player.monsters[0].addItem(Item("Gift", 2, "Poisoned", 100, true));

    std::cout << "Character created.\n";
    player.print();

    std::cout << "\nItems on first monster:\n";
    player.monsters[0].showItems();
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