#include <iostream>
using namespace std;

template<typename U>
class ImperialStarship {
    U shield, attackPower;
public:
    using valueType = U;
    ImperialStarship(U shield, U attackPower);
    U getShield() { return shield; }
    U getAttackPower() { return attackPower; }
    void takeDamage(U damage) { shield = max(0, shield - damage); }
};

template<typename U>
ImperialStarship<U>::ImperialStarship(U _shield, U _attackPower)
    : shield(_shield), attackPower(_attackPower) { }

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;

int main () {

    return 0;
}
