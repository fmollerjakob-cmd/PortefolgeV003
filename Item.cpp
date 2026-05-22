#include "Item.h"

Item::Item(std::string itemName, int itemDamage)
{
    name = itemName;
    damage = itemDamage;

    statusName = "";
    statusChance = 0;
    targetEnemy = true;
}

Item::Item(std::string itemName, int itemDamage, std::string itemStatusName, int itemStatusChance, bool itemTargetsEnemy)
{
    name = itemName;
    damage = itemDamage;

    statusName = itemStatusName;
    statusChance = itemStatusChance;
    targetEnemy = itemTargetsEnemy;
}

std::string Item::getName()
{
    return name;
}

int Item::getDamage()
{
    return damage;
}

std::string Item::getStatusName()
{
    return statusName;
}

int Item::getStatusChance()
{
    return statusChance;
}

bool Item::targetsEnemy()
{
    return targetEnemy;
}

bool Item::hasStatus()
{
    return statusName != "";
}