#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "rebelfleet.h"
#include "imperialfleet.h"
#include <tuple>
#include <vector>
#include <cmath>

template<typename T, T t0, T t1, typename... S>
class SpaceBattle {
	std::tuple<S...> ships;
	T time;
	size_t currentIndex = 0;

public:
	constexpr SpaceBattle(S... _ships) :
		time(t0), ships(std::forward<S>(_ships)...)
	{ 
		while (currentIndex < attackTimes.size() && 
			attackTimes[currentIndex] < t0)
		{
			currentIndex++;
		}
		static_assert(t0 <= t1 && t1 > 0, "Niepoprawne czasy bitwy.");
		cout << "Total ships in battle: " << sizeof...(S) << " ci: " << 
			currentIndex << "/" << attackTimes.size() << endl;
		static_assert(attackTimes[0] == 1, "attackTimes not calculated at compilation time");
	}

	size_t countImperialFleet() const {
		size_t result = 0;
		for_each_in_tuple(ships, [&](const auto &ship) {
			if (is_imperial<decltype(ship)>::res && ship.getShield() > 0) {
				++result;
			}
		});
		return result;
	}

	size_t countRebelFleet() const {
		size_t result = 0;
		for_each_in_tuple(ships, [&](const auto &ship) {
			if (is_rebel<decltype(ship)>::res && ship.getShield() > 0) {
				++result;
			}
		});
		return result;
	}

	void tick(T timeStep) {
		cout << "tick @" << time << " o " << timeStep << " ci: " << 
			currentIndex << endl;
		while (currentIndex < attackTimes.size() && 
			attackTimes[currentIndex] < time)
		{ currentIndex++; }

		if (currentIndex < attackTimes.size() && 
			attackTimes[currentIndex] == time)
		{ attack(); }

		time += timeStep;
		if (time > t1) {
			time = 0;
			currentIndex = 0;
		}

	}

private:
	void attack() {
		cout << "Walka!\n";
		for_each_in_tuple(ships, [&](auto &i) {
			if ((is_imperial<decltype(i)>::res) && i.getShield() > 0) {
				for_each_in_tuple(ships, [&](auto &r) {
					if(is_rebel<decltype(r)>::res && r.getShield() > 0) {
						cout << "bija sie" << endl;
						ImperialStarship<int>::attack<decltype(i), decltype(r)>(i, r);
					}
				});
			}
		});
	}

	constexpr static T getTimeArraySize() {
		for (T s = 1; ; s++) {
			if (s*s >= t1)
				return s-(s*s > t1);
		}
	}
	constexpr static T arraySize = getTimeArraySize();

	constexpr static std::array<T, arraySize> calculateAttackTimes() {
		std::array<T, arraySize> arr{0};
		for (T i = 1; i*i <= arraySize; i++) {
			arr[i-1] = i*i;
		}
		return arr;
	}
	constexpr static std::array<T, arraySize> attackTimes = calculateAttackTimes();

	template<class F, class...Ts, std::size_t...Is>
	static void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func, std::index_sequence<Is...>){
	    using expander = int[];
	    (void)expander { 0, ((void)func(std::get<Is>(tuple)), 0)... };
	}

	template<class F, class...Ts>
	static void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func){
	    for_each_in_tuple(tuple, func, std::make_index_sequence<sizeof...(Ts)>());
	}
};

#endif