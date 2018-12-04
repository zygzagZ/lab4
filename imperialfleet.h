#ifndef __IMPERIALFLEET_H__
#define __IMPERIALFLEET_H__
#include "rebelfleet.h"

#include <iostream>
using namespace std;

template<typename U>
class ImperialStarship {
	U shield, attackPower;
public:
	using valueType = U;
	constexpr ImperialStarship(U _shield, U _attackPower) 
		: shield(_shield), attackPower(_attackPower) { }
	constexpr U getShield() const { return shield; }
	constexpr U getAttackPower() const { return attackPower; }
	void takeDamage(U damage) {
		if (shield > damage)
			shield -= damage;
		else
			shield = 0;
	}

	template <class... Args>
	struct attack {
		attack(Args...) {};
	};
	template <class IU, class RU, bool aggressive, bool slow>
	struct attack<ImperialStarship<IU>, RebelStarship<RU, aggressive, slow>> {
		attack(ImperialStarship<IU> &i, RebelStarship<RU, true, slow> &r) {
			r.takeDamage(i.getAttackPower());
			i.takeDamage(r.getAttackPower());
		}
		attack(ImperialStarship<IU> &i, RebelStarship<RU, false, slow> &r) {
			r.takeDamage(i.getAttackPower());
		}
	};
};

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;

template <class...>
struct is_imperial : std::false_type {
	const static bool res = false;
};
template <class... Args>
struct is_imperial<ImperialStarship<Args...>> : std::true_type {
	const static bool res = true;
};

template<typename I, typename R>
inline void attack(I &imperialShip, R &rebelShip) {
	static_assert(is_imperial<I>::res && is_rebel<R>::res, "Złe typy statków!");
	ImperialStarship<int>::attack<I, R>(imperialShip, rebelShip);
}

#endif
