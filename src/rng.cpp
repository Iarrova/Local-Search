#include <random>
#include <iostream>

#include "rng.hpp"

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

float RNG::get_random_probability(){
	std::uniform_int_distribution<> dist(0, 100);
	float prob = dist(rng);
	return prob / 100;
}