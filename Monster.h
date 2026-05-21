#include <string>
#include <vector>

class Monster
{
public:
    std::string name;
    int hp;
    int maxHp;
    int strength;

    Monster(std::string monsterName, int monsterHp, int monsterStrength);

    bool isAlive();
    void print();

    void takeDamage(int damage);

    void attack(Monster& enemy);

    std::string getName();

    int getHp();

    int getStrength();

private:
    std::string name;
    int hp;
    int strength;

};