#ifndef GROTTE_H
#define GROTTE_H

#include <string>
#include <vector>
#include "Monster.h"
#include "Item.h"

class Grotte
{
private:
    std::string name;
    std::vector<Monster> monsters;
    Item rewardItem;

public:
    Grotte(std::string grotteNavn, Item reward);

    std::string getName();

    void addMonster(Monster monster);
    int getMonsterCount();

    Monster& getMonster(int index);

    Item getRewardItem();

    void print();
};

#endif