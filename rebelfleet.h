#ifndef __REBELFLEET_H__
#define __REBELFLEET_H__

#include <iostream>
using namespace std;

namespace speed {
	namespace slow {
		const int min = 99999;
		const int max = 299795;
	}
	const int min = 299796;
	const int max = 2997960;
}

template<typename U, bool aggressive, bool slow>
class RebelStarship {
	U shield, speed, attackPower;

	constexpr void checkSpeed() const {
		if (slow ? (speed < speed::slow::min || speed > speed::slow::max) 
				 : (speed < speed::min || speed > speed::max))
			throw std::logic_error("Wrong speed");
	}
public:
	using valueType = U;

	constexpr RebelStarship(U _shield, U _speed) 
		: shield(_shield), speed(_speed), attackPower(0)
	{
		static_assert(!aggressive, "Aggressive and no attackPower given!");
		checkSpeed();
		
	}

	constexpr RebelStarship(U _shield, U _speed, U _attackPower) 
		: shield(_shield), speed(_speed), attackPower(_attackPower)
	{ 
		static_assert(aggressive, "Not aggressive and attackPower given!");
		checkSpeed();
	}

	constexpr U getAttackPower() const {
		static_assert(aggressive, "Not aggressive!");
		return attackPower;
	}

	constexpr U getShield() const { return shield; }
	constexpr U getSpeed() const { return speed; }
	constexpr void takeDamage(U damage) {
		cout << "TakeDamage(" << damage << ") of " << typeid(decltype(*this)).name() << endl;
		if (shield > damage)
			shield -= damage;
		else
			shield = 0;
	}
};

template<typename U>
using Explorer = RebelStarship<U, false, false>;

template<typename U>
using StarCruiser = RebelStarship<U, true, true>;

template<typename U>
using XWing = RebelStarship<U, true, false>;

template <class...>
struct is_rebel_ : std::false_type {
	const static bool res = false;
};
template <class U, bool aggressive, bool slow>
struct is_rebel_<RebelStarship<U, aggressive, slow>> : std::true_type {
	const static bool res = true;
};

template <class...>
struct is_rebel : std::false_type {
	const static bool res = false;
};
template <class T>
struct is_rebel<T> : is_rebel_
	<typename std::remove_cv<typename std::remove_reference<T>::type>::type> {
};

#endif
