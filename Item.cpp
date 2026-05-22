#include "Item.h"

Item::Item(std::string itemName, int itemDamage)
{
    name = itemName;
    damage = itemDamage;
}

std::string Item::getName()
{
    return name;
}

int Item::getDamage()
{
    return damage;
}