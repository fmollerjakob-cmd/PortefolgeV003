#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include<vector>

#include "Item.h"

class Monster
{
private:
    std::string name;
    int hp;
    int maxHp;
    int strength;

    std::vector<Item> items;

public:
    Monster(std::string monsterName, int monsterHp, int monsterStrength);

    bool isAlive();
    void print();

    void takeDamage(int damage);
    void attack(Monster& enemy);
    void healToFull();

    std::string getName();
    int getHp();
    int getStrength();

    void addItem(Item item);
    void showItems();
    Item getItem(int index);
    int getItemCount();
};

#endif