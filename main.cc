#include "rebelfleet.h"
#include "imperialfleet.h"
#include "battle.h"
#include <cassert>


int main () {	
    constexpr StarCruiser<unsigned> cruiser(1234, 100000, 11);
	static_assert(cruiser.getShield() == 1234);
	static_assert(cruiser.getSpeed() == 100000);
	static_assert(cruiser.getAttackPower() == 11);

    XWing<float> xwing(100.0f, 300000.0f, 50.0f);
    Explorer<int> explorer(150, 400000);
    DeathStar<long> deathStar(10000, 75);
    TIEFighter<unsigned> fighter(50, 9);
    ImperialDestroyer<int> destroyer(150, 20);

	// cout << e1.getAttackPower() << endl; // błąd kompilacji
	// cout << x1.getAttackPower() << endl;
	 auto battle = SpaceBattle<short, 1, 23,
                              DeathStar<long>,
                              Explorer<int>
                              // TIEFighter<unsigned>,
                              // XWing<float>
                              >
                              (
                              	deathStar,
                                explorer
                                // fighter,
                                // xwing
                              );
	cout << "Imperial: " << battle.countImperialFleet() << endl <<
			"Rebel: " << battle.countRebelFleet() << endl;

	// attack<XWing<uint>, DeathStar<uint>>(x1, ds);

	// attack(deathStar, xwing);
	// battle.attack();
	// attack<DeathStar<uint>, Explo

    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 2);

    battle.tick(2);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(1);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(4);
    assert(battle.countRebelFleet() == 0);
    assert(battle.countImperialFleet() == 1);

    battle.tick(1); // Wypisuje "IMPERIUM WON\n".
}
