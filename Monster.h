#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster
{
private:
    std::string name;
    int hp;
    int maxHp;
    int strength;

public:
    Monster(std::string monsterName, int monsterHp, int monsterStrength);

    bool isAlive();
    void print();

    void takeDamage(int damage);
    void attack(Monster& enemy);

    std::string getName();
    int getHp();
    int getStrength();
};

#endif