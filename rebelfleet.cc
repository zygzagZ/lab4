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

template<typename U, bool is_explorer, U min_speed, U max_speed>
class RebelStarship {
	U shield, speed, attackPower;
public:
	using valueType = U;

	template <typename = std::enable_if<is_explorer, void>>
	constexpr RebelStarship(U _shield, U _speed) 
		: shield(_shield), speed(_speed)
	{
		if (min_speed > _speed || _speed > max_speed)
			throw std::logic_error("Niepoprawna prędkość");
	}

	template <typename = std::enable_if<!is_explorer, void>, U _min = min_speed, U _max = max_speed>
	constexpr RebelStarship(U _shield, U _speed, U _attackPower) 
		: shield(_shield), speed(_speed), attackPower(_attackPower)
	{ 
		if (min_speed > _speed || _speed > max_speed)
			throw std::logic_error("Niepoprawna prędkość");
	}


	template <typename = std::enable_if<is_explorer, void>>
	constexpr U getAttackPower() const { return attackPower; }

	constexpr U getShield() const { return shield; }
	constexpr U getSpeed() const { return speed; }
	void takeDamage(U damage) { shield = max(0, shield - damage); }
};

template<typename U>
using Explorer = RebelStarship<U, true, speed::min, speed::max>;

template<typename U>
using StarCruiser = RebelStarship<U, false, speed::StarCruiser::min, speed::StarCruiser::max>;

template<typename U>
using XWing = RebelStarship<U, false, speed::min, speed::max>;

int main () {
	// Explorer<uint> e1(100, 100);
    constexpr XWing<uint> xwing(100, 300000, 50);
    // constexpr XWing<uint> xwing2(100, 200000, 50);
	static_assert(xwing.getShield() == 100);
	// Explorer<uint> e2(100, 100, 100);

	return 0;
}
