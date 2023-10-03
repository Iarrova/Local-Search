#pragma once

#ifndef HILL_CLIMBING_HPP_
#define HILL_CLIMBING_HPP_

#include <string>

#include "knapsack.hpp"
#include "rng.hpp"

class HillClimbingSolver{
    private:
        KnapsackInstance knapsack_instance;
        State state;
        RNG rng;

        void best_improvement();
        void first_improvement();

    public:
        HillClimbingSolver(const KnapsackInstance& knapsack_instance);
        void solve(std::string method);
};

#endif