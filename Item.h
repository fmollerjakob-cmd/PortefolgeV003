#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
private:
    std::string name;
    int damage;

public:
    Item(std::string itemName, int itemDamage);

    std::string getName();
    int getDamage();
};

#endif