#pragma once

#ifndef RNG_HPP_
#define RNG_HPP_

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

        /**
         * Generates a random probability - a float between 0 and 1
         * 
         * @returns A random probability in the range [0, 1]
        */
        float get_random_probability();
};

#endif