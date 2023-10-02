#pragma once
/* 
 * knapsack.h
 * Includes all definitions for the 0/1 Knapsack problem
 */
#ifndef RNG_H_
#define RNG_H_

/**
 * Generates a random solution factible solution to begin the search problem
*/

#include <random>

class RNG{
    private:
        std::mt19937 rng;
    public:
        RNG();
        RNG(int seed);

        /**
         * Generates a random number between 0 and `max`
         * 
         * @param max The maximum number that can be returned
         *      The random number will be between 0 and `max`
         * 
         * @returns A random number in the range [0, max]
        */
        int get_random_number(int max);
};

#endif