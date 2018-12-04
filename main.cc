#include "battle.h"

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
                              Explorer<int>,
                              TIEFighter<unsigned>,
                              XWing<float>>(deathStar,
                                            explorer,
                                            fighter,
                                            xwing);
	// attack<XWing<uint>, DeathStar<uint>>(x1, ds);

	attack(deathStar, xwing);
	// battle.attack();
	// attack<DeathStar<uint>, Explorer<uint>>(ds, e1);

	return 0;
}
