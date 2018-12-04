#include "battle.h"

int main () {
	constexpr StarCruiser<uint> s1(100, 99999, 50);
	static_assert(s1.getShield() == 100);
	
	Explorer<uint> e1(100, 300000);
    XWing<uint> x1(100, 300000, 50);
    // constexpr XWing<uint> xwing2(100, 200000, 50); // błąd kompilacji - za wolny
	// Explorer<uint> e2(100, 100, 100); // błąd kompilacji - podany attackPower

	DeathStar<uint> ds(100, 50);
	attack(ds, x1);
	attack<DeathStar<uint>, Explorer<uint>>(ds, e1);
	// cout << e1.getAttackPower() << endl; // błąd kompilacji
	cout << x1.getAttackPower() << endl;
	// attack<XWing<uint>, DeathStar<uint>>(x1, ds);

	return 0;
}
