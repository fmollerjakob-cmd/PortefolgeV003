#include "Grotte.h"
#include <iostream>

Grotte::Grotte(std::string grotteNavn, Item reward)
    : rewardItem(reward)
{
    name = grotteNavn;
}

std::string Grotte::getName()
{
    return name;
}

void Grotte::addMonster(Monster monster)
{
    monsters.push_back(monster);
}

int Grotte::getMonsterCount()
{
    return monsters.size();
}

Monster& Grotte::getMonster(int index)
{
    return monsters[index];
}

Item Grotte::getRewardItem()
{
    return rewardItem;
}

void Grotte::print()
{
    std::cout << name << "\n";

    for (int i = 0; i < monsters.size(); i++)
    {
        std::cout << i + 1 << ". ";
        monsters[i].print();
    }

    std::cout << "Reward: " << rewardItem.getName() << "\n";
}