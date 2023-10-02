#include <random>
#include <iostream>

#include "rng.h"

RNG::RNG(){
	rng.seed(0);
};

RNG::RNG(int seed){
	rng.seed(seed);
};

int RNG::get_random_number(int max){
	std::uniform_int_distribution<> dist(0, max);
	return dist(rng);
};