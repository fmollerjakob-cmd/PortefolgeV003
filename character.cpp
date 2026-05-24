#include "character.h"
#include <iostream>
#include <stdexcept>

Character::Character(std::string characterName)
{
    name = characterName;

    //Should always start with 2 horses
    monsters.push_back(Monster("Hest", 6, 6, 2)); //Horse
    monsters.push_back(Monster("Hest", 6, 6, 2));

    totalDefeatedMonsters = 0;
}

bool Character::hasAliveMonster()
{
    for (int i = 0; i < monsters.size(); i++)
    {
        if (monsters[i].isAlive())
        {
            return true;
        }
    }

    return false;
}

void Character::print()
{
    std::cout << "Character: " << name << "\n";
    std::cout << "Monsters:\n";

    for (int i = 0; i < monsters.size(); i++)
    {
        std::cout << i + 1 << ". ";
        monsters[i].print();
    }
}

void Character::addMonster(Monster monster)
{
    if (monsters.size() < 4)
    {
        monsters.push_back(monster);
    }
}

Monster& Character::getFirstAliveMonster()
{
    for (int i = 0; i < monsters.size(); i++)
    {
        if (monsters[i].isAlive())
        {
            return monsters[i];
        }
    }

    throw std::runtime_error("No alive monsters");
}

bool Character::hasSpaceForMonster()
{
    return monsters.size() < 4;
}

void Character::replaceMonster(int index, Monster monster)
{
    if (index >= 0 && index < monsters.size())
    {
        monsters[index] = monster;
    }
}

int Character::getCombinedHp()
{
    int combinedHp = 0;
    
    for (int i = 0; i < monsters.size(); i++)
    {
        combinedHp += monsters[i].getHp();
    }

    return combinedHp;
}

std::string Character::getName()
{
    return name;
}

std::vector<Monster> Character::getMonsters()
{
    return monsters;
}

void Character::addDefeatedMonster()
{
    totalDefeatedMonsters += 1;
}

void Character::printStatistics()
{
    std::cout << "\n\t\tStatistics:"
        << "\nDefeated Monsters: " << totalDefeatedMonsters
        << "\nItems used: \n";
        printItemCounts(usedItems); //for items used

        std::cout << "\nMonsters defeated by item:\n";
        printItemCounts(itemDefeatedMonster); //for items used to defeat monster
        std::cout << std::endl;
}

void Character::addUsedItem(std::string itemName)
{
    usedItems.push_back(itemName);
}

void Character::addItemDefeatedMonster(std::string itemName)
{
    itemDefeatedMonster.push_back(itemName);
}

void Character::printItemCounts(std::vector<std::string> names)
{
    //cloning names vector unto new vector needed
    std::vector<std::string> checkedNames;
    for (int i = 0; i < names.size(); i++)
    {
        checkedNames.push_back(names[i]);
    }

    //checking each name for occurances
    while (checkedNames.size() > 0)
    {
        std::string currentName = checkedNames[0];

        int occuranceCounter = 0;
        
        for (int i = 0; i < names.size(); i++)
        {
            if (names[i] == currentName)
            {
                occuranceCounter += 1;
            }
        }
        std::cout << currentName << "| " << occuranceCounter << std::endl;

        //deleting all occurances from placeholder vector
        int i = 0;
        while (i < checkedNames.size())
        {
            if (checkedNames[i] == currentName)
            {
               checkedNames.erase(checkedNames.begin() + i);
            }
            else{
                i++;
            }
        }
    }
}