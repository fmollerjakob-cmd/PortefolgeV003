#include <string>
#include <vector>
#include "Monster.h"

class Character
{
public:
    std::string name;
    std::vector<Monster> monsters;

    Character();
    Character(std::string characterName);

    bool hasAliveMonster();
    void print();
    void addMonster(Monster monster);
};