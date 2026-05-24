#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Monster.h"

class Character
{
public:
    std::string name;
    std::vector<Monster> monsters;

    int totalDefeatedMonsters;

    std::vector<std::string> usedItems;
    std::vector<std::string> itemDefeatedMonster;

    Character(std::string characterName);

    bool hasAliveMonster();
    void print();
    void addMonster(Monster monster);

    Monster& getFirstAliveMonster();

    bool hasSpaceForMonster();

    void replaceMonster(int index, Monster monster);

    int getCombinedHp(); //For checking level of player

    std::string getName();

    std::vector<Monster> getMonsters();

    void addUsedItem(std::string itemName);

    void addItemDefeatedMonster(std::string itemName);

    void addDefeatedMonster();
    void printStatistics();

    void printItemCounts(std::vector<std::string> names);

};

#endif