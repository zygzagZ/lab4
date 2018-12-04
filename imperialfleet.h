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

	template <class...>
	struct attack {};
	template <class IU, class RU, bool aggressive, RU min_speed, RU max_speed>
	struct attack<ImperialStarship<IU>, RebelStarship<RU, aggressive, min_speed, max_speed>> {
		attack(ImperialStarship<IU> &i, RebelStarship<RU, true, min_speed, max_speed> &r) {
			r.takeDamage(i.getAttackPower());
			i.takeDamage(r.getAttackPower());
		}
		attack(ImperialStarship<IU> &i, RebelStarship<RU, false, min_speed, max_speed> &r) {
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

template<typename I, typename R>
inline void attack(I &imperialShip, R &rebelShip) {
	ImperialStarship<int>::attack<I, R>(imperialShip, rebelShip);
}

#endif
