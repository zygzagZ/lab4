#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "rebelfleet.h"
#include "imperialfleet.h"
#include <tuple>

template<typename T, T t0, T t1, typename... S>
class SpaceBattle {
	std::tuple<S...> ships;
	T time;
	// const std::array<> attackTimes = calculateAttackTimes(t1);

public:
	constexpr SpaceBattle(S... _ships) :
		time(t0), ships(std::forward<S>(_ships)...)
	{ 
		static_assert(t0 <= t1 && t1 > 0, "Niepoprawne czasy bitwy.");
	}

	size_t countImperialFleet() const {
		size_t result = 0;
		for_each_in_tuple(ships, [&result](const auto &ship) {
			if (is_imperial<decltype(ship)>::res)
				++result;
		});
		return result;
	}

	size_t countRebelFleet() const {
		size_t result = 0;
		for_each_in_tuple(ships, [&result](const auto &ship) {
			if (is_rebel<decltype(ship)>::res)
				++result;
		});
		return result;
	}

	void tick(T timeStep) {


	}

private:
	void attack() {
		for_each_in_tuple(ships, [&](auto &i) {
			if ((is_imperial<decltype(i)>::res) && i.getShield() > 0) {
				for_each_in_tuple(ships, [&](auto &r) {
					if(is_rebel<decltype(r)>::res && r.getShield() > 0) {
						::attack(i, r);
					}
				});
			}
		});
	}

	auto calculateAttackTimes() {

	}

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