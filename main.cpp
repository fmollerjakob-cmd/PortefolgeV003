#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

int getRandomBetween(int min, int max)
{
    return min + rand() % (max - min +1);
}

void setupRandom()
{
    srand(time(0) + getpid());
}

int main()
{
    setupRandom();

    std::string characterName;

    std::cout << "Enter character name: " << std::endl;
    std::cin >> characterName;

    //Freendly Mobs
    std::string playerMonsterName = "Hest";
    int playerMonsterHp = 9;
    int playerMonsterStrength = 1;

    //Enemy mobs
    std::string enemyMonsterName = "Weak Goblin";
    int enemyMonsterHp = 4;
    int enemyMonsterStrength = 2;

    std::cout << "Character created: " << characterName << std::endl;
    std::cout << "You have one monster: " << playerMonsterName << std::endl;

    std::cout << "Battle starts!" << std::endl;
    std::cout << playerMonsterName << " vs " << enemyMonsterName << std::endl;
    
    int playerTurn = getRandomBetween(0,1);

    if (playerTurn)
    {
        std::cout << playerMonsterName << "'s First turn!" << std::endl;
    }
    else
    {
        std::cout << enemyMonsterName << "'s First turn!" << std::endl;
    }
    while (playerMonsterHp > 0 && enemyMonsterHp > 0)
    {
        std::cout << playerMonsterName << " HP: " << playerMonsterHp << std::endl;
        std::cout << enemyMonsterName << " HP: " << enemyMonsterHp << std::endl;

        if (playerTurn == 1)
        {
            enemyMonsterHp = enemyMonsterHp - playerMonsterStrength;

            std::cout << 
            playerMonsterName << " attacks with " << 
            playerMonsterStrength <<
            " damage!" <<
            std::endl;
        }
        else
        {
            playerMonsterHp = playerMonsterHp - enemyMonsterStrength;

            std::cout << 
            enemyMonsterName << " attacks with " << 
            enemyMonsterStrength <<
            " damage!" <<
            std::endl;

        }

        playerTurn += 1;
        playerTurn = playerTurn % 2;
    }

    if (playerMonsterHp > 0)
    {
        std::cout << "\nYou won!" << std::endl;
    }
    else
    {
        std::cout << "\nYou lost!" << std::endl;
    }

    return 0;

}

