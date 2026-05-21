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

void Monster::takeDamage(int damage)
{
    hp -= damage;

    if (hp < 0)
    {
        hp = 0;
    }
}

void Monster::attack(Monster& enemy)
{
    std::cout << name << " attacks " << enemy.getName() << " with " << strength << " damage.\n";

    enemy.takeDamage(strength);
}

void Monster::print()
{
    std::cout << name << " HP: " << hp << "/" << maxHp << " Strength: " << strength << std::endl;
}

std::string Monster::getName()
{
    return name;
}

int Monster::getHp()
{
    return hp;
}

int Monster::getStrength()
{
    return strength;
}