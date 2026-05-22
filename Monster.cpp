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

void Monster::healToFull()
{
    hp = maxHp;
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

void Monster::addItem(Item item)
{
    items.push_back(item);
}

void Monster::showItems()
{
    for (int i = 0; i < items.size(); i++)
    {
        std::cout << i + 1 << ". " << items[i].getName() << " - Damage: " << items[i].getDamage() << std::endl;
    }
}

Item Monster::getItem(int a)
{
    return items[a];
}

void Monster::removeItem(int index)
{
    if (index >= 0 && index < items.size())
    {
        items.erase(items.begin() + index);
    }
}

int Monster::getItemCount()
{
    return items.size();
}

void Monster::addStatus(std::string status)
{
    statuses.push_back(status);

    std::cout << name << " has status: " << status << "!\n";
}

void Monster::showStatuses()
{
    if (statuses.size() == 0)
    {
        std::cout << "No statuses.\n";
        return;
    }

    std::cout << "Statuses: ";

    for (int i = 0; i < statuses.size(); i++)
    {
        std::cout << statuses[i] << " ";
    }

    std::cout << std::endl;
}

void Monster::runStatuses()
{
    for (int i = 0; i < statuses.size(); i++)
    {
        if (statuses[i] == "Poisoned")
        {
            std::cout << name << " takes 1 poison damage!\n";
            takeDamage(2);
        }
    }
}