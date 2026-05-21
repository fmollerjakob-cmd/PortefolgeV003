#include <string>
#include <vector>

class Monster
{
public:
    std::string name;
    int hp;
    int maxHp;
    int strength;

    Monster();
    Monster(std::string monsterName, int monsterHp, int monsterStrength);

    bool isAlive();
    void print();
};