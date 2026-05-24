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

    //would probably be better to just add the item name to 
    //a vector when used, and then check if enenywas defeated and 
    //then count specific occurances in that vector when printing.
    int koelleUsed;
    int bombUsed;
    int giftUsed;

    int bombDefeatedMonster;
    int giftDefeatedMonster;
    int koelleDefeatedMonster;

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

    

    void addDefeatedMonster();
    void printStatistics();

};

#endif