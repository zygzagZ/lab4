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
	constexpr void takeDamage(U damage) {
		cout << "TakeDamage(" << damage << ") of " << typeid(decltype(*this)).name() << endl;
		if (shield > damage)
			shield -= damage;
		else
			shield = 0;
	}



	/*template <class... Args>
	struct attack {
		attack(Args...) {
			cout << "bledna walka1" << endl;
		};
	};*/

	template <class I, class R>
	struct attack {
		constexpr attack(I &i, R &r) {
			using CI = typename std::remove_cv<typename std::remove_reference<I>::type>::type;
			using CR = typename std::remove_cv<typename std::remove_reference<R>::type>::type;
			_attack<CI&, CR&>(i, r);
		}
	};

	template <class I, class R>
	struct _attack {
		_attack(const I&, const R&) {
			cout << "bledna walka" << endl;
		};
	};

	template <class IU, class RU, bool aggressive, bool slow>
	struct _attack<ImperialStarship<IU>&, RebelStarship<RU, aggressive, slow>&> {
		constexpr _attack(ImperialStarship<IU> &i, RebelStarship<RU, true, slow> &r) {
			cout << "walka obu" << endl;
			r.takeDamage(i.getAttackPower());
			i.takeDamage(r.getAttackPower());
		}
		constexpr _attack(ImperialStarship<IU> &i, RebelStarship<RU, false, slow> &r) {
			cout << "walka ucieka" << endl;
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
struct is_imperial_ : std::false_type {
	const static bool res = false;
};
template <class T>
struct is_imperial_<ImperialStarship<T>> : std::true_type {
	const static bool res = true;
};

template <class...>
struct is_imperial : std::false_type {
	const static bool res = false;
};
template <class T>
struct is_imperial<T> : is_imperial_
	<typename std::remove_cv<typename std::remove_reference<T>::type>::type> {
};

template<typename I, typename R>
inline void attack(I &imperialShip, R &rebelShip) {
	static_assert(is_imperial<I>::res && is_rebel<R>::res, "Wrong types of starships!");
	ImperialStarship<int>::attack<I, R>(imperialShip, rebelShip);
}

#endif
