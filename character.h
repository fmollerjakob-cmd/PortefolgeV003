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

    Character(std::string characterName);

    bool hasAliveMonster();
    void print();
    void addMonster(Monster monster);

    Monster& getFirstAliveMonster();

    bool hasSpaceForMonster();

    void replaceMonster(int index, Monster monster);
};

#endif