#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "rebelfleet.h"
#include "imperialfleet.h"

template<typename T, T t0, T t1, typename... S>
class SpaceBattle {
	std::tuple<S...> ships;
	T time;
	constexpr SpaceBattle(const S&... _ships) :
		time(t0), ships(_ships...) { }


};

#endif