#include "Monster.h"
#include <iostream>

Monster::Monster(std::string monsterName, int monsterHp, int monsterStrength)
{
    name = monsterName;
    hp = monsterHp;
    maxHp = monsterHp;
    strength = monsterStrength;
}

bool Monster::isAlive()
{
    if (hp <= 0)
    {
        return false;
    }
    else 
    {
        return true;
    }
}

void Monster::print()
{
    std::cout << name << " HP: " << hp << "/" << maxHp << " Strength: " << strength << std::endl;
}