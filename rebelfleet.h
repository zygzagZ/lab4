#ifndef __REBELFLEET_H__
#define __REBELFLEET_H__

#include <iostream>
using namespace std;

namespace speed {
	namespace StarCruiser {
		const int min = 99999;
		const int max = 299795;
	}
	const int min = 299796;
	const int max = 2997960;
}

template<typename U, bool aggressive, U min_speed, U max_speed>
class RebelStarship {
	U shield, speed, attackPower;
public:
	using valueType = U;

	constexpr RebelStarship(U _shield, U _speed) 
		: shield(_shield), speed(_speed), attackPower(0)
	{
		static_assert(!aggressive, "Aggressive and no attackPower given!");
		if (_speed < min_speed || _speed > max_speed) {
			throw std::logic_error("Niepoprawna prędkość");
		}
	}

	constexpr RebelStarship(U _shield, U _speed, U _attackPower) 
		: shield(_shield), speed(_speed), attackPower(_attackPower)
	{ 
		static_assert(aggressive, "Not aggressive and attackPower given!");
		if (_speed < min_speed || _speed > max_speed) {
			throw std::logic_error("Niepoprawna prędkość");
		}
	}

	U getAttackPower() const {
		static_assert(aggressive, "Not aggressive!");
		return attackPower;
	}

	constexpr U getShield() const { return shield; }
	constexpr U getSpeed() const { return speed; }
	void takeDamage(U damage) {
		if (shield > damage)
			shield -= damage;
		else
			shield = 0;
	}
};

template<typename U>
using Explorer = RebelStarship<U, false, speed::min, speed::max>;

template<typename U>
using StarCruiser = RebelStarship<U, true, speed::StarCruiser::min, speed::StarCruiser::max>;

template<typename U>
using XWing = RebelStarship<U, true, speed::min, speed::max>;

#endif
