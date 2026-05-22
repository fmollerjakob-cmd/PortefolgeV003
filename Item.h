#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
private:
    std::string name;
    int damage;

    std::string statusName;
    int statusChance;
    bool targetEnemy;

public:
    Item(std::string itemName, int itemDamage);

    Item(std::string itemName, int itemDamage, std::string itemStatusName, int itemStatusChance, bool itemTargetsEnemy);

    std::string getName();
    int getDamage();

    std::string getStatusName();
    int getStatusChance();
    bool targetsEnemy();
    bool hasStatus();
};

#endif