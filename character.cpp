#include "character.h"
#include <iostream>
#include <stdexcept>

Character::Character(std::string characterName)
{
    name = characterName;

    //Should always start with 2 horses
    monsters.push_back(Monster("Hest", 6, 2)); //Horse
    monsters.push_back(Monster("Hest", 6, 2));
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