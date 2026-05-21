#include "character.h"
#include <iostream>

Character::Character(std::string characterName)
{
    name = characterName;

    //Should always start with 2
    monsters.push_back();
    monsters.push_back();
}

bool Character::hasAliveMonster()
{
    
}

void Character::print()
{
std::cout << name << " HP: " << hp << "/" << maxHp << " Strength: " << strength << std::endl;
}

void Character::addMonster()
{
    
}